/* Copyright 2021 pecolynx
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
#include "print.h"
#include "pointing_device.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    KC_MY_BTN1,
    KC_MY_BTN2,
    KC_MY_BTN3
};

// #define LOWER  MO(_LOWER)
// #define RAISE  MO(_RAISE)
// #define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
    * ,-----------------------------------------.                               .-----------------------------------------.
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |                               |   Y  |   U  |   I  |   O  |   P  |   ~  |
    * |------+------+------+------+------+------|                               |------+------+------+------+------+------|
    * | Shift|   A  |   S  |   D  |   F  |   G  |                               |   H  |   J  |   K  |   L  |   ;  |   '  |
    * |------+------+------+------+------+------|                               |------+------+------+------+------+------|
    * | Ctrl |   Z  |   X  |   C  |   V  |   B  |                               |   N  |   M  |   ,  |   .  |   /  |   `  |
    * |------+------+------+------+------+------+-------------.   .-------------+------+------+------+------+------+------|
    * | Alt  | GUI  | Alt  |      |Lower | Esc  |Space |      |   |Enter | Bksp | Esc  |Raise | Del  |      |      |Enter |
    * `-------------------------------------------------------'   `-------------------------------------------------------'
    */
    [_QWERTY] = LAYOUT(
      KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,      KC_T,                                KC_Y,  KC_U,      KC_I,   KC_O,   KC_P,   KC_TILD, \
      KC_LSFT,KC_A,   KC_S,   KC_D,   KC_F,      KC_G,                                KC_H,  KC_J,      KC_K,   KC_L,   KC_SCLN,KC_QUOT, \
      KC_LCTL,KC_Z,   KC_X,   KC_C,   KC_V,      KC_B,                                KC_N,  KC_M,      KC_COMM,KC_DOT, KC_SLSH,KC_GRV , \
      KC_LALT,KC_LGUI,KC_LALT,_______,MO(_LOWER),KC_ESC,KC_SPC,_______,KC_ENT,KC_BSPC,KC_ESC,MO(_RAISE),KC_DEL, _______,_______,KC_ENT   \
    ),
    /* Lower
    * ,-----------------------------------------.                               .-----------------------------------------.
    * | Tab  |   !  |   @  |   #  |   $  |   %  |                               |   ^  |   &  |   *  |   \  |   |  |      |
    * |------+------+------+------+------+------|                               |------+------+------+------+------+------|
    * | Shift|      |      |      |      |      |                               | Left | Down |  Up  |Right | Home | End  |
    * |------+------+------+------+------+------|                               |------+------+------+------+------+------|
    * | Ctrl |      |      |      |      |      |                               |   -  |   _  |   +  |   =  |PageUp|PageDn|
    * |------+------+------+------+------+------+-------------.   .-------------+------+------+------+------+------+------|
    * | Alt  | GUI  | Alt  |      |      | Esc  |   (  |  )   |   |   {  |   }  |      |      |      |      |      |      |
    * `-------------------------------------------------------'   `------------------------------------------------------'
    */
    [_LOWER] = LAYOUT(
      KC_TAB, KC_EXLM,KC_AT,  KC_HASH,   KC_DLR,    KC_PERC,                                KC_CIRC,KC_AMPR,KC_ASTR,KC_BSLS,KC_PIPE,_______, \
      KC_LSFT,_______,_______,KC_MY_BTN2,KC_MY_BTN1,_______,                                KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_HOME,KC_END,  \
      KC_LCTL,_______,_______,_______,   _______,   _______,                                KC_MINS,KC_UNDS,KC_PLUS,KC_EQL, KC_PGUP,KC_PGDN, \
      KC_LALT,KC_LGUI,KC_LALT,_______,   _______,   KC_ESC, KC_LPRN,KC_RPRN,KC_LCBR,KC_RCBR,KC_SPC, _______,_______,_______,_______,_______  \
    ),
    /* Raise
    * ,-----------------------------------------.                               .-----------------------------------------.
    * | Tab  |   1  |   2  |   3  |   4  |   5  |                               |   6  |   7  |   8  |   9  |   0  |      |
    * |------+------+------+------+------+------|                               |------+------+------+------+------+------|
    * | Shift|  F1  |  F2  |  F3  |  F4  |  F5  |                               |  F6  |  F7  |  F8  |  F9  |  F10 |      |
    * |------+------+------+------+------+------|                               |------+------+------+------+------+------|
    * | Ctrl | F11  | F12  |      |      |      |                               |      |      |      |      |      |      |
    * |------+------+------+------+------+------+-------------.   .-------------+------+------+------+------+------+------|
    * | Alt  | GUI  | Alt  |      |      | Esc  |   (  |  )   |   |   {  |   }  |      |      |      |      |      |      |
    * `-------------------------------------------------------'   `-------------------------------------------------------'
    */
    [_RAISE] = LAYOUT( \
      KC_TAB, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                                   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   _______, \
      KC_LSFT,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                                  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, _______, \
      KC_LCTL,KC_F11, KC_F12, _______,_______,_______,                                _______,_______,_______,_______,_______,_______, \
      KC_LALT,KC_LGUI,KC_LALT,_______,_______,KC_ESC, KC_LBRC,KC_RBRC,_______,_______,KC_SPC, _______,_______,_______,_______,_______  \
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // switch (keycode) {
    //     case QMKBEST:
    //         if (record->event.pressed) {
    //             // when keycode QMKBEST is pressed
    //             SEND_STRING("QMK is the best thing ever!");
    //         } else {
    //             // when keycode QMKBEST is released
    //         }
    //         break;
    //     case QMKURL:
    //         if (record->event.pressed) {
    //             // when keycode QMKURL is pressed
    //             SEND_STRING("https://qmk.fm/\n");
    //         } else {
    //             // when keycode QMKURL is released
    //         }
    //         break;
    // }
    switch (keycode) {
        case KC_MY_BTN1:
        case KC_MY_BTN2:
        case KC_MY_BTN3:
        {
            report_mouse_t currentReport = pointing_device_get_report();
            uint8_t btn = 1 << (keycode - KC_MY_BTN1);
            if (record->event.pressed) {
                currentReport.buttons |= btn;
            } else {
                currentReport.buttons &= ~btn;
            }
            pointing_device_set_report(currentReport);
            pointing_device_send();
            return false;
        }
    }
    uprintf("BEN: index: %d, clockwise: %d\n", 11, 22);
    return true;
}