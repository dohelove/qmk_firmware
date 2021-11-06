#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"
#include "split_common/split_util.h"
#include "split_common/transactions.h"
#include  "gpio.h"

#define ROWS_PER_HAND (MATRIX_ROWS / 2)

#define SPLIT_MUTABLE_ROW const
#define SPLIT_MUTABLE_COL const


static SPLIT_MUTABLE_ROW pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static SPLIT_MUTABLE_COL pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

/* matrix state(1:on, 0:off) */
matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
matrix_row_t matrix[MATRIX_ROWS];      // debounced values

int64_t *raw_matrix_p    = (int64_t *)raw_matrix;
int64_t *matrix_p        = (int64_t *)matrix;
int32_t *matrix_master_p = (int32_t *)matrix;
int32_t *matrix_slave_p  = (int32_t *)matrix + 1;

// row offsets for each hand
uint8_t thisHand, thatHand;

// user-defined overridable functions
__attribute__((weak)) void matrix_init_pins(void);
__attribute__((weak)) void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row);
__attribute__((weak)) void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col);
__attribute__((weak)) void matrix_slave_scan_kb(void) { matrix_slave_scan_user(); }
__attribute__((weak)) void matrix_slave_scan_user(void) {}

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }
__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }
__attribute__((weak)) void matrix_init_user(void) {}
__attribute__((weak)) void matrix_scan_user(void) {}
__attribute__((weak)) void matrix_output_select_delay(void) { waitInputPinDelay(); }

#define MATRIX_IO_DELAY 30
__attribute__((weak)) void matrix_output_unselect_delay(uint8_t line, bool key_pressed) { wait_us(MATRIX_IO_DELAY); }

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON { setPinInputHigh(pin); }
}

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return readPin(pin);
    } else {
        return 1;
    }
}

// matrix code
static bool select_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        setPinOutput_writeLow(pin);
        return true;
    }
    return false;
}

static void unselect_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        setPinInputHigh_atomic(pin);
    }
}

static void unselect_rows(void) {
    for (uint8_t x = 0; x < ROWS_PER_HAND; x++) {
        unselect_row(x);
    }
}

__attribute__((weak)) void matrix_init_pins(void) {
    unselect_rows();
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        if (col_pins[x] != NO_PIN) {
            setPinInputHigh_atomic(col_pins[x]);
        }
    }
}

// TODO: Explain details of the optimizations on the matrix scan code.

// https://docs.splitkb.com/hc/en-us/articles/360010588560-Which-microcontroller-pins-does-the-Kyria-use-
// COL pins: { B6, B2, B3, B1, F7, F6, F5, F4 }
// COL0_state:  pinB_state & 01000000
// COL1_state:  pinB_state & 00000100
// COL2_state:  pinB_state & 00001000
// COL3_state:  pinB_state & 00000010
// COL4_state:  pinF_state & 10000000
// COL5_state:  pinF_state & 01000000
// COL6_state:  pinF_state & 00100000
// COL7_state:  pinF_state & 00010000

// Shift operation is expansive when the n is high.
// So we define it in advance.
#define B0_PORT B0 >> 4
#define F0_PORT F0 >> 4

__attribute__((weak)) void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    if (!select_row(current_row)) {  // Select row
        return;                      // skip NO_PIN row
    }

    matrix_output_select_delay();
    //_PIN_ADDRESS(p, offset) _SFR_IO8(ADDRESS_BASE + ((p) >> PORT_SHIFTER) + (offset))
    // ADDRESS_BASE: 0
    // PORT_SHIFTER: 4
    // OFFSET      : 0
    port_data_t port_state_B = _SFR_IO8(B0_PORT);
    port_data_t port_state_F = _SFR_IO8(F0_PORT);

    // Unselect row
    unselect_row(current_row);
    current_row_value = (port_state_B & 0b01000000 ? 0 : 0b00000001)
                      | (port_state_B & 0b00000100 ? 0 : 0b00000010)
                      | (port_state_B & 0b00001000 ? 0 : 0b00000100)
                      | (port_state_B & 0b00000010 ? 0 : 0b00001000)
                      | (port_state_F & 0b10000000 ? 0 : 0b00010000)
                      | (port_state_F & 0b01000000 ? 0 : 0b00100000)
                      | (port_state_F & 0b00100000 ? 0 : 0b01000000)
                      | (port_state_F & 0b00010000 ? 0 : 0b10000000);

    matrix_output_unselect_delay(current_row, current_row_value != 0);  // wait for all Col signals to go HIGH

    // Update the matrix
    current_matrix[current_row] = current_row_value;
}

void matrix_init(void) {
    split_pre_init();

    thisHand = isLeftHand ? 0 : (ROWS_PER_HAND);
    thatHand = ROWS_PER_HAND - thisHand;

    // initialize key pins
    matrix_init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(ROWS_PER_HAND);

    matrix_init_quantum();

    split_post_init();
}

static matrix_row_t slave_matrix[ROWS_PER_HAND] = {0};
int32_t *slave_matrix_p = (int32_t *)slave_matrix;

bool matrix_post_scan(void) {
    bool changed = false;
    if (is_keyboard_master()) {
        transport_master(matrix + thisHand, slave_matrix);
        matrix_scan_quantum();
        changed = *matrix_slave_p == *slave_matrix_p;
        *matrix_slave_p = *slave_matrix_p;
    }
    else {
        transport_slave(matrix + thatHand, matrix + thisHand);

        matrix_slave_scan_kb();
    }
    return changed;
}

static matrix_row_t curr_matrix[MATRIX_ROWS] = {0};
int64_t *curr_matrix_p = (int64_t *)curr_matrix;

uint8_t matrix_scan(void) {

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < ROWS_PER_HAND; current_row++) {
        matrix_read_cols_on_row(curr_matrix, current_row);
    }

    bool changed = *raw_matrix_p != *curr_matrix_p;
    *raw_matrix_p = *curr_matrix_p;

    debounce(raw_matrix, matrix + thisHand, ROWS_PER_HAND, changed);
    changed = (changed || matrix_post_scan());
    return (uint8_t)changed;
}

matrix_row_t matrix_get_row(uint8_t row) {
    // debounced values
    return matrix[row];
}

void matrix_print(void) {
    // TODO: use print() to dump the current matrix state to console
}
