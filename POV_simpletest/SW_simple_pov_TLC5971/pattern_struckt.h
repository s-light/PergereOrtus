#ifndef POV_SIMPLETEST_SW_SIMPLE_POV_TLC5971_PATTERN_STRUCKT_H_
#define POV_SIMPLETEST_SW_SIMPLE_POV_TLC5971_PATTERN_STRUCKT_H_

#include <Arduino.h>

const uint8_t pixel_line_count = 8;
// const uint8_t pattern_count = 20;

struct tPattern {
  const uint8_t count;
  const uint8_t data[pixel_line_count][80];
};



#endif  // POV_SIMPLETEST_SW_SIMPLE_POV_TLC5971_PATTERN_STRUCKT_H_
