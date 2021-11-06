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
#define DEBOUNCE 0

// Lets you roll mod-tap keys
#define IGNORE_MOD_TAP_INTERRUPT

#undef COMBO_TERM
#undef COMBO_LEN
#define COMBO_TERM 35
#define COMBO_MUST_TAP_PER_COMBO
#define COMBO_TERM_PER_COMBO
// All combos are specified from the base layer, saves space
#define COMBO_ONLY_FROM_LAYER 0

// Match Tick For EC11 default value 4 will skip one tick.
#define ENCODER_RESOLUTION 2

// Using experimental serial communication speed
#define SELECT_SOFT_SERIAL_SPEED 0

// Assume always connected both split keyboard side.
#define SPLIT_MAX_CONNECTION_ERRORS 0
