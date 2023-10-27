#include QMK_KEYBOARD_H
// #include "math.h"

// enum layers {
//     _QWERTY,
//     _LOWER,
//     _RAISE,
// };

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  DRAG_SCROLL,
};

bool set_scrolling = false;

const uint16_t PROGMEM cb_tgl[] = {KC_RALT, LT(1,KC_SPC), COMBO_END};
const uint16_t PROGMEM cb_rctl[] = {KC_RALT,KC_RBRC, COMBO_END};

combo_t key_combos[] = {
  COMBO(cb_tgl, TG(1)),
  COMBO(cb_rctl, KC_RCTL),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        QK_GESC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                            KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL ,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                            KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_EQL ,
 WIN_T(KC_MINS), KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                            KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                            KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, RSFT_T(KC_ENT),
                          KC_LBRC,KC_LALT,LT(2,KC_SPC),KC_LCTL,                          KC_PGUP ,LT(1,KC_SPC),KC_RALT,KC_RBRC,
                          KC_DEL , KC_WFWD, KC_WBAK, KC_BSPC,                            KC_PGDN, KC_HOME, KC_END, KC_BSLS  

    ),
    [_LOWER] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                            _______, _______, KC_UP  , _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                            _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______,                            _______, _______, _______, _______,
                          _______, _______, _______, _______,                            _______, _______, _______, _______
    ),
    [_RAISE] = LAYOUT(
        KC_VOLU, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                            KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
        KC_VOLD, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, KC_F12 ,
        KC_NUM , _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______,                            _______, _______, _______, _______,
                          _______, _______, _______, _______,                            _______, _______, _______, _______
    ),
    [_ADJUST] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
                          _______, _______, KC_BTN1, _______,                            KC_BTN1, _______, _______, _______,
                          _______, _______, _______, _______,                            DRAG_SCROLL, KC_BTN2, _______, _______
    ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
      case QWERTY:
        if (record->event.pressed) {
          set_single_persistent_default_layer(_QWERTY);
        }
        return false;
        break;
      case LOWER:
        if (record->event.pressed) {
          layer_on(_LOWER);
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
          layer_off(_LOWER);
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
      case RAISE:
        if (record->event.pressed) {
          layer_on(_RAISE);
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
          layer_off(_RAISE);
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
      case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;

      // case KC_LEFT:
      //   if (record->event.pressed) {
      //     layer_on(_LOWER);
      //   }
      //   break;
      //   return false;
      //   break;

      // case KC_DOWN:
      //   if (record->event.pressed) {
      //     layer_on(_LOWER);
      //   }
      //   break;
      //   return false;
      //   break;

      // case KC_RGHT:
      //   if (record->event.pressed) {
      //     layer_on(_LOWER);
      //   }
      //   break;
      //   return false;
      //   break;

      // case KC_A ... KC_Z:
      //   if (record->event.pressed) {
      //     layer_off(_LOWER);
      //   }
      //   break;
      //   return false;
      //   break;

      // case DRAG_SCROLL:
      //       // Toggle set_scrolling when DRAG_SCROLL key is pressed or released
      //       set_scrolling = record->event.pressed;
      //       break;
      //   default:
      //       break;

      case DRAG_SCROLL:
          if (record->event.pressed) {
              layer_on(_ADJUST);
              set_scrolling = true;
            } else {
              layer_off(_ADJUST);
              set_scrolling = false;
            }
            return false;
            break;
    }
    return true;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RSFT_T(KC_ENT):
            return true;
        case CTL_T(KC_BSPC):
            return true;
        case LT(2,KC_SPC):
            return true;
        case RSFT_T(KC_QUOT):
            return true;
        case LSFT_T(KC_MINS):
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RSFT_T(KC_ENT):
            return true;
        case CTL_T(KC_BSPC):
            return true;
        case RSFT_T(KC_QUOT):
            return true;
        case LSFT_T(KC_MINS):
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_T(KC_BSPC):
            return QUICK_TAP_TERM - 20;
        case LT(1,KC_RGHT):
            return QUICK_TAP_TERM - 20;
        case RSFT_T(KC_QUOT):
            return QUICK_TAP_TERM - 20;
        case LSFT_T(KC_MINS):
            return QUICK_TAP_TERM - 20;
        case RSFT_T(KC_ENT):
            return QUICK_TAP_TERM - 20;
        default:
            return QUICK_TAP_TERM;
    }
}

void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

// layer_state_t layer_state_set_user(layer_state_t state) {
//     switch (get_highest_layer(state)) {
//         case _ADJUST:  // If we're on the _RAISE layer enable scrolling mode
//             set_scrolling = true;
//             // pointing_device_set_cpi(2000);
//             break;
//         default:
//             set_scrolling = false;
//             // if (set_scrolling) {  // check if we were scrolling before and set disable if so
//             //     set_scrolling = false;
//             //     // pointing_device_set_cpi(8000);
//             // }
//             break;
//     }
//     // if (get_highest_layer(state) != AUTO_MOUSE_DEFAULT_LAYER) {
//     //     set_scrolling = false;
//     // }
//     return state;
// }

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 15.0
#define SCROLL_DIVISOR_V 15.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        // scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        // mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        // scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

// Function to handle layer changes and disable drag scrolling when not in AUTO_MOUSE_DEFAULT_LAYER
// layer_state_t layer_state_set_user(layer_state_t state) {
//     // Disable set_scrolling if the current layer is not the AUTO_MOUSE_DEFAULT_LAYER
//     if (get_highest_layer(state) != AUTO_MOUSE_DEFAULT_LAYER) {
//         set_scrolling = false;
//     }
//     return state;
// }
