#include "v3.h"

#include "i2c_master.h"
#include "pointing_device.h"

#include "iqs5xx.h"

static void dummy_func(uint8_t btn){};
void (*pointing_device_set_button)(uint8_t btn) = dummy_func;
void (*pointing_device_clear_button)(uint8_t btn) = dummy_func;

bool mouse_send_flag = false;
// bool is_osx = false;

// void identify_os(void) { 
//     is_osx = get_usb_host_os_type() == 2;
// }

void pointing_device_task(void) {
    if (mouse_send_flag) {
        pointing_device_send();
        mouse_send_flag = false;
    }
}

void keyboard_pre_init_kb() {
    i2c_init();
}

void keyboard_post_init_kb() {
    init_iqs5xx();
    pointing_device_set_button = pointing_device_set_button_iqs5xx;
    pointing_device_clear_button = pointing_device_clear_button_iqs5xx;
    ges_time = timer_read32();
    one_finger_drag = false;
        
    wait_ms(300);

    // identify_os();
}

void matrix_scan_kb() {
    iqs5xx_data_t iqs5xx_data;
    report_mouse_t mouse_rep = {0};
    bool is_valid = false;

    is_valid = read_iqs5xx(&iqs5xx_data);

    if (is_valid) {
        static iqs5xx_processed_data_t iqs5xx_processed_data;
        static iqs5xx_gesture_data_t iqs5xx_gesture_data;
        bool send_flag = process_iqs5xx(&iqs5xx_data, &iqs5xx_processed_data, &mouse_rep, &iqs5xx_gesture_data);

        switch (iqs5xx_gesture_data.two.gesture_state) {
            case GESTURE_SWIPE_U:
                if(timer_elapsed32(ges_time) > GES_TIME_MS){
                    mouse_rep.v = 1.5;
                    send_flag = true;
                    ges_time = timer_read32();
                }
                break;
                // mouse_rep.v = 1;
                // send_flag = true;
                // break;
            case GESTURE_SWIPE_D:
                if(timer_elapsed32(ges_time) > GES_TIME_MS){
                    mouse_rep.v = -1.5;
                    send_flag = true;
                    ges_time = timer_read32();
                }
                break;
                // mouse_rep.v = -1;
                // send_flag = true;
                // break;
            case GESTURE_SWIPE_R:
                if(timer_elapsed32(ges_time) > GES_TIME_MS){
                    mouse_rep.h = -1;
                    send_flag = true;
                    ges_time = timer_read32();
                }
                break;
                // mouse_rep.h = -1;
                // send_flag = true;
                // break;
            case GESTURE_SWIPE_L:
                if(timer_elapsed32(ges_time) > GES_TIME_MS){
                    mouse_rep.h = 1;
                    send_flag = true;
                    ges_time = timer_read32();
                }
                break;
                // mouse_rep.h = 1;
                // send_flag = true;
                // break;
            case GESTURE_PINCH_IN:
                if(timer_elapsed32(ges_time) > GES_TIME_MS){
                    tap_code16(LCTL(KC_WH_U));
                    // is_osx ? tap_code16(LGUI(KC_EQL)) : tap_code16(LCTL(KC_PPLS));
                    ges_time = timer_read32();
                }
                break;
            case GESTURE_PINCH_OUT:
                if(timer_elapsed32(ges_time) > GES_TIME_MS){
                    tap_code16(LCTL(KC_WH_D));
                    // is_osx ? tap_code16(LGUI(KC_MINS)) : tap_code16(LCTL(KC_PMNS));
                    ges_time = timer_read32();
                }
                break;
            // case GESTURE_ROT_CW:
            //     if(timer_elapsed32(ges_time) > GES_TIME_MS){
            //         tap_code16(KC_WFWD);
            //         // is_osx ? tap_code16(LGUI(KC_EQL)) : tap_code16(LCTL(KC_PPLS));
            //         ges_time = timer_read32();
            //     }
            //     break;
            // case GESTURE_ROT_CCW:
            //     if(timer_elapsed32(ges_time) > GES_TIME_MS){
            //         tap_code16(KC_WBAK);
            //         // is_osx ? tap_code16(LGUI(KC_MINS)) : tap_code16(LCTL(KC_PMNS));
            //         ges_time = timer_read32();
            //     }
            //     break;
            default:
                break;
        }
        if (send_flag) {
            mouse_send_flag = true;
            pointing_device_set_report(mouse_rep);
        }
    }
}
