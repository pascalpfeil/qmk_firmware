#include "sadekbaroudi.h"

#define USER_SUPER_ALT_TAB_TIMEOUT 500

#ifdef PIMORONI_TRACKBALL_ENABLE
#include "drivers/sensors/pimoroni_trackball.h"
#include "pointing_device.h"
#include "color.h"
#endif

userspace_config_t userspace_config;
bool is_caps_lock_on;
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

void handle_caps_lock_change(void) {
#if defined(RGBLIGHT_ENABLE) // We only do this because we want the layer color to change
    layer_state_set_rgb_light(layer_state);
#endif  // RGBLIGHT_ENABLE
}

// Leader key combos - TODO move into another file?
#if defined(LEADER_ENABLE)
LEADER_EXTERNS();

void matrix_scan_leader_key(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_Q) {
      // Anything you can do in a macro.
      SEND_STRING("QMK is awesome.");
    }

    // Time shortcuts
    SEQ_TWO_KEYS(KC_H, KC_SLSH) {
      SEND_STRING("1:00");
    }
    SEQ_TWO_KEYS(KC_COMM, KC_SLSH) {
      SEND_STRING("2:00");
    }
    SEQ_TWO_KEYS(KC_DOT, KC_SLSH) {
      SEND_STRING("3:00");
    }
    SEQ_TWO_KEYS(KC_N, KC_SLSH) {
      SEND_STRING("4:00");
    }
    SEQ_TWO_KEYS(KC_E, KC_SLSH) {
      SEND_STRING("5:00");
    }
    SEQ_TWO_KEYS(KC_I, KC_SLSH) {
      SEND_STRING("6:00");
    }
    SEQ_TWO_KEYS(KC_L, KC_SLSH) {
      SEND_STRING("7:00");
    }
    SEQ_TWO_KEYS(KC_U, KC_SLSH) {
      SEND_STRING("8:00");
    }
    SEQ_TWO_KEYS(KC_Y, KC_SLSH) {
      SEND_STRING("9:00");
    }
    SEQ_THREE_KEYS(KC_H, KC_SLSH, KC_SLSH) {
      SEND_STRING("10:00");
    }
    SEQ_THREE_KEYS(KC_H, KC_H, KC_SLSH) {
      SEND_STRING("11:00");
    }
    SEQ_THREE_KEYS(KC_H, KC_COMM, KC_SLSH) {
      SEND_STRING("12:00");
    }
    SEQ_TWO_KEYS(KC_H, KC_DOT) {
      SEND_STRING("1:30");
    }
    SEQ_TWO_KEYS(KC_COMM, KC_DOT) {
      SEND_STRING("2:30");
    }
    SEQ_TWO_KEYS(KC_DOT, KC_DOT) {
      SEND_STRING("3:30");
    }
    SEQ_TWO_KEYS(KC_N, KC_DOT) {
      SEND_STRING("4:30");
    }
    SEQ_TWO_KEYS(KC_E, KC_DOT) {
      SEND_STRING("5:30");
    }
    SEQ_TWO_KEYS(KC_I, KC_DOT) {
      SEND_STRING("6:30");
    }
    SEQ_TWO_KEYS(KC_L, KC_DOT) {
      SEND_STRING("7:30");
    }
    SEQ_TWO_KEYS(KC_U, KC_DOT) {
      SEND_STRING("8:30");
    }
    SEQ_TWO_KEYS(KC_Y, KC_DOT) {
      SEND_STRING("9:30");
    }
    SEQ_THREE_KEYS(KC_H, KC_SLSH, KC_DOT) {
      SEND_STRING("10:30");
    }
    SEQ_THREE_KEYS(KC_H, KC_H, KC_DOT) {
      SEND_STRING("11:30");
    }
    SEQ_THREE_KEYS(KC_H, KC_COMM, KC_DOT) {
      SEND_STRING("12:30");
    }

    // 
    SEQ_TWO_KEYS(KC_D, KC_D) {
      SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
      SEND_STRING("https://start.duckduckgo.com\n");
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }
  }
}
#endif

__attribute__((weak)) void keyboard_pre_init_keymap(void) {}

void keyboard_pre_init_user(void) {
    userspace_config.raw = eeconfig_read_user();

    // hack for a weird issue where userspace_config.val gets set to 0 on keyboard restart
    userspace_config.val = 255;
    
    keyboard_pre_init_keymap();
}
// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps
__attribute__((weak)) void matrix_init_keymap(void) {}

// Call user matrix init, set default RGB colors and then
// call the keymap's init function
void matrix_init_user(void) {
    matrix_init_keymap();
}

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
    is_caps_lock_on = false;
    #if defined(PIMORONI_TRACKBALL_ENABLE) && !defined(RGBLIGHT_ENABLE)
    trackball_set_rgbw(RGB_BLUE, 0x00);
    #endif
#if defined(RGBLIGHT_ENABLE)
    keyboard_post_init_rgb_light();
#endif
// #if defined(RGB_MATRIX_ENABLE)
//     keyboard_post_init_rgb_matrix();
// #endif
    keyboard_post_init_keymap();
}

__attribute__((weak)) void shutdown_keymap(void) {}

void rgb_matrix_update_pwm_buffers(void);

void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(1);
    rgblight_setrgb_red();
#endif
// #ifdef RGB_MATRIX_ENABLE
//     rgb_matrix_set_color_all(0xFF, 0x00, 0x00);
//     rgb_matrix_update_pwm_buffers();
// #endif
    shutdown_keymap();
}

__attribute__((weak)) void suspend_power_down_keymap(void) {}

void suspend_power_down_user(void) { suspend_power_down_keymap(); }

__attribute__((weak)) void suspend_wakeup_init_keymap(void) {}

void suspend_wakeup_init_user(void) { suspend_wakeup_init_keymap(); }

__attribute__((weak)) void matrix_scan_keymap(void) {}

// No global matrix scan code, so just run keymap's matrix
// scan function
void matrix_scan_user(void) {
    static bool has_ran_yet;
    if (!has_ran_yet) {
        has_ran_yet = true;
        startup_user();
    }

#if defined(RGBLIGHT_ENABLE)
    matrix_scan_rgb_light();
#endif  // RGBLIGHT_ENABLE

    // We do this in matrix scan in case there are two keyboards connected and we
    // need to make sure this keyboard is aware
    led_t led_state = host_keyboard_led_state();
    if (led_state.caps_lock != is_caps_lock_on) {
        is_caps_lock_on = led_state.caps_lock;
        handle_caps_lock_change();
    }

// #if defined(RGB_MATRIX_ENABLE)
//     matrix_scan_rgb_matrix();
// #endif

#if defined(LEADER_ENABLE)
    matrix_scan_leader_key();
#endif

    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > USER_SUPER_ALT_TAB_TIMEOUT) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }

    matrix_scan_keymap();
}

void press_super_alt_tab(bool shift) {
    if (shift) {
        register_code(KC_LSHIFT);
    }
    if (!is_alt_tab_active) {
        is_alt_tab_active = true;
        register_code(KC_LALT);
    }
    alt_tab_timer = timer_read();
    tap_code(KC_TAB);
    if (shift) {
        unregister_code(KC_LSHIFT);
    }
}

__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) { return state; }

// on layer change, no matter where the change was initiated
// Then runs keymap's layer change check
layer_state_t layer_state_set_user(layer_state_t state) {
#if defined(RGBLIGHT_ENABLE)
    state = layer_state_set_rgb_light(state);
#endif  // RGBLIGHT_ENABLE
    return layer_state_set_keymap(state);
}

__attribute__((weak)) layer_state_t default_layer_state_set_keymap(layer_state_t state) { return state; }

// Runs state check and changes underglow color and animation
layer_state_t default_layer_state_set_user(layer_state_t state) {
    state = default_layer_state_set_keymap(state);
    return state;
}

__attribute__((weak)) void led_set_keymap(uint8_t usb_led) {}

// Any custom LED code goes here.
// So far, I only have keyboard specific code,
// So nothing goes here.
void led_set_user(uint8_t usb_led) { led_set_keymap(usb_led); }

__attribute__((weak)) void eeconfig_init_keymap(void) {}

void eeconfig_init_user(void) {
    userspace_config.raw              = 0;
    userspace_config.rgb_base_layer_override = false;
    userspace_config.rgb_layer_change = true;
    #ifdef RGBLIGHT_ENABLE
    userspace_config.mode = RGBLIGHT_MODE_STATIC_LIGHT;
    #endif
    userspace_config.hue = 167; // BLUE
    userspace_config.sat = 255;
    userspace_config.val = 255;
    userspace_config.speed = 1;
    eeconfig_update_user(userspace_config.raw);
    eeconfig_init_keymap();
    keyboard_init();
}

bool hasAllBitsInMask(uint8_t value, uint8_t mask) {
    value &= 0xF;
    mask &= 0xF;

    return (value & mask) == mask;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // I always type the shift keys too fast, so tapping term of 200 is way too high
        case LSFT_T(KC_T):
        case RSFT_T(KC_N):
            return 75;
        default:
            return TAPPING_TERM;
    }
}


// This was added to deal with this issue:
// * https://www.reddit.com/r/olkb/comments/mwf5re/help_needed_controlling_individual_rgb_leds_on_a/
// * https://github.com/qmk/qmk_firmware/issues/12037
#ifdef SPLIT_KEYBOARD
void housekeeping_task_user(void) {
    static layer_state_t old_layer_state = 0;
    if (!is_keyboard_master() && old_layer_state != layer_state) {
        old_layer_state = layer_state;
        layer_state_set_user(layer_state);
    }
}
#endif