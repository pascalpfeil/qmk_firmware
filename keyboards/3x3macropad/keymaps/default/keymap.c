/* Copyright 2021 Simon S.
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

// Defines names for use in layer keycodes and the keymap
enum layer_names
{
    _MEDIA,
    _RGB,
    _LAYER3,
    _LAYER4,
    LAYER_COUNT,
};

enum custom_keycodes
{
    NEXT_LAYER = SAFE_RANGE,
};

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MEDIA] = LAYOUT_OLED(
        KC_MUTE,
        NEXT_LAYER, KC_NO, KC_NO,
        KC_MPRV, KC_MPLY, KC_MNXT),

    [_RGB] = LAYOUT_OLED(
        RGB_TOG,
        NEXT_LAYER, RGB_VAD, RGB_VAI,
        RGB_M_P, RGB_RMOD, RGB_MOD),

    [_LAYER3] = LAYOUT_OLED(
        KC_NO,
        NEXT_LAYER, RGB_VAD, KC_NO,
        KC_NO, KC_NO, KC_NO),

    [_LAYER4] = LAYOUT_OLED(
        KC_NO,
        NEXT_LAYER, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
    case NEXT_LAYER:
        if (record->event.pressed)
        {
            layer_move((get_highest_layer(layer_state) + 1) % LAYER_COUNT);
        }
        return false;
    default:
        return true;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise)
{
    switch (get_highest_layer(layer_state))
    {
    case _MEDIA:
        tap_code(clockwise ? KC_VOLU : KC_VOLD);
        break;
    case _RGB:
        if (clockwise)
            rgblight_increase_hue();
        else
            rgblight_decrease_hue();
        break;
    case _LAYER3:
        tap_code16(clockwise ? C(KC_Y) : C(KC_Z));
        break;
    case _LAYER4:
        if (clockwise)
        {
            if (!is_alt_tab_active)
            {
                is_alt_tab_active = true;
                register_code(KC_LALT);
            }
            alt_tab_timer = timer_read();
            tap_code16(KC_TAB);
        }
        else
        {
            if (!is_alt_tab_active)
            {
                is_alt_tab_active = true;
                register_code(KC_LALT);
            }
            alt_tab_timer = timer_read();
            tap_code16(S(KC_TAB));
        }

        break;
    }

    return true;
}

void matrix_scan_user(void)
{
    if (is_alt_tab_active)
    {
        if (timer_elapsed(alt_tab_timer) > 500)
        {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}

#ifdef OLED_ENABLE
void oled_task_user(void)
{
    // Host Keyboard Layer Status
    switch (get_highest_layer(layer_state))
    {
    case _MEDIA:
        oled_write_ln_P(PSTR("VOL+    MUTE     VOL-"
                             "LAYER+               "
                             "PREV  PLAY/PAUSE NEXT"),
                        false);
        break;
    case _RGB:
        oled_write_ln_P(PSTR("HUE+   RGB_TOG   HUE-"
                             "LAYER+  VAL-    VAL+ "
                             "PLAIN   MODE-   MODE+"),
                        false);
        break;
    case _LAYER3:
        oled_write_ln_P(PSTR("UNDO             REDO"
                             "LAYER+               "
                             "                     "),
                        false);
        break;
    case _LAYER4:
        oled_write_ln_P(PSTR("WINDOW+       WINDOW-"
                             "LAYER+               "
                             "                     "),
                        false);
        break;
    }
}
#endif
