#include QMK_KEYBOARD_H

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

const uint16_t PROGMEM cb_btn2[] = {KC_BTN1, KC_RGHT, COMBO_END};
const uint16_t PROGMEM cb_btn3[] = {KC_BTN1, KC_WH_D, COMBO_END};
// const uint16_t PROGMEM df_shft[] = {KC_D, KC_F, COMBO_END};
// const uint16_t PROGMEM jk_shft[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM cmb_lbrc[] = {LGUI_T(KC_MINS), KC_A, COMBO_END};
const uint16_t PROGMEM cmb_rbrc[] = {KC_SCLN, KC_QUOT, COMBO_END};
const uint16_t PROGMEM vb_btn1[] = {KC_V, KC_B, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  // COMBO(cb_btn2, KC_BTN2),
  COMBO(cb_btn2, TG(2)),
  COMBO(cb_btn3, TG(2)),
  // COMBO(df_shft, KC_LSFT),
  // COMBO(jk_shft, KC_RSFT),
  COMBO(cmb_lbrc, KC_LBRC),
  COMBO(cmb_rbrc, KC_RBRC),
  COMBO(vb_btn1, KC_BTN1),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        QK_GESC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                        KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL ,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,       KC_HOME, KC_END , KC_PGUP,       KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_EQL ,
LGUI_T(KC_MINS), KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,       KC_DEL , KC_UP  , KC_PGDN,       KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,       KC_LEFT, KC_DOWN, KC_RGHT,       KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                              KC_LALT, LT(1,KC_SPC), LCTL_T(KC_BSPC),        KC_BTN1,           KC_ENT, LT(1,KC_SPC) , KC_RALT
    ),
    [_LOWER] = LAYOUT(
        _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                        KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_HOME,
        _______, _______, _______, _______, _______, _______,       KC_F11 , _______, KC_F12 ,       _______, _______, KC_UP  , _______, _______, KC_END ,
        _______, _______, _______, _______, _______, _______,       _______, KC_VOLU, _______,       _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_PGUP,
        _______, _______, _______, _______, _______, _______,       _______, KC_VOLD, _______,       _______, _______, _______, _______, KC_BSLS, KC_PGDN,
                                            _______, _______, KC_LCTL,       KC_NUM ,       _______, _______, KC_RCTL
    ),
    [_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,       _______, _______, _______,       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,       LCTL(KC_W), KC_WFWD, KC_WH_U,    _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,       KC_WBAK, KC_BTN2, KC_WH_D,       _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,       KC_BTN1,       _______, _______, _______
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
      case KC_BTN1 ... KC_BTN5:
        if (record->event.pressed) {
          pointing_device_set_button(1 << (keycode - KC_BTN1));
        } else {
          pointing_device_clear_button(1 << (keycode - KC_BTN1));
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