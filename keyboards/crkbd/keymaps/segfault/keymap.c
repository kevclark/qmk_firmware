/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "keymap_uk.h"

/*
Largely imported from https://github.com/qmk/qmk_firmware/tree/master/users/manna-harbour_miryoku
Added some personality tweaks:
    1. Colemak-dh / qwerty switchable base layer
    2. Inverted T Nav layer
    3. Added laptop brightness control to Media layer
    4. Added some UK symbols for gb language
*/

#define U_NP KC_NO // key is not present
#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used

#define U_RDO KC_AGIN
#define U_PST S(KC_INS)
#define U_CPY C(KC_INS)
#define U_CUT S(KC_DEL)
#define U_UND KC_UNDO

enum userspace_layers {
	COLEMAK_DH = 0,
    QWERTY,
    MEDIA,
    NAV,
    MOUSE,
    SYM,
    NUM,
    FUNC

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* colemak DH
     * ,-----------------------------------------------. .-----------------------------------------------.
     * |       |   Q   |   W   |   F   |   P   |   B   | |   J   |   L   |   U   |   Y   |   '   |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |   A   |   R   |   S   |   T   |   G   | |   M   |   N   |   E   |   I   |   O   |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |   Z   |   X   |   C   |   S   |   V   | |   K   |   H   |   ,   |   .   |   /   |       |
     * `-----------------------.                       | |                       .-----------------------'
     *                         |-------+-------+-------| |-------+-------+-------|
     *                         |  ESC  |  SPC  |  TAB  | |  ENT  |  BSPC |  DEL  |
     *                         `-----------------------' '-----------------------'
     *                           Media    Nav    Mouse      Sym     Num    Func
     */
	[COLEMAK_DH] = LAYOUT_split_3x6_3(
    KC_NO,             KC_Q,              KC_W,              KC_F,              KC_P,              KC_B,              KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,          KC_NO,
    KC_NO,             LGUI_T(KC_A),      LALT_T(KC_R),      LCTL_T(KC_S),      LSFT_T(KC_T),      KC_G,              KC_M,              LSFT_T(KC_N),      LCTL_T(KC_E),      LALT_T(KC_I),      LGUI_T(KC_O),     KC_NO,
    KC_NO,             KC_Z,              ALGR_T(KC_X),      KC_C,              KC_D,              KC_V,              KC_K,              KC_H,              KC_COMM,           KC_DOT,    KC_SLSH,          KC_NO,
                                          LT(MEDIA, KC_ESC), LT(NAV, KC_SPC),   LT(MOUSE, KC_TAB), LT(SYM, KC_ENT),   LT(NUM, KC_BSPC),  LT(FUNC, KC_DEL)
	),

    /* QWERTY
     * ,-----------------------------------------------. .-----------------------------------------------.
     * |       |   Q   |   W   |   E   |   R   |   T   | |   Y   |   U   |   I   |   O   |   P   |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |   A   |   S   |   D   |   F   |   G   | |   H   |   J   |   K   |   L   |   '   |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |   Z   |   X   |   C   |   V   |   B   | |   N   |   M   |   ,   |   .   |   /   |       |
     * `-----------------------.                       | |                       .-----------------------'
     *                         |-------+-------+-------| |-------+-------+-------|
     *                         |  ESC  |  SPC  |  TAB  | |  ENT  |  BSPC |  DEL  | 
     *                         `-----------------------' '-----------------------'
     *                           Media    Nav    Mouse      Sym     Num    Func
     */
	[QWERTY] = LAYOUT_split_3x6_3(
    KC_NO,             KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,             KC_NO,
    KC_NO,             LGUI_T(KC_A),      LALT_T(KC_S),      LCTL_T(KC_D),      LSFT_T(KC_F),      KC_G,              KC_H,              LSFT_T(KC_J),      LCTL_T(KC_K),      LALT_T(KC_L),      LGUI_T(KC_QUOT),  KC_NO,
    KC_NO,             KC_Z,              ALGR_T(KC_X),      KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           KC_DOT,    KC_SLSH,          KC_NO,
                                          LT(MEDIA, KC_ESC), LT(NAV, KC_SPC),   LT(MOUSE, KC_TAB), LT(SYM, KC_ENT),   LT(NUM, KC_BSPC),  LT(FUNC, KC_DEL)
	),

    /* Nav
     * ,-----------------------------------------------. .-----------------------------------------------.
     * |       | Reset |       |       |       |       | |  PgUp |  Home |  Up   |  End  |  Ins  |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       | Super |  Alt  |  Ctrl | Shift |       | |  PgDn |  Left |  Down | Right |  Caps |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |       |       |       |       |       | |  Undo |  Cut  |  Copy | Paste |  Redo |       |
     * `-----------------------.                       | |                       .-----------------------'
     *                         |-------+-------+-------| |-------+-------+-------|
     *                         |       |       |       | |  ENT  |  BSPC |  DEL  | 
     *                         `-----------------------' '-----------------------'
     *                                    Nav
     */
    [NAV] = LAYOUT_split_3x6_3(
    KC_NO, RESET,   U_NA,    U_NA,    U_NA,    U_NA,    KC_PGUP, KC_HOME, KC_UP,   KC_END,   KC_INS,  KC_NO,
    KC_NO, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,    KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_CAPS, KC_NO,
    KC_NO, U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_UND,   U_CUT,   U_CPY,   U_PST,    U_RDO,   KC_NO,
                      U_NA,    U_NA,    U_NA,    KC_ENT,  KC_BSPC, KC_DEL
  ),

    /* Mouse
     * ,-----------------------------------------------. .-----------------------------------------------.
     * |       | Reset |       |       |       |       | |  Redo | Paste |  Copy |  Cut  | Undo  |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       | Super |  Alt  |  Ctrl | Shift |       | |       |  Left |  Down |   Up  | Right |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |       |       |       |       |       | |       |  Wh-L |  Wh-D |  Wh-U |  Wh-R |       |
     * `-----------------------.                       | |                       .-----------------------'
     *                         |-------+-------+-------| |-------+-------+-------|
     *                         |       |       |       | |   1   |   2   |   3   | 
     *                         `-----------------------' '-----------------------'
     *                                           Mouse
     */
    [MOUSE] = LAYOUT_split_3x6_3(
    KC_NO, RESET,   U_NA,    U_NA,    U_NA,    U_NA,    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,   KC_NO,
    KC_NO, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,    U_NU,    KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO,
    KC_NO, U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NU,    KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_NO,
                      U_NA,    U_NA,    U_NA,    KC_BTN1, KC_BTN2, KC_BTN3
  ),

    /* Media
     * ,-----------------------------------------------. .-----------------------------------------------.
     * |       | Reset |       |       |       |       | | RGB-T |RGB-MOD|RGB-HUI|RGB-SAI|RGB-VAI|       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       | Super |  Alt  |  Ctrl | Shift |       | |       |  <<   | VolDn | VolUp |  >>   |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |       |       |       |       |       | |COLEMAK| QWERTY|       |  BriU |  BriD |       |
     * `-----------------------.                       | |                       .-----------------------'
     *                         |-------+-------+-------| |-------+-------+-------|
     *                         |       |       |       | |  Stop |  Play | Mute  | 
     *                         `-----------------------' '-----------------------'
     *                           Media
     */
    [MEDIA] = LAYOUT_split_3x6_3(
    KC_NO, RESET,   U_NA,    U_NA,    U_NA,    U_NA,    RGB_TOG,        RGB_MOD,    RGB_HUI, RGB_SAI, RGB_VAI, KC_NO,
    KC_NO, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,    U_NU,           KC_MPRV,    KC_VOLD, KC_VOLU, KC_MNXT, KC_NO,
    KC_NO, U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    DF(COLEMAK_DH), DF(QWERTY), U_NU,    KC_BRIU, KC_BRID, KC_NO,
                      U_NA,    U_NA,    U_NA,    KC_MSTP, KC_MPLY, KC_MUTE
  ),

    /* Num
     * ,-----------------------------------------------. .-----------------------------------------------.
     * |       |   [   |   7   |   8   |   9   |   ]   | |       |       |       |       | Reset |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |   ;   |   4   |   5   |   6   |   =   | |       | Shift |  Ctrl |  Atl  | Super |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |   `   |   1   |   2   |   3   |   \   | |       |       |       |       |       |       |
     * `-----------------------.                       | |                       .-----------------------'
     *                         |-------+-------+-------| |-------+-------+-------|
     *                         |   .   |   0   |   -   | |       |       |       | 
     *                         `-----------------------' '-----------------------'
     *                                                              Num
     */
    [NUM] = LAYOUT_split_3x6_3(
    KC_NO, KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC, U_NA,    U_NA,    U_NA,    U_NA,    RESET,   KC_NO,
    KC_NO, KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,  U_NA,    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO,
    KC_NO, KC_GRV,  KC_1,    KC_2,    KC_3,    UK_BSLS, U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,    KC_NO,
                      KC_DOT,  KC_0,    KC_MINS, U_NA,    U_NA,    U_NA
  ),

    /* Sym
     * ,-----------------------------------------------. .-----------------------------------------------.
     * |       |   {   |   &   |   *   |   (   |   }   | |       |       |       |       | Reset |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |   :   |   $   |   %   |   ^   |   +   | |       | Shift |  Ctrl |  Atl  | Super |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |   ~   |   !   |   "   |   #   |   |   | |       |       |       |       |       |       |
     * `-----------------------.                       | |                       .-----------------------'
     *                         |-------+-------+-------| |-------+-------+-------|
     *                         |   (   |   )   |   _   | |       |       |       | 
     *                         `-----------------------' '-----------------------'
     *                                                      Sym
     */
    [SYM] = LAYOUT_split_3x6_3(
    KC_NO, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, U_NA,    U_NA,    U_NA,    U_NA,    RESET,   KC_NO,
    KC_NO, KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS, U_NA,    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO,
    KC_NO, UK_TILD, KC_EXLM, KC_AT,   UK_HASH, UK_PIPE, U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,    KC_NO,
                      KC_LPRN, KC_RPRN, KC_UNDS, U_NA,    U_NA,    U_NA
  ),

    /* Func
     * ,-----------------------------------------------. .-----------------------------------------------.
     * |       |  F12  |   F7  |   F8  |  F9   | PrtScn| | Scrot |       |       |       | Reset |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |  F11  |   F4  |   F5  |  F6   | Srlck | |       | Shift |  Ctrl |  Atl  | Super |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |  F10  |   F1  |   F2  |  F3   | Break | |       |       |       |       |       |       |
     * `-----------------------.                       | |                       .-----------------------'
     *                         |-------+-------+-------| |-------+-------+-------|
     *                         |   APP |  SPC  |  TAB  | |       |       |       | 
     *                         `-----------------------' '-----------------------'
     *                                                                     Func
     */
    [FUNC] = LAYOUT(
    KC_NO, KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR, S(G(KC_PSCR)), U_NA,    U_NA,    U_NA,    RESET,   KC_NO,
    KC_NO, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SLCK, U_NA,          KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO,
    KC_NO, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, U_NA,          U_NA,    U_NA,    KC_ALGR, U_NA,    KC_NO,
                      KC_APP,  KC_SPC,  KC_TAB,  U_NA,    U_NA,    U_NA
    )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    char string [24];
    //switch (layer_state) {
    switch (get_highest_layer(default_layer_state|layer_state)) {
        case COLEMAK_DH:
            oled_write_ln_P(PSTR("Layer: COLEMAK-DH"),false);
            break;
        case QWERTY:
            oled_write_ln_P(PSTR("Layer: QWERTY"),false);
            break;
        case MEDIA:
            oled_write_ln_P(PSTR("Layer: Media / RGB"),false);
            break;
        case NAV:
            oled_write_ln_P(PSTR("Layer: Nav"),false);
            break;
        case MOUSE:
            oled_write_ln_P(PSTR("Layer: Mouse"),false);
            break;
        case NUM:
            oled_write_ln_P(PSTR("Layer: Numpad"),false);
            break;
        case SYM:
            oled_write_ln_P(PSTR("Layer: Symbols"),false);
            break;
        case FUNC:
            oled_write_ln_P(PSTR("Layer: Function"),false);
            break;
        default:
            snprintf(string, sizeof(string), "%ld",layer_state);
            oled_write_P(PSTR("Layer: Undef-"),false);
            oled_write_ln(string, false);
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_ENABLE
