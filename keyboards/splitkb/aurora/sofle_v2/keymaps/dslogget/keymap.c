/* Copyright 2023 splitkb.com <support@splitkb.com>
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

#include "splitkb/aurora/sofle_v2/rev1/config.h"

enum layers {
    _QWERTY = 0,
    _GAMING,
    _NAVIGATION,
    _SYMBOLS,
};

enum my_keycodes { MO_DIS_GAME = QK_USER };

#define MO_NAV MO(_NAVIGATION)
#define MO_SYM MO(_SYMBOLS)

/*
[_trans] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______
)
*/

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_SPC,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_F24,  KC_MUTE, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TG(_GAMING),
               KC_LGUI, KC_LALT, KC_LSFT, KC_ENT,  MO_SYM,    MO_NAV,  KC_SPC,  KC_BSPC, KC_LCTL, KC_PRINT_SCREEN
    ),
    [_GAMING] = LAYOUT(
         _______, _______,  _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
         KC_T, KC_TAB,  KC_Q, KC_W, KC_E, KC_R,                      _______, _______, _______, _______, _______, _______,
         KC_G, KC_LSFT, KC_A, KC_S, KC_D, KC_F,                      _______, _______, _______, _______, _______, _______,
         KC_B, KC_LCTL,   KC_Z, KC_X, KC_C, KC_V, _______,      _______, _______, _______, _______, _______, _______, _______,
               KC_LSFT, KC_LALT, KC_LCTL, KC_SPC, _______,     _______, _______, _______, _______, _______
    ),
    [_NAVIGATION] = LAYOUT(
        KC_F12,  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                             KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
        _______, KC_MEDIA_PLAY_PAUSE, KC_KP_7, KC_KP_8, KC_KP_9, _______,                   _______, _______, KC_UP, KC_PGUP, KC_PGUP, _______,
        _______, KC_KP_0, KC_KP_4, KC_KP_5, KC_KP_6, _______,                   KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, _______,
        KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_KP_1, KC_KP_2, KC_KP_3, _______, _______, _______, _______, _______, _______, KC_PGDN, _______, _______,
                          _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
    ),
    [_SYMBOLS] = LAYOUT(
        KC_GRV,  _______, _______, RALT(KC_3), _______, _______,                _______, _______, _______, _______, _______, _______,
        _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, _______,                   KC_ASTR, KC_LCBR, KC_PLUS, KC_RCBR, _______, KC_TILD,
        _______, KC_KP_0, KC_KP_4, KC_KP_5, KC_KP_6, _______,                   KC_AMPR, KC_LPRN, KC_MINS, KC_RPRN, KC_EQL,  KC_PIPE,
        _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, _______, _______, _______, KC_HASH, KC_LBRC, KC_UNDS, KC_RBRC, KC_BSLS, _______,
                          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};
// clang-format on

void keyboard_pre_init_user(void) {
    // Set our LED pin as output
    setPinOutput(24);
    // Turn the LED off
    // (Due to technical reasons, high is off and low is on)
    writePinHigh(24);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MO_DIS_GAME:
            record->event.pressed ? layer_off(_GAMING) : layer_on(_GAMING);
            return false; // Skip all further processing of this key
        default:
            return true; // Process all other keycodes normally
    }
}

#define myGreen 0, 80, 0
#define myRed 80, 0, 0
#define myBlue 0, 0, 80

#define PRE_CHARGE_PERIOD 0xD9

void keyboard_post_init_user(void) {
    debug_enable           = true;
    rgb_matrix_config.mode = 1;
    rgb_matrix_sethsv_noeeprom(85, 255, 80);
    // rgb_matrix_set_color_all( myGreen );
}

#define LHS_LED_BASE 35
#define LED_PER_KEY 6

layer_state_t layer_state_set_user(layer_state_t state) {
    if (layer_state_cmp(state, _GAMING)) {
        rgb_matrix_sethsv_noeeprom(8, 245, 80);
    } else {
        rgb_matrix_sethsv_noeeprom(85, 255, 80);
    }
    return state;
}

void housekeeping_task_user(void) {
    /*static uint16_t key_timer = 0;
    static uint16_t last_time = 0;


    uint16_t elapsedTime = timer_elapsed(key_timer) / 200;
    if ( last_time != elapsedTime && elapsedTime < 70 ) {
      // Base colour, green
      rgb_matrix_set_color_all( myGreen );
      rgb_matrix_set_color( elapsedTime, RGB_RED );
      last_time = elapsedTime;
    } else if ( elapsedTime >= 70 ) {
      key_timer = timer_read();
    }*/
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    // 0 is left-half encoder
    // 1 is right-half encoder
    if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 0) {
        if (clockwise) {
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
        }
    }

    return false;
}
#endif

// clang-format off
// 'winton', 32x32px
const char epd_bitmap_winton [] PROGMEM = {
    0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 
    0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x1f, 0x7f, 0xf1, 0xe4, 0xee, 0xee, 0xee, 0xee, 0xee, 0xe4, 0xb1, 0x7b, 0xfb, 
    0xfb, 0x7b, 0xb1, 0xe4, 0xee, 0xee, 0xee, 0xee, 0xee, 0xe4, 0xf1, 0x7f, 0x1f, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf3, 0xff, 0x7f, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 
    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x7f, 0xff, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// clang-format on

void oled_task_post_user(void) {
    if (layer_state_is(_GAMING)) {
        oled_set_cursor(0, 0);
        oled_write_raw_P(epd_bitmap_winton, sizeof(epd_bitmap_winton));
    }
}