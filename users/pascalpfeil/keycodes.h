#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

enum my_keycodes {
    MY_COPY = SAFE_RANGE,
    MY_PSTE,
    MY_UNDO,
    MY_SRCH,
    MY_BGNW,
    MY_ENDW,
};

inline bool is_windows_mode(void) {
    return !keymap_config.swap_lalt_lgui;
}

inline bool tap_os_specific(uint16_t windows_modifier, uint16_t mac_modifier, uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uint16_t modifier = is_windows_mode() ? windows_modifier : mac_modifier;
        tap_code16(modifier | keycode);
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MY_COPY:
            return tap_os_specific(QK_LCTL, QK_LGUI, KC_C, record);
        case MY_PSTE:
            return tap_os_specific(QK_LCTL, QK_LGUI, KC_V, record);
        case MY_UNDO:
            return tap_os_specific(QK_LCTL, QK_LGUI, KC_Z, record);
        case MY_SRCH:
            return tap_os_specific(QK_LCTL, QK_LGUI, KC_F, record);
        case MY_BGNW:
            return tap_os_specific(QK_LCTL, QK_LALT, KC_LEFT, record);
        case MY_ENDW:
            return tap_os_specific(QK_LCTL, QK_LALT, KC_RIGHT, record);
        default:
            return true;
    }
}

#endif
