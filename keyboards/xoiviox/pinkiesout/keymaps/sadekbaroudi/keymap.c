/* Copyright 2021 Sadek Baroudi
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

// Uncomment to set up WPM
//char wpm_as_str[8];

/*
 * The `LAYOUT_pinkiesout_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */

// clang-format off
#define LAYOUT_pinkiesout_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
    KC_ESC,    KC_1,           KC_2,           KC_3,           KC_4,                KC_5,                   KC_LPRN,               KC_RPRN,            KC_6,                  KC_7,               KC_8,             KC_9,           KC_0,            KC_BSPC, \
    KC_TAB,    K01,            K02,            K03,            LT(_FUNCTION, K04),  K05,                    ywfulp,                wyfupl,             K06,                   LT(_FUNCTION, K07), LT(_WINNAV,K08),  K09,            K0A,             KC_BSLS, \
    KC_CAPS,   LCTL_T(K11),    LGUI_T(K12),    LALT_T(K13),    LSFT_T(K14),         K15,                    ywfulp,                wyfupl,             LT(_MOUSE, K16),       RSFT_T(K17),        RALT_T(K18),      RGUI_T(K19),    RCTL_T(K1A),     KC_QUOT, \
    KC_LSFT,   K21,            K22,            K23,            K24,                 K25,                    ywfulp,                wyfupl,             K26,                   K27,                K28,              K29,            K2A,             KC_ENT, \
                               KC_LCTL,        KC_LGUI,        KC_DEL,              LT(_NAVIGATION,KC_ENT), LT(_FUNCTION,KC_TAB),  LT(_MEDIA,KC_BSPC), LT(_SYMBOLS,KC_SPACE), KC_QUOT,            KC_RGUI,          KC_RCTL \
    )

/* Re-pass though to allow templates to be used */
#define LAYOUT_pinkiesout_base_wrapper(...)       LAYOUT_pinkiesout_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_pinkiesout_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [_COLEMAK] = LAYOUT_pinkiesout_base_wrapper(
        ______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________,
        ______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________,
        ______________COLEMAK_MOD_DH_L3____________, ______________COLEMAK_MOD_DH_R3____________
    ),

    [_ISRT] = LAYOUT_pinkiesout_base_wrapper(
        _________________ISRT_L1________________, _________________ISRT_R1________________,
        _________________ISRT_L2________________, _________________ISRT_R2________________,
        _________________ISRT_L3________________, _________________ISRT_R3________________
    ),

    [_NAVIGATION] = LAYOUT_wrapper(
        _______,       _______,       _______,       _______,       _______,       _______,       _______,                 _______,       _______,       _______,       _______,       _______,       _______,       _______,
        _______,                   ________________NAVIGATION_1_______________,                   _______,                 _______,                   _________________NUMPAD_1__________________,                   _______,
        _______,                   ________________NAVIGATION_2_______________,                   _______,                 _______,                   _________________NUMPAD_2__________________,                   _______,
        _______,                   ________________NAVIGATION_3_______________,                   _______,                 _______,                   _________________NUMPAD_3__________________,                   _______,
                                      _______,       _______,       _______,       _______,       KC_TAB,                  KC_BSPC,       KC_SPACE,       KC_DOT,       _______,       _______
    ),

    [_SYMBOLS] = LAYOUT_wrapper(
        _______,       _______,       _______,       _______,       _______,       _______,       _______,                 _______,       _______,       _______,       _______,       _______,       _______,       _______,
        _______,                   ________________SYMBOLS_L1_________________,                   _______,                 _______,                   ________________SYMBOLS_R1_________________,                   _______,
        _______,                   ________________SYMBOLS_L2_________________,                   _______,                 _______,                   ________________SYMBOLS_R2_________________,                   _______,
        _______,                   ________________SYMBOLS_L3_________________,                   _______,                 _______,                   ________________SYMBOLS_R3_________________,                   _______,
                                      _______,       _______,       _______,       KC_ENT,        KC_DEL,                  KC_BSPC,       _______,       _______,       _______,       _______
    ),

    [_FUNCTION] = LAYOUT_wrapper(
        _______,       _______,       _______,       _______,       _______,       _______,       _______,                 _______,       _______,       _______,       _______,       _______,       _______,       _______,
        _______,                   ________________SHIFTNAV_1_________________,                   _______,                 _______,                   ________________FUNCTION_1_________________,                   _______,
        _______,                   ________________SHIFTNAV_2_________________,                   _______,                 _______,                   ________________FUNCTION_2_________________,                   _______,
        _______,                   ________________SHIFTNAV_3_________________,                   _______,                 _______,                   ________________FUNCTION_3_________________,                   _______,
                                      _______,       _______,       _______,       _______,       _______,                 N_DEL_LINE,    KC_SPACE,      _______,       _______,       _______
    ),

    [_MEDIA] = LAYOUT_wrapper(
        _______,       _______,       _______,       _______,       _______,       _______,       _______,                 _______,       _______,       _______,       _______,       _______,       _______,       _______,
        _______,                   ___________________RGB_1___________________,                   _______,                 _______,                   _________________MACROS_1__________________,                   _______,
        _______,                   ___________________RGB_2___________________,                   _______,                 _______,                   _________________MACROS_2__________________,                   _______,
        _______,                   ___________________RGB_3___________________,                   _______,                 _______,                   _________________MACROS_3__________________,                   _______,
                                      _______,       _______,       _______,       _______,       _______,                 _______,       _______,       _______,       _______,       _______
    ),
    
    [_MOUSE] = LAYOUT_wrapper(
        _______,       _______,       _______,       _______,       _______,       _______,       _______,                 _______,       _______,       _______,       _______,       _______,       _______,       _______,
        _______,                   __________________MOUSE_1__________________,                   _______,                 _______,                   ___________________BLANK___________________,                   _______,
        _______,                   __________________MOUSE_2__________________,                   _______,                 _______,                   ___________________BLANK___________________,                   _______,
        _______,                   __________________MOUSE_3__________________,                   _______,                 _______,                   ___________________BLANK___________________,                   _______,
                                      _______,       _______,       _______,       KC_MS_BTN1,    KC_MS_BTN3,              KC_MS_BTN3,    KC_MS_BTN2,    _______,       _______,       _______
    ),

    [_WINNAV] = LAYOUT_wrapper(
        _______,       _______,       _______,       _______,       _______,       _______,       _______,                 _______,       _______,       _______,       _______,       _______,       _______,       _______,
        _______,                   __________________WIN_NAV_1________________,                   _______,                 _______,                   ___________________BLANK___________________,                   _______,
        _______,                   __________________WIN_NAV_2________________,                   _______,                 _______,                   ___________________BLANK___________________,                   _______,
        _______,                   ___________________BLANK___________________,                   _______,                 _______,                   ___________________BLANK___________________,                   _______,
                                      _______,       _______,       _______,       _______,       _______,                 _______,       _______,       _______,       _______,       _______
    )

};


#ifdef OLED_DRIVER_ENABLE


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
      return OLED_ROTATION_180;
} 


// Commenting out logo as it takes up a lot of space :(
static void render_logo(void) {
    // pinkiesout logo, 128x64px
    static const char PROGMEM pinkiesout_logo[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 
    0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x8f, 0x07, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x41, 0x41, 0x41, 
    0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 
    0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x07, 0x8f, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0x8f, 0x07, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 
    0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xf8, 0xf8, 
    0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 
    0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0x7f, 0x3f, 0x3e, 0x3e, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 
    0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 
    0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xc0, 
    0xc0, 0xc0, 0xc1, 0xcd, 0xcd, 0xcc, 0xc0, 0xc1, 0xe1, 0xe3, 0xff, 0xff, 0xef, 0xc1, 0xc1, 0xc1, 
    0xc4, 0xc4, 0xc4, 0xe0, 0xc1, 0xc1, 0xc1, 0xc3, 0xff, 0xff, 0xc1, 0xc0, 0xc0, 0xc1, 0xf9, 0xfd, 
    0xfc, 0xfc, 0xff, 0xe3, 0xe1, 0xc1, 0xc1, 0xcd, 0xcc, 0xcc, 0xcd, 0xc1, 0xc1, 0xe1, 0xe3, 0xff, 
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1, 0xcd, 0xcd, 0xcc, 0xc0, 0xc1, 0xe1, 0xe3, 0xff, 0xff, 0xe3, 
    0xe1, 0xc1, 0xc1, 0xcd, 0xcc, 0xcc, 0xcd, 0xc1, 0xc1, 0xe1, 0xe3, 0xff, 0xff, 0xc1, 0xc0, 0xc0, 
    0xc1, 0xf9, 0xfd, 0xfc, 0xfc, 0xff, 0xe3, 0xe1, 0xc1, 0xc0, 0xcc, 0xcd, 0xcd, 0xc9, 0xc0, 0xc0, 
    0xc0, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff

};
    oled_write_raw_P(pinkiesout_logo, sizeof(pinkiesout_logo));

}


/*
static void render_status(void) {
  oled_write_P(PSTR("pinkiesout\n"), false);
  // Uncomment to set up WPM
  //  sprintf(wpm_as_str, "WPM %03d", get_current_wpm());
  //  oled_write(wpm_as_str,false);
  led_t led_state = host_keyboard_led_state();
  oled_write_P(PSTR("Caps: "), false);
  oled_write_P(led_state.caps_lock ? PSTR("on ") : PSTR("off"), false);
  oled_write_P(PSTR("\n"),false);
  switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Qwerty "), false);
            break;
        case _COLEMAK:
            oled_write_P(PSTR("Colemak"), false);
            break;
        case _ISRT:
            oled_write_P(PSTR("Workman"), false);
            break;
        case _NAVIGATION:
            oled_write_P(PSTR("Nav    "), false);
            break;
        case _SYMBOLS:
            oled_write_P(PSTR("Symbols"), false);
            break;
        case _FUNCTION:
            oled_write_P(PSTR("Function"), false);
            break;
        case _MEDIA:
            oled_write_P(PSTR("Media  "), false);
            break;
        case _MOUSE:
            oled_write_P(PSTR("Mouse  "), false);
            break;
        case _WINNAV:
            oled_write_P(PSTR("Win nav"), false);
            break;

        default:
            oled_write_P(PSTR("Unkn "), false);
            break;
    }
}
*/

/*
static void render_logo_text(void) {
    oled_write_P(PSTR("pinkiesout"), false);
}
*/

void oled_task_user(void) {
    // If you don't want to display the logo, switch
    if (false) {
        //render_status();
    } else if (true) {
        render_logo();
    } else {
        //render_logo_text();
    }
}

#endif
