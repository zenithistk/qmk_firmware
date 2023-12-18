#include QMK_KEYBOARD_H
#include "math.h"

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _NAV 4
#define _FROW 5

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  NAV,
  FROW,
};

const uint16_t PROGMEM cb_btn2[] = {KC_BTN1, LT(1,KC_HOME), COMBO_END};
const uint16_t PROGMEM cb_www_back[] = {KC_LBRC, KC_BSPC, COMBO_END};
const uint16_t PROGMEM cb_www_back2[] = {LT(2,KC_END), KC_N, COMBO_END};
const uint16_t PROGMEM cb_www_back3[] = {LT(5,KC_PGDN), KC_N, COMBO_END};
const uint16_t PROGMEM cb_www_fwd[] = {KC_RBRC, KC_BSPC, COMBO_END};
const uint16_t PROGMEM cb_www_close[] = {LT(2,KC_END), KC_LEFT, COMBO_END};
const uint16_t PROGMEM cb_www_close2[] = {KC_PGUP, LT(4,KC_SPC), COMBO_END};

combo_t key_combos[] = {
  COMBO(cb_btn2, KC_BTN2),
  COMBO(cb_www_back, LALT(KC_LEFT)),
  COMBO(cb_www_back2, LALT(KC_LEFT)),
  COMBO(cb_www_back3, LALT(KC_LEFT)),
  COMBO(cb_www_fwd, LALT(KC_RGHT)),
  COMBO(cb_www_close, LCTL(KC_W)),
  COMBO(cb_www_close2, LCTL(KC_W)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        QK_GESC,    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                                   KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_BSLS,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_DEL,         KC_BTN1,    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_EQL,
    LGUI_T(KC_MINS),KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_PGUP,        LT(1,KC_HOME),KC_H,     KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_PGDN,        LT(2,KC_END),KC_N,      KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    RSFT_T(KC_ENT),
                                                        KC_LALT,    LT(1,KC_SPC),KC_LCTL,       KC_UP,      KC_SPC,     LT(2,KC_RALT),
                                                        KC_LBRC,    KC_BSPC,    KC_RBRC,        KC_LEFT,    KC_DOWN,    KC_RGHT
    ),
    [_LOWER] = LAYOUT(
        _______,    KC_F1  ,    KC_F2  ,    KC_F3  ,    KC_F4  ,    KC_F5  ,                                KC_F6  ,    KC_F7  ,    KC_F8  ,    KC_F9  ,    KC_F10 ,    KC_F11 ,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,        _______,    _______,    _______,    _______,    _______,    _______,    KC_F12 ,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,        _______,    _______,    _______,    _______,    _______,    _______,    _______,
                                                        _______,    _______,    _______,        _______,    _______,    KC_RCTL,
                                                        _______,    _______,    _______,        _______,    _______,    _______
    ),
    [_RAISE] = LAYOUT(
        KC_ESC ,    _______,    _______,    _______,    _______,    _______,                                _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,        _______,    _______,    _______,    _______,    _______,    _______,    _______,
                                                        _______,    _______,    _______,        KC_VOLU,    KC_NUM ,    _______ ,
                                                        _______,    _______,    _______,        _______,    KC_VOLD,    _______
    ),
    [_ADJUST] = LAYOUT(
        _______,    _______,    _______,    _______,    _______,    _______,                                _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,        _______,    _______,    _______,    _______,    _______,    _______,    _______,
                                                        _______,    _______,    _______,        _______,    _______,    _______ ,
                                                        _______,    _______,    _______,        _______,    _______,    _______
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
        case RSFT_T(KC_ENT):
            return true;
        case CTL_T(KC_BSPC):
            return true;
        case LT(2,KC_SPC):
            return true;
        case LT(1,KC_SPC):
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
        case LT(1,KC_SPC):
            return QUICK_TAP_TERM - 20;
        case RSFT_T(KC_QUOT):
            return QUICK_TAP_TERM - 20;
        case LSFT_T(KC_MINS):
            return QUICK_TAP_TERM - 20;
        case RSFT_T(KC_ENT):
            return QUICK_TAP_TERM - 20;
        case LGUI_T(KC_MINS):
            return QUICK_TAP_TERM - 20;
        default:
            return QUICK_TAP_TERM;
    }
}


static bool scrolling_mode = false;
static bool scrolling_mode_h = false;

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

void keyboard_post_init_user(void) {
    pointing_device_set_cpi(430);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _LOWER:
            scrolling_mode = true;
            pointing_device_set_cpi(1);
            break;
        case _RAISE:
            scrolling_mode_h = true;
            pointing_device_set_cpi(1);
            break;
        case _NAV:
            scrolling_mode = true;
            pointing_device_set_cpi(1);
            break;
        case _FROW:
            scrolling_mode_h = true;
            pointing_device_set_cpi(1);
            break;
        default:
            if (scrolling_mode) {
                scrolling_mode = false;
                pointing_device_set_cpi(430);
            }
            else if (scrolling_mode_h) {
                scrolling_mode_h = false;
                pointing_device_set_cpi(430);
            }
            break;
    }
    return state;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    float magnitude = sqrtf(mouse_report.x * mouse_report.x + mouse_report.y * mouse_report.y);
    float adjusted_magnitude = powf(magnitude, 1.6f);

    mouse_report.x = (float)(mouse_report.x * adjusted_magnitude);

    mouse_report.y = (float)(mouse_report.y * adjusted_magnitude);

    if (scrolling_mode) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        // scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        // mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.h = 0;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        // scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    if (scrolling_mode_h) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        // scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        // mouse_report.h = 0;
        mouse_report.v = 0;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        // scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}