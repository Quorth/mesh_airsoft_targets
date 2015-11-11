typedef struct {
  uint8_t led_id;
  uint8_t pattern;
  uint8_t R;
  uint8_t G;
  uint8_t B;
} led_command;

//Target node prototypes and declarations
#ifdef TARGET_NODE

typedef struct {
  uint8_t pin_R;
  uint8_t pin_G;
  uint8_t pin_B;
} led_pinout ;

#endif
