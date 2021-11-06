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

#include "oneshot.h"
#include "swapper.h"

enum layers {
    _QWERTY = 0,
    _CATAC,
    _NAV,
    _SYM,
    _BRACKET,
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
    SE_J,
    SE_T,
    SE_SPC,
    SE_ZERO,
    KC_CCCV,
};

#define CATAC    DF(_CATAC)
#define QWERTY   MO(_QWERTY)

#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define NUM      MO(_NUMBER)
#define BRC      MO(_BRACKET)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_X    MT(MOD_LCTL, KC_X  )
#define CTL_QUT  MT(MOD_RCTL, KC_QUOTE)
#define CTL_MNS  MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

#define SFT_SPC  MT(MOD_LSFT, KC_SPC)

#define MC_A     MT(MOD_LGUI, KC_A)
#define MC_S     MT(MOD_LALT, KC_S)
#define MC_D     MT(MOD_LSFT, KC_D)
#define MC_F     MT(MOD_LCTL, KC_F)

#define MC_J     MT(MOD_LCTL, KC_J)
#define MC_K     MT(MOD_LSFT, KC_K)
#define MC_L     MT(MOD_LALT, KC_L)
#define MC_SCLN  MT(MOD_LGUI, KC_SCLN)

#define CTAB     C(KC_TAB)
#define CRTAB    C(S(KC_TAB))


// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang	format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Base Layer: CATAC
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |  Tab |   W  |   F  |   C  |   D  |   K  |                              |   Z  |   J  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |  Esc |   R  |   N  |   S  |   T  |   G  |                              |   X  |   L  |   E  |   I  |   A  |   '  |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * | Shift|   Q  |   B  |   M  |   P  |   V  |      |      |  |      |      |   -  |   H  |   ,  |   .  |   /  | Enter|
 * `--------------------+------+------+------+ Space+------|  |------+   O  +------+------+------+--------------------'
 *                      |Adjust|  Num |  Nav |      | Shift|  | Ctrl |      |  Brc |  Sym | Menu |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_CATAC] = LAYOUT(
     KC_TAB , KC_W   , KC_F   , KC_C   , KC_D   , KC_K   ,                                     KC_Z   , KC_J   , KC_U   , KC_Y   , KC_SCLN, KC_BSPC,
     CTL_ESC, KC_R   , KC_N   , KC_S   , KC_T   , KC_G   ,                                     KC_X   , KC_L   , KC_E   , KC_I   , KC_A   , CTL_QUT,
     KC_ENT , KC_Q   , KC_B   , KC_M   , KC_P   , KC_V   , XXXXXXX, KC_LSFT, KC_LSFT, XXXXXXX, KC_MINS, KC_H   , KC_COMM, KC_DOT , KC_SLSH, KC_ENT ,
                                ADJUST , NUM    , NAV    , KC_SPC , KC_LSFT, KC_LCTL, KC_O   , BRC    , SYM    , KC_APP
    ),

/*
 * Base Layer: QWERTY
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |  Tab |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |  Esc |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   -  |   '  |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |  SYM |   Z  |   X  |   C  |   V  |   B  |      |      |  | Caps |      |   N  |   M  |   ,  |   .  |   /  |  Esc |
 * `--------------------+------+------+------+ Enter+------|  |------+ Space+------+------+------+--------------------'
 *                      |Adjust|  Num |  Nav |      | Shift|  |  Alt |      |  Brc |  Sym | Menu |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                     KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
     CTL_ESC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                     KC_H   , KC_J   , KC_K   , KC_L   , KC_MINS, CTL_QUT,
     KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , XXXXXXX, KC_TAB , KC_CAPS, XXXXXXX, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_LSFT,
                                ADJUST , NUM    , NAV    , KC_ENT , KC_LSFT, KC_LALT, SFT_SPC , BRC    , SYM    , KC_APP
    ),

/*
 * Sym Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |   @  |   $  |   #  |   ^  |   \  |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |   |  |   =  |   +  |   -  |   !  |                              |      |  Gui | Ctrl |  Alt | Shift|      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |   `  |   %  |   *  |   ~  |   &  |      |      |  |      |      |      |      |      |      |      |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
      _______, KC_AT  , KC_DLR , KC_HASH, KC_CIRC, KC_BSLS,                                    _______, _______, _______, _______, _______, _______,
      _______, KC_PIPE, KC_EQL , KC_PERC, KC_CIRC, KC_EXLM,                                    _______, OS_GUI , OS_CTL , OS_ALT , OS_SFT , _______,
      _______, KC_GRV , KC_PERC, KC_ASTR, KC_TILD, KC_AMPR,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Brc Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |      |      |      |      |                              |      |      |   [  |   ]  |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      | Shift|  Alt | Ctrl |  Gui |      |                              |   ,  |   {  |   (  |   )  |  }   |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  |      |      |   /  |   -  |   <  |   >  |  _   |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_BRACKET] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                    _______, _______, KC_LBRC, KC_RBRC, _______, _______,
      _______, OS_SFT , OS_ALT , OS_CTL , OS_GUI , _______,                                    KC_COMM, KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, _______,
      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, KC_SLSH, KC_MINS, KC_LABK, KC_RABK, KC_UNDS, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Num Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |      |      |      |      |                              |   x  |   1  |   2  |   3  |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      | Shift|  Alt | Ctrl |  Gui |      |                              |   _  |   4  |   5  |   6  |   0  |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  |      |      |   -  |   7  |   8  |   9  |   :  |      |
 * `------+------+------+--------------------+------+------|  |------+------+-------------+------+------+-------------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_NUMBER] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_X   , KC_1   , KC_2   , KC_3   ,_______,  _______,
      _______, OS_SFT , OS_ALT , OS_CTL , OS_GUI , _______,                                     KC_UNDS, KC_4   , KC_5   , KC_6   ,KC_0   ,  _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_7   , KC_8   , KC_9   ,KC_COLN,  _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Function Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |      |      |      |      |                              |      |  F1  |  F2  |  F3  |  F4  |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      | Shift|  Alt | Ctrl |  Gui |      |                              |      |  F5  |  F6  |  F7  |  F8  |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  |      |      |      |  F9  | F10  | F11  | F12  |      |
 * `------+------+------+--------------------+------+------|  |------+------+--------------------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                       `--------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , _______,
      _______, OS_SFT , OS_ALT , OS_CTL , OS_GUI , _______,                                     _______, KC_F5  , KC_F6  , KC_F7  , KC_F8  , _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      | WinRT| WinT |      |      |                              | ScLck| Home |  Up  |  End | PrtSc|      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      | Shift|  Alt | Ctrl |  Gui |      |                              |  Del |  Lt  |  Dn  |  Rt  |  Ins |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  |      |      | Pause| PgUp | Term | PgDn |      |      |
 * `------+------+------+--------------------+------+------|  |------+------+--------------------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, CRTAB  , SW_RWIN, SW_WIN , CTAB   , _______,                                     _______, KC_HOME, KC_UP  , KC_END , KC_PSCR, _______,
      _______, OS_SFT , OS_ALT , OS_CTL , OS_GUI , _______,                                     KC_DEL , KC_LEFT, KC_DOWN, KC_RGHT, KC_INS , _______,
      _______, SE_T   , SE_ZERO, SE_J   , SE_SPC , _______, _______, _______, _______, _______, KC_PAUS, KC_PGUP, SE_J   , KC_PGDN, _______, _______,
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
      _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______,  _______, _______,
      _______, _______, QWERTY , CATAC  , _______, _______,                                    _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),
};

uint16_t copy_paste_timer;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool sw_win_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    update_oneshot(&os_shft_state, KC_LSFT, OS_SFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTL, keycode, record);
    update_oneshot(&os_alt_state , KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_cmd_state , KC_LGUI, OS_GUI, keycode, record);

    /* swapper must be after oneshot other wise there can be lingering mods */
    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, SW_RWIN, SW_WINA, keycode, record);

    switch (keycode) {
    case SE_T:
        if (record->event.pressed) {
            tap_code16(A(G(KC_T)));
            return false;
        }
        break;
    case SE_SPC:
        if (record->event.pressed) {
            tap_code16(A(G(KC_SPC)));
            return false;
        }
        break;
    case SE_J:
        if (record->event.pressed) {
            tap_code16(A(G(KC_J)));
            return false;
        }
        break;
    case SE_ZERO:
        if (record->event.pressed) {
            tap_code16(A(G(KC_0)));
            return false;
        }
        break;
    case KC_CCCV:  // One key copy/paste
        if (record->event.pressed) {
            copy_paste_timer = timer_read();
        } else {
            if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
                tap_code16(LGUI(KC_C));
            } else { // Tap, paste
                tap_code16(LGUI(KC_V));
            }
        }
        break;
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {

    uint8_t encoder_side_n_dir = (index << 1) | clockwise;

    if (IS_LAYER_ON(_NAV)) {
        switch (encoder_side_n_dir) {
        case 0b11:
            tap_code16(LCTL(KC_RGHT));
            break;
        case 0b10:
            tap_code16(LCTL(KC_LEFT));
            break;
        default:
            break;
        }
    } else if (IS_LAYER_ON(_BRACKET)) {
        switch (encoder_side_n_dir) {
        case 0b11:
            tap_code16(SW_WIN);
            break;
        case 0b10:
            tap_code16(SW_RWIN);
            break;
        default:
            break;
        }
    } else {
        switch (encoder_side_n_dir) {
        case 0b01:
            tap_code(KC_MS_WH_UP);
            break;
        case 0b00:
            tap_code(KC_MS_WH_DOWN);
            break;
        case 0b11:
            tap_code16(CTAB);
            break;
        case 0b10:
            tap_code16(CRTAB);
            break;
        default:
            break;
        }
    }
    return false;
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case SYM:
    case NAV:
    case KC_LSFT:
    case OS_SFT:
    case OS_CTL:
    case OS_ALT:
    case OS_GUI:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case SYM:
    case NAV:
        return true;
    default:
        return false;
    }
}
