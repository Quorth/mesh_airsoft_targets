typedef struct {
  uint8_t led_id;
  uint8_t pattern;
  uint8_t R;
  uint8_t G;
  uint8_t B;
} led_command;

uint32_t display_timer=0;
//Target node prototypes and declarations
#ifdef TARGET_NODE

#define NODE_ID 2
#define NUM_LEDS 1
boolean int_flag = 0;
const int led_pinout[NUM_LEDS][3] = {{11,12,13}};
led_command lc[NUM_LEDS];

#endif
