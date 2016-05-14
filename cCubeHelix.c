/**
 * A basic C implementation of the cubehelix color scheme by David Green.
 *
 * Documentation can be found in cCubeHelix.h
 *
 * Author: Henrik Sommerland
 * Main: henrik.sommerland@gmail.com
 *
 * This code is based upon the FORTRAN 77 implementation
 * provided in the paper:
 *
 * A colour scheme for the display of astronomical intensity images
 * By: D. A. Green
 *
 * http://arxiv.org/abs/1108.5083
 *
 *
 * 
 *
 * This is free and unencumbered software released into the public domain.
 * 
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 * 
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 * For more information, please refer to <http://unlicense.org/>
 **/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

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


ch_fsample_s ch_colorFunction(double x, double start, double rot, double hue, double gamma){

  ch_fsample_s sample;

  double angle;
  double amplitude;

  double tr;
  double tg;
  double tb;

  x = x > 1.0 ? 1.0 : (x < 0 ? 0.0 : x);
  angle = 2.0*M_PI*( (start/3.0) + 1 + rot*x);
  x = pow(x,gamma);
  amplitude = hue * x * (1 - x)/2.0;
  tr = x + amplitude*(-0.14861*cos(angle) + 1.78277*sin(angle));
  tg = x + amplitude*(-0.29227*cos(angle) - 0.90649*sin(angle));
  tb = x + amplitude*(1.97294*cos(angle));

  sample.r = tr > 1.0 ? 1.0 : (tr < 0 ? 0 : tr);
  sample.g = tg > 1.0 ? 1.0 : (tg < 0 ? 0 : tg);
  sample.b = tb > 1.0 ? 1.0 : (tb < 0 ? 0 : tb);

  return sample;

}

ch_fsample_s* ch_fMap(size_t length, ch_param_s params){
  double x;
  double angle;
  double amplitude;

  double tr;
  double tg;
  double tb;

  ch_fsample_s* samples = (ch_fsample_s*)malloc(sizeof(ch_fsample_s)*length);

  for(int i = 0; i < length;i++){
    x = ((double)i)/(length-1);
    samples[i] = ch_colorFunction(x,params.start, params.rot, params.hue, params.gamma);
  }

  return samples;
}

unsigned char* ch_cMap(size_t length, ch_param_s params){
  ch_fsample_s* samples = ch_fMap(length, params);
  unsigned char* map = (unsigned char*)malloc(sizeof(char) * 3*length);
  for(int i = 0; i < length; i++){
    map[i*3] = (unsigned char)(samples[i].r*255);
    map[i*3 + 1] = (unsigned char)(samples[i].g*255);
    map[i*3 + 2] = (unsigned char)(samples[i].b*255);
  }
  free(samples);
  return map;

}


int main(){

  ch_param_s params;
  params.start = 0.5;
  params.rot = -1.5;
  params.hue = 1.0;
  params.gamma = 1.0;

  ch_fsample_s* samples = ch_fMap(100,params);
  
  for( int i = 0; i < 100; i++){
    double v = (samples[i].r + samples[i].r + samples[i].r)/3;
    printf("val: %f\n",v);
  }

  unsigned char* char_samples = ch_cMap(100,params);
  
  for( int i = 0; i < 100; i++){
    unsigned char v = (char_samples[i*3] + char_samples[i*3+1] + char_samples[i*3+2])/3;
    printf("val: %d\n",v);
  }

  return 0;
}


