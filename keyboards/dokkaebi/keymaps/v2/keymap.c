#include QMK_KEYBOARD_H
#include "math.h"

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

const uint16_t PROGMEM cb_btn2[] = {KC_BTN1, LT(2,KC_6), COMBO_END};
const uint16_t PROGMEM df_shft[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_shft[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM mina_lbrc[] = {LGUI_T(KC_MINS), KC_A, COMBO_END};
const uint16_t PROGMEM sclnquot_rbrc[] = {KC_SCLN, KC_QUOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  COMBO(cb_btn2, KC_BTN2),
  COMBO(df_shft, KC_LSFT),
  COMBO(jk_shft, KC_RSFT),
  COMBO(mina_lbrc, KC_LBRC),
  COMBO(sclnquot_rbrc, KC_RBRC),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        QK_GESC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                               LT(2,KC_6), KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL ,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_DEL ,       KC_HOME, KC_PGUP,        KC_BTN1, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_EQL ,
LGUI_T(KC_MINS), KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                KC_END , KC_PGDN,                 KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
LSFT_T(KC_LBRC), KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                     KC_UP  ,                     KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, RSFT_T(KC_RBRC),
                              KC_LALT, LT(1,KC_SPC), LCTL_T(KC_BSPC),   KC_LEFT, KC_DOWN, KC_RGHT, LSFT_T(KC_ENT), LT(1,KC_SPC) , LT(1,KC_RALT)

    ),
    [_LOWER] = LAYOUT(
        _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                                  KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_HOME,
        _______, _______, _______, _______, _______, _______, KC_F11 ,       KC_NUM , _______,        KC_F12 , _______, _______, KC_UP  , _______, _______, KC_END ,
        _______, _______, _______, _______, _______, _______,                _______, _______,                 _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_PGUP,
        _______, _______, _______, _______, _______, _______,                     KC_VOLU,                     _______, _______, _______, _______, KC_BSLS, KC_PGDN,
                                            _______, _______, KC_LCTL,   _______, KC_VOLD, _______,   _______, _______, KC_RCTL
    ),
    [_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                                  _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, KC_WH_U,        KC_BTN1, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                _______, KC_WH_D,                 _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                     _______,                     _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,   _______, _______, KC_WBAK,   KC_WFWD, _______, _______
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
        case LCTL_T(KC_BSPC):
            return true;
        case LSFT_T(KC_ENT):
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
        case LSFT_T(KC_ENT):
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_BSPC):
            return QUICK_TAP_TERM - 20;
        case LSFT_T(KC_ENT):
            return QUICK_TAP_TERM - 20;
        default:
            return QUICK_TAP_TERM;
    }
}

static bool scrolling_mode = false;
// // static bool scrolling_mode2 = false;

void keyboard_post_init_user(void) {
    pointing_device_set_cpi(40000);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _RAISE:
            scrolling_mode = true;
            pointing_device_set_cpi(16000);
            break;
        default:
            if (scrolling_mode) {
                scrolling_mode = false;
                pointing_device_set_cpi(40000);
            }
            break;
    }
    return state;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    float magnitude = sqrtf(mouse_report.x * mouse_report.x + mouse_report.y * mouse_report.y);

    float adjusted_magnitude = powf(magnitude, 0.4f);

    mouse_report.x = (int16_t)(mouse_report.x * adjusted_magnitude);

    mouse_report.y = (int16_t)(mouse_report.y * adjusted_magnitude);

    if (scrolling_mode) {
        mouse_report.h = -1*mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

// static uint16_t mouse_timer           = 0;
// static uint16_t mouse_debounce_timer  = 0;
// bool            tap_toggling = false, enable_acceleration = true;

// #define TAP_CHECK 10

// __attribute__((weak)) report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report) {
//     return mouse_report;
// }

// report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {

//     // if (scrolling_mode) {
//     //     mouse_report.h = -1*mouse_report.x;
//     //     mouse_report.v = mouse_report.y;
//     //     mouse_report.x = 0;
//     //     mouse_report.y = 0;
//     // }
//     // // if (scrolling_mode2) {
//     // //     mouse_report.h = -1*mouse_report.x;
//     // //     mouse_report.v = 0;
//     // //     mouse_report.x = 0;
//     // //     mouse_report.y = 0;
//     // // }
//     // return mouse_report;

//     mouse_xy_report_t x = mouse_report.x, y = mouse_report.y;
//     mouse_report.x = 0;
//     mouse_report.y = 0;

//     if (x != 0 && y != 0) {
//         mouse_timer = timer_read();

//         if (timer_elapsed(mouse_debounce_timer) > TAP_CHECK) {
//             if (enable_acceleration) {
//                 x = (mouse_xy_report_t)(x > 0 ? x * x / 16 + x : -x * x / 16 + x);
//                 y = (mouse_xy_report_t)(y > 0 ? y * y / 16 + y : -y * y / 16 + y);
//             }
//             mouse_report.x = x;
//             mouse_report.y = y;
//             // if (!layer_state_is(_MOUSE)) {
//             //     layer_on(_MOUSE);
//             // }
//         }
//     // } else if (timer_elapsed(mouse_timer) > 650 && layer_state_is(_MOUSE) && !mouse_keycode_tracker && !tap_toggling) {
//     //     layer_off(_MOUSE);
//     // } else if (tap_toggling) {
//     //     if (!layer_state_is(_MOUSE)) {
//     //         layer_on(_MOUSE);
//     //     }
//     }

//     return pointing_device_task_keymap(mouse_report);
// }