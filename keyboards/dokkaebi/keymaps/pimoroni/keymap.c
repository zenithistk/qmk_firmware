#include QMK_KEYBOARD_H
#ifdef PIMORONI_TRACKBALL_ENABLE
  #include "pimoroni_trackball.h"
#endif

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
};
                         
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        QK_GESC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                                  KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_EQL ,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_DEL ,       KC_HOME, KC_PGUP,        KC_BTN1, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_MINS,
LGUI_T(KC_BSPC), KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                KC_END , KC_PGDN,                 KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
LSFT_T(KC_LBRC), KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                     KC_UP  ,                     KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, RSFT_T(KC_RBRC),
                               LALT_T(KC_BTN1), LT(1,KC_SPC), KC_LCTL,   KC_LEFT, KC_DOWN, KC_RGHT,   KC_ENT , LT(1,KC_SPC), KC_RALT

    ),
    [_LOWER] = LAYOUT(
        KC_NUM , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                                  KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______,        KC_BSLS, _______, _______, _______, _______, _______, KC_F12 ,
        _______, _______, _______, _______, _______, _______,                _______, _______,                 _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                     KC_VOLU,                     _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,   _______, KC_VOLD, _______,   KC_RCTL, _______, _______
    ),
    [_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                                  _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                _______, _______,                 _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                     _______,                     _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,   _______, _______, _______,   _______, _______, _______
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
    }
    return true;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_LBRC):
            return true;
        case RSFT_T(KC_RBRC):
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_LBRC):
            // Immediately select the hold action when another key is tapped.
            return true;
        case RSFT_T(KC_RBRC):
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

// static bool scrolling_mode = false;
// // static bool scrolling_mode2 = false;

// void keyboard_post_init_user(void) {
//     pointing_device_set_cpi(45000);
// }

// layer_state_t layer_state_set_user(layer_state_t state) {
//     switch (get_highest_layer(state)) {
//         case _LOWER:
//             scrolling_mode = true;
//             pointing_device_set_cpi(8000);
//             break;
//         // case _RAISE:
//         //     scrolling_mode2 = true;
//         //     pointing_device_set_cpi(17000);
//         //     break;
//         default:
//             if (scrolling_mode) {
//                 scrolling_mode = false;
//                 pointing_device_set_cpi(45000);
//             }
//             // if (scrolling_mode2) {
//             //     scrolling_mode2 = false;
//             //     pointing_device_set_cpi(65535);
//             // }
//             break;
//     }
//     return state;
// }

// report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
//     if (scrolling_mode) {
//         mouse_report.h = -1*mouse_report.x;
//         mouse_report.v = mouse_report.y;
//         mouse_report.x = 0;
//         mouse_report.y = 0;
//     }
//     // if (scrolling_mode2) {
//     //     mouse_report.h = -1*mouse_report.x;
//     //     mouse_report.v = 0;
//     //     mouse_report.x = 0;
//     //     mouse_report.y = 0;
//     // }
//     return mouse_report;
// }
