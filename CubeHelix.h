#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
  double start;
  double rot;
  double hue;
  double gamma;
}ch_param_s;

typedef struct{
  double r;
  double g;
  double b;
}ch_fsample_s;

ch_fsample_s ch_colorFunction(double x, double start, double rot, double hue, double gamma);

ch_fsample_s* ch_fMap(size_t length, ch_param_s params);
