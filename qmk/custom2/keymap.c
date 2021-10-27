#include QMK_KEYBOARD_H

enum custom_keycodes {
	CCARON = SAFE_RANGE,
	ZCARON,
	SCARON,
	THUMB_UP,
	RUNNER,
	HIDE
};

static bool shift_held = false;
// winCompose config:
// <Multi_key> <s> : "š"
// <Multi_key> <n> : "č"
// <Multi_key> <z> : "ž"

// <Multi_key> <S> : "Š"
// <Multi_key> <N> : "Č"
// <Multi_key> <Z> : "Ž"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch(keycode) {
		case THUMB_UP:
			if (record->event.pressed) {
				send_unicode_string("👍");
			}
			return false;
			break;
		case RUNNER:
			if (record->event.pressed) {
				SEND_STRING(SS_DOWN(X_LALT)SS_DOWN(X_SPC)SS_UP(X_SPC)SS_UP(X_LALT));
			}
			return false;
			break;
		case HIDE:
			if (record->event.pressed) {
				SEND_STRING(SS_DOWN(X_LGUI)"n"SS_UP(X_LGUI));
			}
			return false;
			break;
		case KC_LSFT:
			shift_held = record->event.pressed;
			return true;
			break;
		case ZCARON: {
			if (record->event.pressed) {
				if (shift_held) {
					// send_unicode_string("Ž");
					// send_unicode_hex_string("17D");
					SEND_STRING(SS_DOWN(X_RCTL)"Z"SS_UP(X_RCTL));
				} else {
					// send_unicode_string("ž");
					// send_unicode_hex_string("17E");
					SEND_STRING(SS_DOWN(X_RCTL)"z"SS_UP(X_RCTL));
				}
			}
			return false;
			break;
		}
		case CCARON: {
			if (record->event.pressed) {
				if (shift_held) {
					// send_unicode_string("Č");
					// send_unicode_hex_string("10C");
					SEND_STRING(SS_DOWN(X_RCTL)"N"SS_UP(X_RCTL));

				} else {
					// send_unicode_string("č");
					// send_unicode_hex_string("10D");
					SEND_STRING(SS_DOWN(X_RCTL)"n"SS_UP(X_RCTL));
				}
			}
			return false;
			break;
		}
		case SCARON: {
			if (record->event.pressed) {
				if (shift_held) {
					// send_unicode_string("Š");
					// send_unicode_hex_string("160");
					SEND_STRING(SS_DOWN(X_RCTL)"S"SS_UP(X_RCTL));
				} else {
					// send_unicode_string("š");
					// send_unicode_hex_string("161");
					SEND_STRING(SS_DOWN(X_RCTL)"s"SS_UP(X_RCTL));
				}
			}
			return false;
			break;
		}
	};
	return true;
}


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
		switch(biton32(layer_state)){
			case 2:
				if (clockwise){
                    tap_code(KC_VOLU);
                } else{
                    tap_code(KC_VOLD);
                }
				break;
			default:
                if (clockwise){
                    tap_code(KC_F14);
                } else{
                    tap_code(KC_F15);
                }
                break;
			}
		
    }
    return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_5x6(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, 		KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL,
					 KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, 		KC_Z, KC_U, KC_I, KC_O, KC_P, KC_QUOT,
					 KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, 	KC_H, KC_J, KC_K, KC_L, KC_ENT, KC_SCLN,
					 KC_LCTL, KC_Y, KC_X, KC_C, KC_V, KC_B, 	KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
						KC_MPLY, KC_MUTE, 										KC_EQL, KC_MINS, 
							MO(2), _______, 								KC_BSPC, MO(1), 
								KC_LALT, KC_SPC, 						RUNNER, KC_F13, 
									_______, KC_LGUI, 			HIDE, _______),
					 
	[1] = LAYOUT_5x6(KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, 	 	KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
					 _______, _______, _______, KC_LCBR, KC_RCBR, KC_GRV, 		ZCARON, KC_HOME, KC_UP, KC_END, _______, KC_PLUS,
					 _______, _______, _______, KC_LPRN, KC_RPRN, UC(0x20AC), 	SCARON, KC_LEFT, KC_DOWN, KC_RGHT, KC_MINS, KC_PIPE,
					 _______, _______, _______, KC_LBRC, KC_RBRC, _______, 		CCARON, _______, _______, _______, KC_EQL, KC_UNDS,
					 	_______, _______, 																	_______, KC_P0,
					 		_______, _______,														 _______, _______,
					 			_______, _______,												 _______, _______,
					 				_______, _______,									 _______, _______),

	[2] = LAYOUT_5x6(KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,		 			 KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
					 _______, _______, KC_WH_D, KC_MS_U, KC_WH_U, KC_LBRC,		 _______, KC_7, KC_8, KC_9, KC_SLCK, _______,
					 _______, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN2,		 _______, KC_4, KC_5, KC_6, _______, _______,
					 _______, _______, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU, 		 _______, KC_1, KC_2, KC_3, _______, _______,
					 	KC_MPRV, KC_MNXT,														 KC_0, THUMB_UP, 
							_______, _______,											 _______, _______,
								_______, _______, 									_______, _______,
									_______, _______,							 _______, _______)
};
