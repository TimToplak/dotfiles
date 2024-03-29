#include QMK_KEYBOARD_H

enum custom_keycodes {
	CCARON = SAFE_RANGE,
	ZCARON,
	SCARON,
	THUMB_UP
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_5x6(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, 		KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL,
					 KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, 		KC_Z, KC_U, KC_I, KC_O, KC_P, KC_QUOT,
					 KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, 	KC_H, KC_J, KC_K, KC_L, KC_ENT, KC_SCLN,
					 KC_LCTL, KC_Y, KC_X, KC_C, KC_V, KC_B, 	KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
						KC_LGUI, KC_LALT, 										KC_EQL, KC_MINS, 
							MO(2), KC_SPC, 									KC_BSPC, MO(1), 
								KC_LALT, KC_ESC, 						KC_ENT, KC_LALT, 
									KC_ENT, KC_LGUI, 			KC_GRV, KC_TAB),
					 
	[1] = LAYOUT_5x6(KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, 	 	KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
					 KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_GRV, 		ZCARON, KC_HOME, KC_UP, KC_END, KC_TRNS, KC_PLUS,
					 KC_TRNS, KC_TRNS, KC_TRNS, KC_LPRN, KC_RPRN, UC(0x20AC), 	SCARON, KC_LEFT, KC_DOWN, KC_RGHT, KC_MINS, KC_PIPE,
					 KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_TRNS, 		CCARON, KC_TRNS, KC_TRNS, KC_TRNS, KC_EQL, KC_UNDS,
					 	KC_TRNS, KC_TRNS, 																	KC_TRNS, KC_P0,
					 		KC_TRNS, KC_TRNS,														 KC_TRNS, KC_TRNS,
					 			KC_TRNS, KC_TRNS,												 KC_TRNS, KC_TRNS,
					 				KC_TRNS, KC_TRNS,									 KC_TRNS, KC_TRNS),

	[2] = LAYOUT_5x6(KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,		 			 KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
					 KC_TRNS, KC_TRNS, KC_WH_D, KC_MS_U, KC_WH_U, KC_LBRC,		 KC_TRNS, KC_7, KC_8, KC_9, KC_SLCK, KC_TRNS,
					 KC_TRNS, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN2,		 KC_TRNS, KC_4, KC_5, KC_6, KC_TRNS, KC_TRNS,
					 KC_TRNS, KC_TRNS, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU, 		 KC_TRNS, KC_1, KC_2, KC_3, KC_TRNS, KC_TRNS,
					 	KC_MPRV, KC_MNXT,														 KC_0, THUMB_UP, 
							KC_TRNS, KC_TRNS,											 KC_TRNS, KC_TRNS,
								KC_TRNS, KC_TRNS, 									KC_TRNS, KC_TRNS,
									KC_TRNS, KC_TRNS,							 KC_TRNS, KC_TRNS)
};
