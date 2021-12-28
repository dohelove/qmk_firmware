/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include "swapper.h"
/* #include "print.h" */

enum layers {
    _QWERTY = 0,
    _QWERTYB,
    _NAV,
    _SYM,
    _NUMBER,
    _FUNCTION,
    _ADJUST,
};

enum custom_keycodes {
    OS_SFT = SAFE_RANGE,
    OS_CTL,
    OS_ALT,
    OS_GUI,
    SW_WIN,   // Switch to next window        (cmd-tab)
    SW_RWIN,  // Switch to previous window    (cmd-shift-tab)
    SW_WINA,  // Activate selected window     (cmd-tab-alt)
    REPEAT,
    KC_CCCV,
    SV_QWY,
    SV_QWYB,
};

#define QWERTY   DF(_QWERTY)
#define QWERTYB  DF(_QWERTYB)
#define BASE     TO(0)
#define SYM      TT(_SYM)
#define NAV      TT(_NAV)
#define NUM      TT(_NUMBER)
#define FKEYS    MO(_FUNCTION)
#define BLANK    MO(_BLANK)
#define ADJUST   MO(_ADJUST)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUT  MT(MOD_LCTL, KC_QUOTE)
#define ALT_ENT  MT(MOD_LALT, KC_ENTER)
#define ALT_SPC  MT(MOD_LALT, KC_SPC)

#define CTAB     C(KC_TAB)
#define CRTAB    C(S(KC_TAB))

enum combo_events {
    COMB_CAPS,
    COMB_BASE,
};

// uint16_t COMBO_LEN = COMBO_LENGTH;
uint16_t COMBO_LEN = 1;

const uint16_t PROGMEM caps_combo[] = {KC_LSFT, KC_RSFT, COMBO_END};
/* const uint16_t PROGMEM base_combo[] = {ALT_ENT, ALT_SPC, COMBO_END}; */

combo_t key_combos[] = {
    [COMB_CAPS] = COMBO(caps_combo , KC_CAPS),
    /* [COMB_BASE] = COMBO(base_combo , BASE), */
};

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang	format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Base Layer: QWERTY
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |  Tab |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |  Esc |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   ;  |   '  |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |      | CcCv |  | Caps |      |   N  |   M  |   ,  |   .  |   /  | Shift|
 * `--------------------+------+------+------+ Enter+------|  |------+ Space+------+------+------+--------------------'
 *                      |Adjust| FKeys|  Nav | /Alt | Num  |  |  Sym | /Alt | Lang | Menu |Adjust|
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                     KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
     CTL_ESC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                     KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, CTL_QUT,
     KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , XXXXXXX, KC_CCCV, KC_CAPS, XXXXXXX, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                                ADJUST , FKEYS  , NAV    , ALT_ENT, NUM    , SYM    , ALT_SPC, KC_HAEN, KC_APP , ADJUST
    ),

/*
 * Base Layer: QWERTYB
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |  Tab |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |  Esc |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   B  |   '  |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   ;  |      | CcCv |  | Caps |      |   N  |   M  |   ,  |   .  |   /  | Shift|
 * `--------------------+------+------+------+ Enter+------|  |------+ Space+------+------+------+--------------------'
 *                      |Adjust| FKeys|  Nav | /Alt | Num  |  |  Sym | /Alt |  Lang| Menu |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_QWERTYB] = LAYOUT(
     KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                     KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
     CTL_ESC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                     KC_H   , KC_J   , KC_K   , KC_L   , KC_B   , CTL_QUT,
     KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_SCLN, XXXXXXX, KC_CCCV, KC_CAPS, XXXXXXX, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                                ADJUST , FKEYS  , NAV    , ALT_ENT, NUM    , SYM    , ALT_SPC, KC_HAEN, KC_APP , _______
    ),

/*
 * Sym Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |   @  |   $  |   #  |   ^  |   \  |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * | Base |   |  |   =  |   +  |   -  |   !  |                              |      | Shift| Ctrl |  Alt |  Gui | Base |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |   `  |   %  |   *  |   ~  |   &  |      |      |  | Caps |      |      |      |      |      |      |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      |      |      |      |  |      |      | Lead |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
      _______, KC_AT  , KC_DLR , KC_HASH, KC_CIRC, KC_BSLS,                                    _______, _______, _______, _______, _______, _______,
      BASE   , KC_PIPE, KC_EQL , KC_PERC, KC_CIRC, KC_EXLM,                                    _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, BASE   ,
      _______, KC_GRV , KC_PERC, KC_ASTR, KC_TILD, KC_AMPR,_______, _______, KC_CAPS, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______,_______, _______, _______, _______, KC_LEAD, _______, _______
    ),

/*
 * Num Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |   :  |   -  |      |      |                              |   /  |   1  |   2  |   3  |   -  |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * | Base |  Gui |  Alt | Ctrl | Shift|      |                              |   0  |   4  |   5  |   6  |   +  |   .  |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | CcCv |  |      |      |   =  |   7  |   8  |   9  |   *  |      |
 * `------+------+------+--------------------+------+------|  |------+------+-------------+------+------+-------------'
 *                      |      |      |      |      |      |  |      |      | Lead |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_NUMBER] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_X   , KC_1   , KC_2   , KC_3   ,KC_MINS,  _______,
      BASE   , KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     KC_0   , KC_4   , KC_5   , KC_6   ,KC_PLUS,  KC_UNDS,
      _______, _______, _______, _______, _______, _______, _______, KC_CCCV, _______, _______, KC_COLN, KC_7   , KC_8   , KC_9   ,KC_EQL ,  _______,
                                 _______, _______, _______, _______, _______, _______, _______, KC_LEAD, _______, _______
    ),

/*
 * Function Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |      |      |      |      |                              |      |  F1  |  F2  |  F3  |  F4  |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * | Base |  Gui |  Alt | Ctrl | Shift|      |                              |      |  F5  |  F6  |  F7  |  F8  |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  |      |      |      |  F9  | F10  | F11  | F12  |      |
 * `------+------+------+--------------------+------+------|  |------+------+--------------------+------+------+------'
 *                      |      |      |      |      |      |  |      |      | Lead |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                       `--------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , _______,
      BASE   , KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     _______, KC_F5  , KC_F6  , KC_F7  , KC_F8  , _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______,
                                 _______, _______, _______, _______, _______, _______, _______, KC_LEAD, _______, _______
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      | WinRT| WinT |      |      |                              | ScLck| Home |  Up  |  End |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * | Base |  Gui |  Alt | Ctrl | Shift|      |                              | PrtSc|  Lt  |  Dn  |  Rt  |  Del |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  |      |      | Pause| PgUp |  Ins | PgDn |      |      |
 * `------+------+------+--------------------+------+------|  |------+------+--------------------+------+------+------'
 *                      |      |      |      |      |      |  |      |      | Lead |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, CRTAB  , SW_RWIN, SW_WIN , CTAB   , _______,                                     KC_SLCK, KC_HOME, KC_UP  , KC_END , _______, _______,
      BASE   , KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     KC_PSCR, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , _______,
      _______, _______, _______, _______, _______, _______, XXXXXXX, _______, _______, XXXXXXX, KC_PAUS, KC_PGUP, KC_INS , KC_PGDN, _______, _______,
                                 _______, _______, _______, _______, _______, _______, KC_DOWN, KC_LEAD, _______, _______
    ),

/*
 * Blank Layer:
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    /* [_BLANK] = LAYOUT( */
    /*   _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______, _______, _______, */
    /*   _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______, _______, _______, */
    /*   _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
    /*                              _______, _______, _______,_______, _______, _______, _______, _______, _______, _______ */
    /* ), */

/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, SV_QWY , SV_QWYB, _______,                                    _______, _______, _______, _______, _______, _______,
      _______, _______, _______, QWERTY , QWERTYB, _______,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, _______, _______,
      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, _______, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),
};

uint16_t copy_paste_time;

bool sw_win_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    /* swapper must be after oneshot other wise there can be lingering mods */
    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, SW_RWIN, SW_WINA, keycode, record);

    switch (keycode) {
    case KC_CCCV:  // One key copy/paste
        if (record->event.pressed) {
            copy_paste_time = timer_read();
        } else {
            if (timer_elapsed(copy_paste_time) > TAPPING_TERM) {  // Hold, copy
                tap_code16(LCTL(KC_C));
            } else { // Tap, paste
                tap_code16(LCTL(KC_V));
            }
        }
        break;
    case SV_QWY:
        if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
            layer_move(_QWERTY);
        }
        return false;
    case SV_QWYB:
        if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTYB);
            layer_move(_QWERTYB);
        }
        return false;
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {

    uint8_t encoder_side_n_dir = (index << 1) | clockwise;

    if (IS_LAYER_ON(_NAV)) {
        switch (encoder_side_n_dir) {
        case 0b11:
            tap_code16(LCTL(KC_LEFT));
            break;
        case 0b10:
            tap_code16(LCTL(KC_RGHT));
            break;
        default:
            break;
        }
    } else {
        switch (encoder_side_n_dir) {
        case 0b01:
            tap_code(KC_MS_WH_DOWN);
            break;
        case 0b00:
            tap_code(KC_MS_WH_UP);
            break;
        case 0b11:
            tap_code16(KC_VOLD);
            break;
        case 0b10:
            tap_code16(KC_VOLU);
            break;
        default:
            break;
        }
    }
    return false;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

void oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

        /* // Host Keyboard Layer Status */
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("QWERTY\n"), false);
                break;
            case _QWERTYB:
                oled_write_P(PSTR("QWERTY-B\n"), false);
                break;
            case _NUMBER:
                oled_write_P(PSTR("Num\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case _SYM:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Func\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adj\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

    } else {
        /* // Write host Keyboard LED Status to OLEDs */

        oled_write_P(PSTR("DoHee's Keeb!\n"), false);
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
    }
}
#endif

/*
LEADER_EXTERNS();
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_S) {
        layer_on(_NUMBER);
    }

    SEQ_ONE_KEY(KC_D) {
        layer_on(_NAV);
    }

    SEQ_ONE_KEY(KC_ESC) {
        layer_clear();
        layer_on(_QWERTY);
    }

    SEQ_ONE_KEY(KC_F) {
      // Anything you can do in a macro.
      SEND_STRING("QMK is awesome.");
    }
    SEQ_TWO_KEYS(KC_D, KC_D) {
      SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
      SEND_STRING("https://start.duckduckgo.com\n");
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }
  }
}
*/
