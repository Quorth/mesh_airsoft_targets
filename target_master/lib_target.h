typedef struct {
  uint8_t led_id;
  uint8_t pattern;
  uint8_t R;
  uint8_t G;
  uint8_t B;
} led_command;

unsigned long display_timer=0;
//Target node prototypes and declarations
#ifdef TARGET_NODE

#define NODE_ID 2
#define NUM_LEDS 1
boolean int_flag = 0;
boolean int_proc = 0;
uint8_t frame = 0;
const int led_pinout[NUM_LEDS][3] = {{3,5,6}};
led_command lc[NUM_LEDS];

#define NUM_ANIMATIONS 4
const uint8_t mask_frame[NUM_ANIMATIONS][24] = {
                                   {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8},
                                   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,8,8,8,8,8,8,8,8,8},
                                   {0,0,0,0,0,0,8,8,8,8,8,8,0,0,0,0,0,0,8,8,8,8,8,8}
                                  };

#endif
#ifdef TARGET_MASTER
led_command lc;
#endif
