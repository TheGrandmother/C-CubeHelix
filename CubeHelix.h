/**
 * A basic C implementation of the cubehelix color scheme by David Green.
 *
 * Author: Henrik Sommerland
 * Mail: henrik.sommerland@gmail.com
 *
 * This code is based upon the FORTRAN 77 implementation
 * provided in the paper:
 *
 * A colour scheme for the display of astronomical intensity images
 * By: D. A. Green
 *
 * http://arxiv.org/abs/1108.5083
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
