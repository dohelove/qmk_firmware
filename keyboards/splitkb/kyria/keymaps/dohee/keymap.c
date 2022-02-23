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
#include "caps_word.h"
#include "common.h"
/* #include "print.h" */

#ifdef BONGO_ENABLE
#include "bongo.h"
#endif


enum custom_keycodes {
    KC_CCCV = SAFE_RANGE,
    SW_WIN,   // (alt-tab)
    SW_RWIN,  // (alt-shift-tab)
};

#define BASE     TO(0)
#define QWERTY   DF(_QWERTY)
#define SYM      TT(_SYM)
#define NAV      TT(_NAV)
#define NUM      TT(_NUMBER)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUT  MT(MOD_RCTL, KC_QUOTE)
#define ALT_ENT  MT(MOD_LALT, KC_ENTER)
#define ALT_SPC  MT(MOD_LALT, KC_SPC)

#define CTAB     C(KC_TAB)
#define CRTAB    C(S(KC_TAB))


// clang	format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Base Layer: QWERTY
 *
 * ,------------------------------------------.                              ,------------------------------------------.
 * |  Tab  |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  | Bspc  |
 * |-------+------+------+------+------+------|                              |------+------+------+------+------+-------|
 * |Esc/Ctl|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   ;  | '/Ctl |
 * |-------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+-------|
 * | Shift |   Z  |   X  |   C  |   V  |   B  |      | CcCv |  | Enter|      |   N  |   M  |   ,  |   .  |   /  | Shift |
 * `---------------------+------+------+------+ Enter+------|  |------+ Space+------+------+------+---------------------'
 *                       |Adjust| Menu | FKeys| /Alt | Sym  |  |  Num | /Alt |  Nav | Lang |Adjust|
 *                       |      |      |      |      |      |  |      |      |      |      |      |
 *                       `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                     KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
     CTL_ESC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                     KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, CTL_QUT,
     KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , XXXXXXX, KC_CCCV, KC_ENT , XXXXXXX, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                                ADJUST , KC_APP , FKEYS  , ALT_ENT, SYM    , NUM    , ALT_SPC, NAV    , KC_HAEN, ADJUST
    ),

/*
 * Sym Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |   `  |   $  |   #  |   &  |   ^  |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * | Base |   !  |   =  |   +  |   -  |   |  |                              |      | Shift| Ctrl |  Gui |  Alt |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |   @  |   %  |   *  |   ~  |   \  |      |      |  | Enter|      |      |      |      |      |      |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
      _______, KC_AT  , KC_DLR , KC_HASH, KC_CIRC, KC_BSLS,                                    _______, _______, _______, _______, _______, _______,
      BASE   , KC_PIPE, KC_EQL , KC_PERC, KC_CIRC, KC_EXLM,                                    _______, KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT, _______,
      _______, KC_GRV , KC_PERC, KC_ASTR, KC_TILD, KC_AMPR,_______, _______, KC_ENT , _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Num Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |   :  |   .  |      |      |                              |   /  |   1  |   2  |   3  |   -  |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * | Base |  Alt |  Gui | Ctrl | Shift|      |                              |   0  |   4  |   5  |   6  |   +  |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  | Enter|      |   =  |   7  |   8  |   9  |   *  |      |
 * `------+------+------+--------------------+------+------|  |------+------+-------------+------+------+-------------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_NUMBER] = LAYOUT(
      _______, _______, KC_COLN, KC_DOT , _______, _______,                                     KC_SLSH, KC_1   , KC_2   , KC_3   ,KC_MINS,  _______,
      BASE   , KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT, _______,                                     KC_0   , KC_4   , KC_5   , KC_6   ,KC_PLUS,  _______,
      _______, _______, _______, _______, _______, _______, _______, _______, KC_ENT , _______, KC_EQL , KC_7   , KC_8   , KC_9   ,KC_ASTR,  _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      | BrwRT| WinRT| WinT | BrwT |      |                              | ScLck| Home |  Up  |  End |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * | Base |  Alt |  Gui | Ctrl | Shift|      |                              | PrtSc|  Lt  |  Dn  |  Rt  |  Del |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  |      |      | Pause| PgUp |  Ins | PgDn |      |      |
 * `------+------+------+--------------------+------+------|  |------+------+--------------------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, CRTAB  , SW_RWIN, SW_WIN , CTAB   , _______,                                     KC_SLCK, KC_HOME, KC_UP  , KC_END , _______, _______,
      BASE   , KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT, _______,                                     KC_PSCR, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PAUS, KC_PGUP, KC_INS , KC_PGDN, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Function Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |      |      |      |      |                              |      |  F1  |  F2  |  F3  |  F4  |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |  Alt |  Gui | Ctrl | Shift|      |                              |      |  F5  |  F6  |  F7  |  F8  |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  |      |      |      |  F9  | F10  | F11  | F12  |      |
 * `------+------+------+--------------------+------+------|  |------+------+--------------------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                       `--------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , _______,
      _______, KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT, _______,                                     _______, KC_F5  , KC_F6  , KC_F7  , KC_F8  , _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

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
      _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, _______, _______,
      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, _______, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),
};

uint16_t copy_paste_time;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!update_swapper(KC_LGUI, KC_TAB, SW_WIN, SW_RWIN, KC_SPC , keycode, record)) {
        return false;
    }

    if (!process_caps_word(keycode, record)) {
        return false;
    }

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
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {

    uint8_t encoder_side_n_dir = (index << 1) | clockwise;
    const uint8_t mods = get_mods();

    switch (encoder_side_n_dir) {
    case 0b01:
        if ((mods & MOD_BIT(KC_RCTL)) == MOD_BIT(KC_RCTL)) {
            tap_code16(KC_Z);
        } else {
            tap_code(KC_MS_WH_DOWN);
        }
        break;
    case 0b00:
        if ((mods & MOD_BIT(KC_RCTL)) == MOD_BIT(KC_RCTL)) {
            tap_code16(KC_Y);
        } else {
            tap_code(KC_MS_WH_UP);
        }
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
    return false;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

void oled_task_user(void) {
    if (is_keyboard_master()) {
        draw_bongo();
        // QMK Logo and version information
        /* static const char PROGMEM qmk_logo[] = { */
        /*     0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94, */
        /*     0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4, */
        /*     0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0}; */
        // clang-format on
        /* oled_write_P(qmk_logo, false); */
        /* oled_write_P(PSTR("Kyria rev1.0\n\n"), false); */


        oled_set_cursor(0, 5);
        oled_write("Layer: ", false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                oled_write("QWERTY", false);
                break;
            case _NUMBER:
                oled_write("Num   ", false);
                break;
            case _NAV:
                oled_write("Nav   ", false);
                break;
            case _SYM:
                oled_write("Sym   ", false);
                break;
            case _FUNCTION:
                oled_write("Func  ", false);
                break;
            case _ADJUST:
                oled_write("Set   ", false);
                break;
            default:
                oled_write("Error ", false);
        }

        led_t led_usb_state = host_keyboard_led_state();
        oled_set_cursor(0, 6);
        oled_write(led_usb_state.caps_lock ? "CAPLCK " : "       ", false);

    } else {
        oled_set_cursor(0, 2);
        oled_write("DoHee's Keeb!", false);
        /* led_t led_usb_state = host_keyboard_led_state(); */
        /* oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false); */
        /* oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false); */
        /* oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false); */
    }
}
#endif
