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
#define RESET KC_NO // key is not present
#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used

#define U_RDO KC_AGIN
#define U_PST S(KC_INS)
#define U_CPY C(KC_INS)
#define U_CUT S(KC_DEL)
#define U_UND KC_UNDO

enum userspace_layers {
	COLEMAK_DH = 0,
    MEDIA,
    NAV,
    MOUSE,
    SYM,
    NUM,
    FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* colemak DH
     * ,---------------------------------------. .---------------------------------------.
     * |   Q   |   W   |   F   |   P   |   B   | |   J   |   L   |   U   |   Y   |   '   |
     * |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
     * |   A   |   R   |   S   |   T   |   G   | |   M   |   N   |   E   |   I   |   O   |
     * |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
     * |   Z   |   X   |   C   |   S   |   V   | |   K   |   H   |   ,   |   .   |   /   |
     * `---------------.                       | |                       .---------------'
     *                 |-------+-------+-------| |-------+-------+-------|
     *                 |  ESC  |  SPC  |  TAB  | |  ENT  |  BSPC |  DEL  |
     *                 `-----------------------' '-----------------------'
     *                   Media    Nav    Mouse      Sym     Num    Func
     */
	[COLEMAK_DH] = LAYOUT_split_3x5_3(
    KC_Q,              KC_W,              KC_F,              KC_P,              KC_B,              KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,
    LGUI_T(KC_A),      LALT_T(KC_R),      LCTL_T(KC_S),      LSFT_T(KC_T),      KC_G,              KC_M,              LSFT_T(KC_N),      LCTL_T(KC_E),      LALT_T(KC_I),      LGUI_T(KC_O),
    KC_Z,              ALGR_T(KC_X),      KC_C,              KC_D,              KC_V,              KC_K,              KC_H,              KC_COMM,           KC_DOT,            KC_SLSH,
                       LT(MEDIA, KC_ESC), LT(NAV, KC_SPC),   LT(MOUSE, KC_TAB), LT(SYM, KC_ENT),   LT(NUM, KC_BSPC),  LT(FUNC, KC_DEL)
	),

    /* Nav
     * ,---------------------------------------. .---------------------------------------.
     * | Reset |       |       |       |       | |  PgUp |  Home |  Up   |  End  |  Ins  |
     * |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
     * | Super |  Alt  |  Ctrl | Shift |       | |  PgDn |  Left |  Down | Right |  Caps |
     * |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
     * |       |       |       |       |       | |  Undo |  Cut  |  Copy | Paste |  Redo |
     * `---------------.                       | |                       .---------------'
     *                 |-------+-------+-------| |-------+-------+-------|
     *                 |       |       |       | |  ENT  |  BSPC |  DEL  |
     *                 `-----------------------' '-----------------------'
     *                            Nav
     */
    [NAV] = LAYOUT_split_3x5_3(
    RESET,   U_NA,    U_NA,    U_NA,    U_NA,    KC_PGUP, KC_HOME, KC_UP,   KC_END,   KC_INS,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,    KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_CAPS,
    U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_UND,   U_CUT,   U_CPY,   U_PST,    U_RDO,
             U_NA,    U_NA,    U_NA,    KC_ENT,  KC_BSPC, KC_DEL
  ),

    /* Mouse
     * ,---------------------------------------. .---------------------------------------.
     * | Reset |       |       |       |       | |  Redo | Paste |  Copy |  Cut  | Undo  |
     * |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
     * | Super |  Alt  |  Ctrl | Shift |       | |       |  Left |  Down |   Up  | Right |
     * |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
     * |       |       |       |       |       | |       |  Wh-L |  Wh-D |  Wh-U |  Wh-R |
     * `---------------.                       | |                       .---------------'
     *                 |-------+-------+-------| |-------+-------+-------|
     *                 |       |       |       | |   1   |   2   |   3   |
     *                 `-----------------------' '-----------------------'
     *                                   Mouse
     */
    [MOUSE] = LAYOUT_split_3x5_3(
    RESET,   U_NA,    U_NA,    U_NA,    U_NA,    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,    U_NU,    KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
    U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NU,    KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,
             U_NA,    U_NA,    U_NA,    KC_BTN1, KC_BTN2, KC_BTN3
  ),

    /* Media
     * ,---------------------------------------. .---------------------------------------.
     * | Reset |       |       |       |       | | RGB-T |RGB-MOD|RGB-HUI|RGB-SAI|RGB-VAI|
     * |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
     * | Super |  Alt  |  Ctrl | Shift |       | |       |  <<   | VolDn | VolUp |  >>   |
     * |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
     * |       |       |       |       |       | |       |       |       |  BriU |  BriD |
     * `---------------.                       | |                       .---------------'
     *                 |-------+-------+-------| |-------+-------+-------|
     *                 |       |       |       | |  Stop |  Play | Mute  |
     *                 `-----------------------' '-----------------------'
     *                   Media
     */
    [MEDIA] = LAYOUT_split_3x5_3(
    RESET,   U_NA,    U_NA,    U_NA,    U_NA,    RGB_TOG,        RGB_MOD,    RGB_HUI, RGB_SAI, RGB_VAI,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,    U_NU,           KC_MPRV,    KC_VOLD, KC_VOLU, KC_MNXT,
    U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NU,           U_NU,       U_NU,    KC_BRIU, KC_BRID,
             U_NA,    U_NA,    U_NA,    KC_MSTP, KC_MPLY, KC_MUTE
  ),

    /* Num
     * ,---------------------------------------. .---------------------------------------.
     * |   [   |   7   |   8   |   9   |   ]   | | DT_UP |       |       |       | Reset |
     * |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
     * |   ;   |   4   |   5   |   6   |   =   | | DT_DN | Shift |  Ctrl |  Atl  | Super |
     * |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
     * |   `   |   1   |   2   |   3   |   \   | | DT_PRN|       |       |       |       |
     * `---------------.                       | |                       .---------------'
     *                 |-------+-------+-------| |-------+-------+-------|
     *                 |   0   |   .   |   -   | |       |       |       |
     *                 `-----------------------' '-----------------------'
     *                                                      Num
     */
    [NUM] = LAYOUT_split_3x5_3(
    KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC, DT_UP,     U_NA,    U_NA,    U_NA,    RESET,
    KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,  DT_DOWN,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_GRV,  KC_1,    KC_2,    KC_3,    UK_BSLS, DT_PRNT,   U_NA,    U_NA,    KC_ALGR, U_NA,
             KC_0,    KC_DOT,  KC_MINS, U_NA,    U_NA,      U_NA
  ),

    /* Sym
     * ,---------------------------------------. .---------------------------------------.
     * |   {   |   &   |   *   |   (   |   }   | |       |       |       |       | Reset |
     * |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
     * |   :   |   $   |   %   |   ^   |   +   | |       | Shift |  Ctrl |  Atl  | Super |
     * |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
     * |   ~   |   !   |   "   |   #   |   |   | |       |       |       |       |       |
     * `---------------.                       | |                       .---------------'
     *                 |-------+-------+-------| |-------+-------+-------|
     *                 |   (   |   )   |   _   | |       |       |       |
     *                 `-----------------------' '-----------------------'
     *                                              Sym
     */
    [SYM] = LAYOUT_split_3x5_3(
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, U_NA,    U_NA,    U_NA,    U_NA,    RESET,
    KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS, U_NA,    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    UK_TILD, KC_EXLM, KC_AT,   UK_HASH, UK_PIPE, U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
             KC_LPRN, KC_RPRN, KC_UNDS, U_NA,    U_NA,    U_NA
  ),

    /* Func
     * ,---------------------------------------. .---------------------------------------.
     * |  F12  |   F7  |   F8  |  F9   | PrtScn| | Scrot |       |       |       | Reset |
     * |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
     * |  F11  |   F4  |   F5  |  F6   | Srlck | |       | Shift |  Ctrl |  Atl  | Super |
     * |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
     * |  F10  |   F1  |   F2  |  F3   | Break | |       |       |       |       |       |
     * `---------------.                       | |                       .---------------'
     *                 |-------+-------+-------| |-------+-------+-------|
     *                 |   APP |  SPC  |  TAB  | |       |       |       |
     *                 `-----------------------' '-----------------------'
     *                                                             Func
     */
    [FUNC] = LAYOUT_split_3x5_3(
    KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR, S(G(KC_PSCR)), U_NA,    U_NA,    U_NA,    RESET,
    KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SLCT, U_NA,          KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, U_NA,          U_NA,    U_NA,    KC_ALGR, U_NA,
             KC_APP,  KC_SPC,  KC_TAB,  U_NA,    U_NA,    U_NA
    )
};

