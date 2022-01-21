/* Copyright 2015-2017 Jack Humbert
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

#include "sadekbaroudi.h"
#include QMK_KEYBOARD_H
#include "muse.h"

#ifndef UNICODE_ENABLE
#    define UC(x) KC_NO
#endif


// clang-format off
#define LAYOUT_ortho_5x12_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_ortho_5x12_wrapper( \
        _______,        KC_1,           KC_2,           KC_3,           KC_4,                   KC_5,                 KC_6,                  KC_7,                  KC_8,              KC_9,           KC_0,            _______, \
        _______,        K01,            K02,            K03,            LT(_FUNCTION, K04),     K05,                  K06,                   LT(_FUNCTION, K07),    LT(_WINNAV,K08),   K09,            K0A,             _______, \
        _______,        LCTL_T(K11),    LGUI_T(K12),    LALT_T(K13),    LSFT_T(K14),            K15,                  LT(_MOUSE, K16),       RSFT_T(K17),           RALT_T(K18),       RGUI_T(K19),    RCTL_T(K1A),     _______, \
        _______,        K21,            K22,            K23,            K24,                    K25,                  K26,                   K27,                   K28,               K29,            K2A,             _______, \
        _______,        _______,        _______,        KC_DEL,         LT(_NAVIGATION,KC_ENT), LT(_FUNCTION,KC_TAB), LT(_MEDIA,KC_BSPC), LT(_SYMBOLS,KC_SPACE),    KC_QUOT,           _______,        _______,         _______ \
    )

/* Re-pass though to allow templates to be used */
#define LAYOUT_ortho_5x12_base_wrapper(...)       LAYOUT_ortho_5x12_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_ALPHA_ALT] = LAYOUT_ortho_5x12_base_wrapper(
        _________________ALPHA_ALT_L1_________________, _________________ALPHA_ALT_R1_________________,
        _________________ALPHA_ALT_L2_________________, _________________ALPHA_ALT_R2_________________,
        _________________ALPHA_ALT_L3_________________, _________________ALPHA_ALT_R3_________________
    ),

    [_ALPHA] = LAYOUT_ortho_5x12_base_wrapper(
        __________________ALPHA_L1____________________, __________________ALPHA_R1____________________,
        __________________ALPHA_L2____________________, __________________ALPHA_R2____________________,
        __________________ALPHA_L3____________________, __________________ALPHA_R3____________________
    ),

    [_NAVIGATION] = LAYOUT_wrapper(
        _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
        _______, ________________NAVIGATION_1_______________, _________________NUMPAD_1__________________, _______,
        _______, ________________NAVIGATION_2_______________, _________________NUMPAD_2__________________, _______,
        _______, ________________NAVIGATION_3_______________, _________________NUMPAD_3__________________, _______,
        _______, _______, _______, _______, _______, KC_TAB, KC_BSPC, KC_SPACE, KC_DOT, _______, _______, _______
    ),

    [_SYMBOLS] = LAYOUT_wrapper(
        _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
        _______, ________________SYMBOLS_L1_________________, ________________SYMBOLS_R1_________________, _______,
        _______, ________________SYMBOLS_L2_________________, ________________SYMBOLS_R2_________________, _______,
        _______, ________________SYMBOLS_L3_________________, ________________SYMBOLS_R3_________________, _______,
        _______, _______, _______, _______, KC_ENT, KC_DEL,   KC_BSPC, _______, _______, _______, _______, _______
    ),

    [_FUNCTION] = LAYOUT_wrapper(
        _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
        _______, ________________SHIFTNAV_1_________________, ________________FUNCTION_1_________________, _______,
        _______, ________________SHIFTNAV_2_________________, ________________FUNCTION_2_________________, _______,
        _______, ________________SHIFTNAV_3_________________, ________________FUNCTION_3_________________, _______,
        _______, ___________________BLANK___________________, N_DEL_LINE, KC_SPACE, _______, _______, _______, _______
    ),

    [_MEDIA] = LAYOUT_wrapper(
        _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
        _______, ___________________RGB_1___________________, _________________MACROS_1__________________, _______,
        _______, ___________________RGB_2___________________, _________________MACROS_2__________________, _______,
        _______, ___________________RGB_3___________________, _________________MACROS_3__________________, _______,
        _______, ___________________BLANK___________________, ___________________BLANK___________________, _______
    ),
    
    [_MOUSE] = LAYOUT_wrapper(
        _______,      ___________________BLANK___________________,  ___________________BLANK___________________,       _______,
        _______,      __________________MOUSE_1__________________,  ___________________BLANK___________________,       _______,
        _______,      __________________MOUSE_2__________________,  ___________________BLANK___________________,       _______,
        _______,      __________________MOUSE_3__________________,  ___________________BLANK___________________,       _______,
        _______, _______, _______, _______, KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN3, KC_MS_BTN2, _______, _______, _______, _______
    ),

    [_WINNAV] = LAYOUT_wrapper(
        _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
        _______, __________________WIN_NAV_1________________, ___________________BLANK___________________, _______,
        _______, __________________WIN_NAV_2________________, ___________________BLANK___________________, _______,
        _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
        _______, ___________________BLANK___________________, ___________________BLANK___________________, _______
    )

};

