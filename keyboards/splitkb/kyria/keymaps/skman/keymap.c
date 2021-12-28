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
#include "print.h"

enum layers {
    _CATACV2 = 0,
    _HDX,
    _MTGAP,
    _CATAC,
    _TACAT,
    _SMMKJQ,
    _COLEMAK,
    _QWERTY,
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
    SE_DASH,
    KC_CCCV,
    /* CB_Q, */
    /* CB_Z, */
    AD_SCLL,
    AD_LSCL,
    SP_TH,
    SP_ION,
};

#define QWERTY   DF(_QWERTY)
#define MTGAP    DF(_MTGAP)
#define SMMKJQ   DF(_SMMKJQ)
#define CATACV2  DF(_CATACV2)
#define CATAC    DF(_CATAC)
#define TACAT    DF(_TACAT)
#define HDX      DF(_HDX)
#define COLEMAK  DF(_COLEMAK)

#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define NUM      MO(_NUMBER)
#define BRC      MO(_BRACKET)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_X    MT(MOD_LCTL, KC_X  )
#define CTL_QUT  MT(MOD_LCTL, KC_QUOTE)
#define CTL_SLH  MT(MOD_LCTL, KC_SLASH)
#define CTL_SCL  MT(MOD_LCTL, KC_SCLN)
#define CTL_MNS  MT(MOD_LCTL, KC_MINUS)
#define CTL_Q    MT(MOD_LCTL, KC_Q)
#define CTL_J    MT(MOD_LCTL, KC_J)
#define CTL_Z    MT(MOD_LCTL, KC_Z)
#define CTL_Y    MT(MOD_LCTL, KC_Y)
#define CTL_BSS  MT(MOD_LCTL, KC_BSLS)

#define SFT_CAP  MT(MOD_LSFT, KC_CAPS)
#define SFT_MNS  MT(MOD_LSFT, KC_MINUS)
#define SFT_ESC  MT(MOD_LSFT, KC_ESC)
#define SFT_ENT  MT(MOD_LSFT, KC_ENT)
#define SFT_SPC  MT(MOD_LSFT, KC_SPC)
#define SFT_QOT  MT(MOD_LSFT, KC_QUOT)
#define SFT_Q    MT(MOD_LSFT, KC_Q)
#define SFT_Z    MT(MOD_LSFT, KC_Z)

#define ALT_ENT  MT(MOD_LALT, KC_ENT)
#define ALT_SPC  MT(MOD_LALT, KC_SPC)

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

enum combo_events {
    COMB_Y,
};

/* uint16_t COMBO_LEN = COMBO_LENGTH; */
uint16_t COMBO_LEN = 1;

const uint16_t PROGMEM y_combo[] = {KC_K, KC_G, COMBO_END};

combo_t key_combos[] = {
    [COMB_Y]  = COMBO(y_combo , KC_Y ),
};


// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang	format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*  MTGAP
 * ,--------------------+--------------------.                              ,-----------------------------------------.
 * |  Tab |   Y  |   P  |   O  |   U  |   J  |                              |   K  |   D  |   L  |   C  |   W  | Bspc |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |  Esc |   I  |   N  |   E  |   A  |   ,  |                              |   M  |   H  |   T  |   S  |   R  |   '  |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |  Brc |   Q  |   Z  |   /  |   .  |   ;  |      | Caps |  |  Alt |      |   B  |   F  |   G  |   V  |   X  | Fkeys|
 * `--------------------+------+------+------+ Shift+------|  |------+ Space+------+------+------+--------------------'
 *                      |Adjust|  Nav |  Num |      | Ctrl |  | Enter|      | Shift|  Sym | Menu |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_MTGAP] = LAYOUT(
     KC_TAB , KC_Y   , KC_P   , KC_O   , KC_U   , KC_J   ,                                     KC_K   , KC_D   , KC_L   , KC_C   , KC_W   , KC_BSPC,
     CTL_ESC, KC_I   , KC_N   , KC_E   , KC_A   , KC_COMM,                                     KC_M   , KC_H   , KC_T   , KC_S   , KC_R   , CTL_QUT,
     BRC    , KC_Q   , KC_Z   , KC_SLSH, KC_DOT , KC_SCLN, XXXXXXX, KC_LALT, KC_LALT, XXXXXXX, KC_B   , KC_F   , KC_G   , KC_V   , KC_X   , FKEYS  ,
                                ADJUST , NAV    , NUM    , KC_LSFT, KC_LCTL, KC_ENT , KC_SPC , KC_RSFT, SYM    , KC_APP
    ),

/* Base Layer: TACAT
 *
 *  Adaptive Keys:
      + BM -> BL
      + MF -> MB
    Alt Finger:
      + LV: (Index , Index ) -> (Index , Middle)
      + MB: (Index , Index ) -> (Middle, Index )
      + NL: (Index , Index ) -> (Middle, Index )
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |  Tab |   .  |   ,  |   '  |   -  |   /  |                              |   Q  |   V  |   D  |   W  |   Z  | Bspc |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |  Esc |   R  |   I  |   O  |   E  |   K  |                              |   L  |   N  |   T  |   S  |   C  |  ;   |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * | Shift|   X  |   Y  |   A  |   U  |   J  |      |  Alt |  | Caps |      |   B  |   M  |   P  |   F  |   G  | Shift|
 * `--------------------+------+------+------+ Space+------|  |------+   H  +------+------+------+--------------------'
 *                      |Adjust|  Num |  Nav |      | Enter|  | FKeys|      |  Brc |  Sym | Menu |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_TACAT] = LAYOUT(
     KC_TAB , KC_DOT , KC_COMM, KC_QUOT, KC_MINS, KC_SLSH,                                     KC_Q   , KC_V   , KC_D   , KC_W   , KC_Z   , KC_BSPC,
     CTL_ESC, KC_R   , KC_I   , KC_O   , KC_E   , KC_K   ,                                     KC_L   , KC_N   , KC_T   , KC_S   , KC_C   , CTL_SCL,
     KC_LSFT, KC_X   , KC_Y   , KC_A   , KC_U   , KC_J   , XXXXXXX, KC_LALT, KC_LALT, XXXXXXX, KC_B   , KC_M   , KC_P   , KC_F   , KC_G   , KC_LSFT,
                                ADJUST , NUM    , NAV    , KC_SPC , KC_ENT , FKEYS  , KC_H   , BRC    , SYM    , KC_APP
    ),

/* Base Layer: CATAC
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |  Tab |   Q  |   Y  |   O  |   U  |   Z  |                              |   V  |   W  |   D  |   C  |   X  | Bspc |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |  Esc |   H  |   I  |   A  |   E  |   .  |                              |   F  |   N  |   T  |   S  |   R  |   -  |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * | Shift|   K  |   /  |   '  |   ,  |   ;  |      | Caps |  |  Alt |      |   B  |   P  |   M  |   G  |   J  | Shift|
 * `--------------------+------+------+------+   L  +------|  |------+ Space+------+------+------+--------------------'
 *                      |Adjust|  Num |  Nav |      | FKeys|  | Enter|      |  Brc |  Sym | Menu |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_CATAC] = LAYOUT(
     KC_TAB , KC_Y   , KC_O   , KC_U   , KC_K   , KC_QUOT,                                     KC_V   , KC_W   , KC_D   , KC_L   , KC_B   , KC_BSPC,
     CTL_ESC, KC_I   , KC_A   , KC_E   , KC_H   , KC_DOT ,                                     KC_G   , KC_S   , KC_T   , KC_R   , KC_N   , CTL_SCL,
     BRC    , KC_J   , KC_Q   , KC_COMM, KC_P   , KC_F   , XXXXXXX, KC_LALT, KC_LALT, XXXXXXX, KC_Z   , KC_C   , KC_M   , KC_SLSH, KC_X   , FKEYS  ,
                                ADJUST , NAV    , NUM    , KC_LSFT, KC_LCTL, KC_ENT , KC_SPC , KC_RSFT, SYM    , KC_APP
    ),

/* Base Layer: HDX
    x f m p b  - / . , q
  z r s n t g  ' a e i h j
    w c l d v  = u o y k

  Adaptive keys:
    + FM -> FL
    + PM -> PL
    + BM -> BL
    + XF -> XC
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |  Tab |   Y  |   O  |   U  |   Q  |   Z  |                              |   V  |   K  |   G  |   P  |   J  | Bspc |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |  Esc |   I  |   A  |   E  |   N  |   M  |                              |   D  |   H  |   T  |   S  |   R  |   -  |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * | Shift|   ;  |   /  |   '  |   ,  |   .  |      | Caps |  |  Alt |      |   B  |   C  |   W  |   F  |   X  | Shift|
 * `--------------------+------+------+------+   L  +------|  |------+ Space+------+------+------+--------------------'
 *                      |Adjust|  Num |  Nav |      | FKeys|  | Enter|      |  Brc |  Sym | Menu |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_HDX] = LAYOUT(
     KC_TAB , KC_QUOT, KC_O   , KC_U   , KC_Y   , KC_Z   ,                                     KC_V   , KC_K   , KC_G   , KC_C   , KC_W   , KC_BSPC,
     CTL_ESC, KC_I   , KC_A   , KC_E   , KC_N   , KC_M   ,                                     KC_D   , KC_H   , KC_T   , KC_S   , KC_R   , CTL_X  ,
     KC_LSFT, KC_DOT , KC_SLSH, KC_COMM, KC_MINS, KC_SCLN, XXXXXXX, KC_LALT, KC_LALT, XXXXXXX, KC_B   , KC_P   , KC_F   , KC_Q   , KC_J   , KC_LSFT,
                                ADJUST , NUM    , NAV    , KC_L   , FKEYS  , KC_ENT , KC_SPC , BRC    , SYM    , KC_APP
    ),

/* Base Layer: CATACV2
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |  Tab |   Y  |   O  |   U  |   Q  |   Z  |                              |   -  |   K  |   W  |   C  |   V  | Bspc |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |  Esc |   I  |   A  |   E  |   N  |   M  |                              |   D  |   H  |   T  |   S  |   R  |   X  |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * | Shift|   ;  |   /  |   '  |   ,  |   .  |      | Caps |  |  Alt |      |   B  |   P  |   F  |   G  |   J  | Shift|
 * `--------------------+------+------+------+   L  +------|  |------+ Space+------+------+------+--------------------'
 *                      |Adjust|  Num |  Nav |      | FKeys|  | Enter|      |  Brc |  Sym | Menu |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_CATACV2] = LAYOUT(
     KC_TAB , KC_Y   , KC_O   , KC_U   , KC_Q   , KC_Z   ,                                     KC_Y   , KC_K   , KC_W   , KC_C   , KC_V   , KC_BSPC,
     CTL_ESC, KC_I   , KC_A   , KC_E   , KC_N   , KC_M   ,                                     KC_D   , KC_H   , KC_T   , KC_S   , KC_R   , CTL_X  ,
     KC_LSFT, KC_SCLN, KC_SLSH, KC_QUOT, KC_COMM, KC_DOT , XXXXXXX, KC_LALT, KC_LALT, XXXXXXX, KC_B   , KC_P   , KC_F   , KC_G   , KC_J   , KC_LSFT,
                                ADJUST , NUM    , NAV    , KC_L   , FKEYS  , KC_ENT , KC_SPC , BRC    , SYM    , KC_APP
    ),

/*
 * Base Layer: SMMKJQ
    f l h v z ' w u o y
    s r n t k c d e a i
    x j b m q p g , . /
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |  Tab |   F  |   L  |   H  |   V  |   Z  |                              |   '  |   W  |   U  |   O  |   Y  | Bspc |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |  Esc |   S  |   R  |   N  |   T  |   K  |                              |   C  |   D  |   E  |   A  |   I  |   -  |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * | Shift|   X  |   J  |   B  |   M  |   Q  |      | Caps |  |  Alt |      |   P  |   G  |   ,  |   .  |   /  | Shift|
 * `--------------------+------+------+------+ Shift+------|  |------+ Space+------+------+------+--------------------'
 *                      |Adjust|  Num |  Nav |      | FKeys|  | Enter|      |  Brc |  Sym | Menu |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_SMMKJQ] = LAYOUT(
     KC_TAB , KC_F   , KC_L   , KC_H   , KC_V   , KC_Z   ,                                     KC_QUOT, KC_W   , KC_U   , KC_O   , KC_Y   , KC_BSPC,
     CTL_ESC, KC_S   , KC_R   , KC_N   , KC_T   , KC_K   ,                                     KC_C   , KC_D   , KC_E   , KC_A   , KC_I   , CTL_MNS,
     KC_LSFT, KC_X   , KC_J   , KC_B   , KC_M   , KC_Q   , XXXXXXX, KC_LALT, KC_LALT, XXXXXXX, KC_P   , KC_G   , KC_COMM, KC_DOT , KC_SLSH, KC_LSFT,
                                ADJUST , NUM    , NAV    , KC_LSFT, FKEYS  , KC_ENT , KC_SPC , BRC    , SYM    , KC_APP
    ),
/*
 * Base Layer: COLEMAK
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |  Tab |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |  Esc |   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  |   '  |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |  BRC |   Z  |   X  |   C  |   D  |   K  |      | Caps |  |  Alt |      |   V  |   H  |   /  |   .  |   ,  |  Esc |
 * `--------------------+------+------+------+ Shift+------|  |------+ Space+------+------+------+--------------------'
 *                      |Adjust|  Num |  Nav |      | FKeys|  | Enter|      |  Brc |  Sym | Menu |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_COLEMAK] = LAYOUT(
     KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   ,                                     KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_BSPC,
     CTL_ESC, KC_A   , KC_R   , KC_S   , KC_T   , KC_G   ,                                     KC_M   , KC_N   , KC_E   , KC_I   , KC_O   , CTL_QUT,
     BRC    , KC_Z   , KC_X   , KC_C   , KC_D   , KC_K   , XXXXXXX, KC_LALT, KC_LALT, XXXXXXX, KC_V   , KC_H   , KC_SLSH, KC_DOT , KC_COMM, KC_LSFT,
                                ADJUST , NUM    , NAV    , KC_LSFT, FKEYS  , KC_ENT , KC_SPC , _______, SYM    , KC_APP
    ),
/*
 * Base Layer: QWERTY
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |  Tab |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |  Esc |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   B  |   '  |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   ;  |      |      |  |      |      |   N  |   M  |   ,  |   .  |   /  | Shift|
 * `--------------------+------+------+------+ Enter+  Num |  |  Sym + Space+------+------+------+--------------------'
 *                      |Adjust| FKeys|  Nav | /Alt |      |  |      | /Alt |  Lang| Menu |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
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
 * |      |      |      |      |      |      |                              |      |   {  |   }  |   ,  |   $  |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      | Shift|  Alt | Ctrl |  Gui |      |                              |   -  |   (  |   )  |   [  |  ]   |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  |      |      |   _  |   <  |   >  |   /  |   *  |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_BRACKET] = LAYOUT(
      _______, KC_DLR , KC_COMM, KC_LCBR, KC_RCBR, _______,                                     _______, KC_LCBR, KC_RCBR, KC_COMM, KC_DLR , _______,
      _______, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_MINS,                                     KC_MINS, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, _______,
      _______, KC_ASTR, KC_SLSH, KC_LABK, KC_RABK, KC_UNDS, _______, _______, _______, _______, KC_UNDS, KC_LABK, KC_RABK, KC_SLSH, KC_ASTR, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
      _______, SE_T   , SE_ZERO, SE_J   , SE_SPC , SE_DASH, _______, _______, _______, _______, KC_PAUS, KC_PGUP, SE_J   , KC_PGDN, _______, _______,
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
      _______, _______, SMMKJQ , MTGAP  , _______, _______,                                    _______, _______, MTGAP  , SMMKJQ , _______, _______,
      _______, HDX    , QWERTY , COLEMAK, CATACV2, _______,                                    _______, CATACV2, COLEMAK, QWERTY , HDX    , _______,
      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),
};

uint16_t copy_paste_time;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool sw_win_active = false;

#define ADAPTIVE_TERM 300

bool process_adaptive_key(uint16_t keycode, const keyrecord_t *record) {
    bool return_state = true;
    static uint16_t prior_keycode = KC_NO;
    static uint16_t prior_keydown = 0;

    if (record->event.pressed) {
        keycode = keycode & 0xFF; // ignore all mods? or just shift?
        if ((timer_elapsed(prior_keydown) < ADAPTIVE_TERM)) {
            switch (keycode) {
            case KC_M:
                switch (prior_keycode) {
                case KC_F: // FM -> FL
                case KC_P: // PM -> PL
                case KC_B: // BM -> BL
                    tap_code(KC_L);
                    return_state = false;
                }
                break;
            case KC_F:
                switch (prior_keycode) {
                case KC_X: //XF -> XC
                    tap_code(KC_C);
                    return_state = false;
                }
                break;
            }
        }
        prior_keycode = keycode;
        prior_keydown = timer_read();
    }
    return return_state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    /* if (!process_adaptive_key(keycode, record)) { */
    /*     return false; */
    /* } */

#ifdef CONSOLE_ENABLE
    /* uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count); */
#endif 

    update_oneshot(&os_shft_state, KC_LSFT, OS_SFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTL, keycode, record);
    update_oneshot(&os_alt_state , KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_cmd_state , KC_LGUI, OS_GUI, keycode, record);

    /* swapper must be after oneshot other wise there can be lingering mods */
    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, SW_RWIN, SW_WINA, keycode, record);

    switch (keycode) {
    case SP_TH:
        if (record->event.pressed) {
            if ( get_mods() & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                send_string("Th");
            } else {
                del_mods(MOD_MASK_SHIFT);
                send_string("th");
            }
            return false;
        }
        break;
    case SP_ION:
        if (record->event.pressed) {
            send_string("ion");
            return false;
        }
        break;
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
    case SE_DASH:
        if (record->event.pressed) {
            tap_code16(C(KC_BSLS));
            return false;
        }
        break;
    case KC_CCCV:  // One key copy/paste
        if (record->event.pressed) {
            copy_paste_time = timer_read();
        } else {
            if (timer_elapsed(copy_paste_time) > TAPPING_TERM) {  // Hold, copy
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
            tap_code16(LCTL(KC_LEFT));
            break;
        case 0b10:
            tap_code16(LCTL(KC_RGHT));
            break;
        default:
            break;
        }
    } else if (IS_LAYER_ON(_BRACKET)) {
        switch (encoder_side_n_dir) {
        case 0b01:
            tap_code16(LCTL(KC_LEFT));
            break;
        case 0b00:
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

/* void keyboard_post_init_user(void) { */
/*   // Customise these values to desired behaviour */
/*   debug_enable=true; */
/*   debug_matrix=true; */
/*   //debug_keyboard=true; */
/*   //debug_mouse=true; */
/* } */
