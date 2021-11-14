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
    _BASE,
    _LAYER2,
    _LAYER3,
    _LAYER4,
    LAYER_COUNT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F,
        KC_G, KC_H, KC_I),

    [_LAYER2] = LAYOUT(
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F,
        KC_G, KC_H, KC_I),

    [_LAYER3] = LAYOUT(
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F,
        KC_G, KC_H, KC_I),

    [_LAYER4] = LAYOUT(
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F,
        KC_G, KC_H, KC_I),
};

bool encoder_update_user(uint8_t index, bool clockwise)
{
    const uint8_t current_layer = get_highest_layer(layer_state);
    if (clockwise)
    {
        layer_move((current_layer + 1) % LAYER_COUNT);
    }
    else
    {
        layer_move((current_layer + LAYER_COUNT - 1) % LAYER_COUNT);
    }
    return true;
}

#ifdef OLED_ENABLE
void oled_task_user(void)
{
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state))
    {
    case _BASE:
        oled_write_ln_P(PSTR("Base"), false);
        break;
    case _LAYER2:
        oled_write_ln_P(PSTR("Layer2"), false);
        break;
    case _LAYER3:
        oled_write_ln_P(PSTR("Layer3"), false);
        break;
    case _LAYER4:
        oled_write_ln_P(PSTR("Layer4"), false);
        break;
    default:
        oled_write_ln_P(PSTR("Undefined"), false);
    }
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}
#endif
