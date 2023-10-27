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
};

// const uint16_t PROGMEM cb_btn2[] = {KC_BTN1, KC_UP, COMBO_END};
// const uint16_t PROGMEM df_shft[] = {KC_D, KC_F, COMBO_END};
// const uint16_t PROGMEM jk_shft[] = {KC_J, KC_K, COMBO_END};
// const uint16_t PROGMEM mina_lbrc[] = {LGUI_T(KC_MINS), KC_A, COMBO_END};
// const uint16_t PROGMEM sclnquot_rbrc[] = {KC_SCLN, KC_QUOT, COMBO_END};

// combo_t key_combos[] = {
//   COMBO(cb_btn2, KC_BTN2),
  // COMBO(df_shft, KC_LSFT),
  // COMBO(jk_shft, KC_RSFT),
  // COMBO(mina_lbrc, KC_LBRC),
  // COMBO(sclnquot_rbrc, KC_RBRC),
// };


// Tap Dance declarations
// enum {
//     TD_RALT_L1,
//     TD_RCTL_L0,
// };

// // Tap Dance definitions
// tap_dance_action_t tap_dance_actions[] = {
//     [TD_RALT_L1] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, TO(1)),
//     [TD_RCTL_L0] = ACTION_TAP_DANCE_DOUBLE(KC_RCTL, TO(0)),
// };


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        QK_GESC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                                               KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL ,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                                               KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_EQL ,
 WIN_T(KC_MINS), KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                                               KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                                                               KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                                            KC_LALT, LT(2,KC_SPC),  XXXXXXX, CTL_T(KC_BSPC), KC_BTN1,   KC_PGUP, KC_ENT , XXXXXXX, LT(1,KC_SPC), KC_RALT,
                                                                    KC_LBRC, KC_RBRC, KC_BTN2,          KC_PGDN, KC_HOME, KC_END

    ),
    [_LOWER] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                                               _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                               _______, _______, KC_UP  , _______, _______, _______ ,
        _______, _______, _______, _______, _______, _______,                                                               _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                               _______, _______, _______, _______, KC_BSLS, _______,
                                            _______, _______,       _______, _______, _______,   _______, _______, _______, _______, KC_RCTL,
                                                                    _______, _______, _______,   _______, _______, _______
    ),
    [_RAISE] = LAYOUT(
        KC_VOLU, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                                               KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
        KC_VOLD, _______, _______, _______, _______, _______,                                                               _______, _______, _______, _______, _______, KC_F12 ,
        KC_NUM , _______, _______, _______, _______, _______,                                                               _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                               _______, _______, _______, _______, KC_BSLS, _______,
                                            _______, _______,       _______, _______, _______,   _______, _______, _______, _______, KC_RCTL,
                                                                    _______, _______, _______,   _______, _______, _______
    ),
    [_ADJUST] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                                               _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                               _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                               _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                               _______, _______, _______, _______, _______, _______,
                                            _______, _______,       _______, _______, _______,   _______, _______, _______, _______, _______,
                                                                    _______, _______, _______,   _______, _______, _______
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
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_T(KC_BSPC):
            return QUICK_TAP_TERM - 20;
        default:
            return QUICK_TAP_TERM;
    }
}