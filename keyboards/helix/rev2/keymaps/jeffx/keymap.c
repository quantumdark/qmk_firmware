#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _FUNC,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  FUNC,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#if HELIX_ROWS == 4
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  /* QWERTY
 * .-----------------------------------------------------.                      .-----------------------------------------------------.
 * | TAB    | Q      | W      | E      | R      | T      |                      | Y      | U      | I      | O      | P      | BACKSP |
 * |--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+-----------------|
 * | LCTRL  | A      | S      | D      | F      | G      |                      | H      | J      | K      | L      | ;      | ENTER  |
 * |--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+-----------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      |                      | N      | M      | ,      | .      | /      | RSHIFT |
 * |--------+--------+--------+--------+--------+--------+--------.    .--------+--------+--------+--------------------------+--------|
 * | ESC    | OS     | ALT    | EISU   | LOWER  | ASD    | SPACE  |    | LOWER  | RAISE  | KANA   | LEFT   | DOWN   | UP     | RSHIFT |
 * '--------------------------------------------------------------'    '--------------------------------------------------------------'
 */
 [_QWERTY] = LAYOUT( \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,  \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    _______, KC_LGUI, KC_LALT, _______, _______, FUNC,    KC_SPC,       LOWER,   RAISE,   KC_DEL,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

  /* LOWER
 * .-----------------------------------------------------.                      .-----------------------------------------------------.
 * | TAB    | 1      | 2      | 3      | 4      | 5      |                      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+-----------------|
 * | LCTRL  | A      | S      | D      | F      | G      |                      | H      | J      | K      | L      | ;      | ENTER  |
 * |--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+-----------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      |                      | N      | M      | ,      | .      | /      | RSHIFT |
 * |--------+--------+--------+--------+--------+--------+--------.    .--------+--------+--------+--------------------------+--------|
 * | ESC    | OS     | ALT    | EISU   | LOWER  | ASD    | SPACE  |    | LOWER  | RAISE  | KANA   | LEFT   | DOWN   | UP     | RSHIFT |
 * '--------------------------------------------------------------'    '--------------------------------------------------------------'
 */
[_LOWER] = LAYOUT( \
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
    _______, _______, _______, _______, _______, _______,                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT, _______, \
    _______, _______, _______, _______, _______, _______,                        KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, _______, \
    _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT \
),

  /* RAISE
 * .-----------------------------------------------------.                      .-----------------------------------------------------.
 * | TAB    | !      | @      | #      | $      | %      |                      | ^      | &      | *      | (      | )      | BACKSP |
 * |--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+-----------------|
 * | LCTRL  | A      | S      | D      | F      | G      |                      | H      | J      | K      | L      | ;      | ENTER  |
 * |--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+-----------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      |                      | N      | M      | ,      | .      | /      | RSHIFT |
 * |--------+--------+--------+--------+--------+--------+--------.    .--------+--------+--------+--------------------------+--------|
 * | ESC    | OS     | ALT    | EISU   | LOWER  | ASD    | SPACE  |    | LOWER  | RAISE  | KANA   | LEFT   | DOWN   | UP     | RSHIFT |
 * '--------------------------------------------------------------'    '--------------------------------------------------------------'
 */
[_RAISE] = LAYOUT( \
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
    _______, _______, _______, _______, _______, _______,                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DQUO, _______, \
    _______, _______, _______, _______, _______, _______,                        KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, _______, \
    _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT \
),

  /* FUNC
 * .-----------------------------------------------------.                      .-----------------------------------------------------.
 * | TAB    | F1     | F2     | F3     | F4     | F5     |                      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+-----------------|
 * | LCTRL  | F6     | F7     | F8     | F9     | F10    |                      | LEFT   | DOWN   | UP     | RIGHT  | ;      | ENTER  |
 * |--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+-----------------+--------|
 * | LSHIFT | Z      | X      | C      | F11    | F12    |                      | N      | M      | ,      | .      | /      | RSHIFT |
 * |--------+--------+--------+--------+--------+--------+--------.    .--------+--------+--------+--------------------------+--------|
 * | ESC    | OS     | ALT    | EISU   | LOWER  | ASD    | SPACE  |    | LOWER  | RAISE  | KANA   | LEFT   | DOWN   | UP     | RSHIFT |
 * '--------------------------------------------------------------'    '--------------------------------------------------------------'
 */
[_FUNC] = LAYOUT( \
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                          _______, _______, _______, _______, _______, KC_MUTE, \
    _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                         KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, KC_MPLY, \
    _______, _______, _______, _______, KC_F11,  KC_F12,                         _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT \
),
  
  /* LOWER
 * .-----------------------------------------------------.                      .-----------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      |                      | 6      | 7      | 8      | 9      | 10     | BACKSP |
 * |--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+-----------------|
 * | TAB    | A      | S      | D      | F      | G      |                      | H      | J      | K      | L      | ;      | DEL    |
 * |--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+-----------------+--------|
 * | LCTRL  | Z      | X      | C      | V      | B      |                      | N      | M      | ,      | .      | /      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------.    .--------+--------+--------+--------------------------+--------|
 * | LSHIFT | OS     | ALT    | EISU   | LOWER  | ASD    | SPACE  |    | LOWER  | RAISE  | KANA   | ,      | .      | /      | RSHIFT |
 * '--------------------------------------------------------------'    '--------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT( \
    _______, RESET,   _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                        _______, _______, RGBRST,  _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                        _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
    _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, RGB_SMOD,RGB_HUD, RGB_SAD, RGB_VAD \
)
};

#else
#error "undefined keymaps"
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(16);
          #endif
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(15);
          #endif
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case FUNC:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(15);
          #endif
        }
        layer_on(_FUNC);
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_FUNC);
        TOG_STATUS = false;
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
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
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// hook point for 'led_test' keymap
//   'default' keymap's led_test_init() is empty function, do nothing
//   'led_test' keymap's led_test_init() force rgblight_mode_noeeprom(35);
__attribute__ ((weak))
void led_test_init(void) {}

void matrix_scan_user(void) {
     led_test_init();
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_FUNC (1<<_FUNC)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_RAISE:
           matrix_write_P(matrix, PSTR("Raise"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("Lower"));
           break;
        case L_FUNC:
           matrix_write_P(matrix, PSTR("Function"));
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("Adjust"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
