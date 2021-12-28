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

#pragma once

#undef DEBOUNCE
#define DEBOUNCE 30

// Lets you roll mod-tap keys
#define IGNORE_MOD_TAP_INTERRUPT

#undef COMBO_TERM
#undef COMBO_LEN
#define COMBO_TERM 40
#define COMBO_MUST_TAP_PER_COMBO
#define COMBO_TERM_PER_COMBO
// All combos are specified from the base layer, saves space
#define COMBO_ONLY_FROM_LAYER 0

// Match Tick For EC11 default value 4 will skip one tick.
#define ENCODER_RESOLUTION 2

// Using experimental serial communication speed
#define SELECT_SOFT_SERIAL_SPEED 1

// Assume always connected both split keyboard side.
#define SPLIT_MAX_CONNECTION_ERRORS 0

#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 4

#define SERIAL_USE_MULTI_TRANSACTION
#define CRC8_USE_TABLE

/* #define DEBUG_MATRIX_SCAN_RATE */


/* #ifdef RGBLIGHT_ENABLE */
/* #    define RGBLIGHT_ANIMATIONS */
/* #    define RGBLIGHT_HUE_STEP  8 */
/* #    define RGBLIGHT_SAT_STEP  8 */
/* #    define RGBLIGHT_VAL_STEP  8 */
/* #    define RGBLIGHT_LIMIT_VAL 150 */
/* #endif */

/* #define NO_ACTION_ONESHOT */
/* #define NO_ACTION_TAPPING */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define OLED_DISPLAY_128X64

/* #define RGBLIGHT_EFFECT_BREATHING */
/* #define RGBLIGHT_EFFECT_RAINBOW_SWIRL */
/* #define RGBLIGHT_LED_MAP {0,1,2,9,8,7,4,3,5,6,19,18,17,10,11,12,15,16,14,13} */

#define TAPPING_TOGGLE 2
