#include "colors.h"
#include <math.h> //compile with -lm
#include <stdlib.h>
#include <time.h>

#define FOO(x) (floor(255 * (x + m)))


/*  Functions for randomly picking the rgb value of a new pixel.
 *  HSV with a static saturation and value for bright colors.
 *  Hue picked using golden ratio to ensure variation.
 */

//Extern variable hue used for color selection.
float hue;

void initialize_hue() {
  srand(time(NULL));
  hue = (float) rand() / (float) RAND_MAX;
}

void hsv_to_rgb(U_SHORT *r, U_SHORT *g, U_SHORT *b, float h, float s, float v) {
  float c, x, m;
  float d = 360 * h;

  c = v * s;
  x = c * (1.0 - fabs(fmod(d / 60.0, 2) - 1.0));
  m = v - c;

  if (0 <= d && d < 60) {
    *r = FOO(c);
    *g = FOO(x);
    *b = FOO(0);
  } else if (60 <= d && d < 120) {
    *r = FOO(x);
    *g = FOO(c);
    *b = FOO(0);
  } else if (120 <= d && d < 180) {
    *r = FOO(0);
    *g = FOO(c);
    *b = FOO(x);
  } else if (180 <= d && d < 240) {
    *r = FOO(0);
    *g = FOO(x);
    *b = FOO(c);
  } else if (240 <= d && d < 300) {
    *r = FOO(x);
    *g = FOO(0);
    *b = FOO(c);
  } else {
    *r = FOO(c);
    *g = FOO(0);
    *b = FOO(x);
  }
}

void generate_rgb(U_SHORT *r, U_SHORT *g, U_SHORT *b) {
  float s = 1, v = 1;
  const float golden_ratio = 0.618033988749895;
  
  hue += golden_ratio;
  hue = fmod(hue, 1);
  hsv_to_rgb(r, g, b, hue, s, v);
}
