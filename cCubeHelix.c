/**C=====================================================================72
C Calculates a "cube helix" colour table. The colours are a tapered
C helix around the diagonal of the [R,G,B] colour cube, from black
C [0,0,0] to white [1,1,1] Deviations away from the diagonal vary
C quadratically, increasing from zero at black, to a maximum, then
C decreasing to zero at white, all the time rotating in colour.
C
C The input parameters controlling the colour helix are:
C
C START colour (1=red, 2=green, 3=blue; e.g. 0.5=purple);
C ROTS rotations in colour (typically -1.5 to 1.5, e.g. -1.0
C is one blue->green->red cycle);
C HUE for hue intensity scaling (in the range 0.0 (B+W) to 1.0
C to be strictly correct, larger values may be OK with
C particular start/end colours);
C GAMMA set the gamma correction for intensity.
C
C The routine returns a colour table NLEV elements long in RED, GRN
C and BLU (each element in the range 0.0 to 1.0), and the numbers,
C NLO and NHI, of red, green or blue values that had to be clipped
C because they were too low or too high.
C---------------------------------------------------------------------72
C Dave Green --- MRAO --- 2011 June 13th
C---------------------------------------------------------------------72
C See:
C Green, D. A., 2011, Bulletin of the Astronomical Society of India,
C Vol.39, p.289
C---------------------------------------------------------------------72
SUBROUTINE CUBHLX(START,ROTS,HUE,GAMMA,NLEV,RED,GRN,BLU,NLO,NHI)
C ================================================================
C
INTEGER NLEV,I,NLO,NHI
REAL START,ROTS,HUE,GAMMA
REAL RED(NLEV),GRN(NLEV),BLU(NLEV)
REAL PI,FRACT,ANGLE,AMP
C
PI=4.0*ATAN(1.0)
NLO=0
NHI=0
C
DO 1000 I=1,NLEV
FRACT=FLOAT(I-1)/FLOAT(NLEV-1)
ANGLE=2*PI*(START/3.0+1.0+ROTS*FRACT)
FRACT=FRACT**GAMMA
AMP=HUE*FRACT*(1-FRACT)/2.0
RED(I)=FRACT+AMP*(-0.14861*COS(ANGLE)+1.78277*SIN(ANGLE))
GRN(I)=FRACT+AMP*(-0.29227*COS(ANGLE)-0.90649*SIN(ANGLE))
BLU(I)=FRACT+AMP*(+1.97294*COS(ANGLE))
C
IF(RED(I).LT.0.0)THEN
RED(I)=0.0
NLO=NLO+1
ENDIF
IF(GRN(I).LT.0.0)THEN
GRN(I)=0.0
NLO=NLO+1
ENDIF
IF(BLU(I).LT.0.0)THEN
BLU(I)=0.0
NLO=NLO+1
ENDIF
C
IF(RED(I).GT.1.0)THEN
RED(I)=1.0
NHI=NHI+1
ENDIF
IF(GRN(I).GT.1.0)THEN
GRN(I)=1.0
NHI=NHI+1
ENDIF
IF(BLU(I).GT.1.0)THEN
BLU(I)=1.0
NHI=NHI+1
ENDIF
1000 CONTINUE
C
RETURN
END**/


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
    angle = 2.0*M_PI*( (params.start/3.0) + 1 + params.rot*x);
    x = pow(x,params.gamma);
    amplitude = params.hue * x * (1 - x)/2.0;
    tr = x + amplitude*(-0.14861*cos(angle) + 1.78277*sin(angle));
    tg = x + amplitude*(-0.29227*cos(angle) - 0.90649*sin(angle));
    tb = x + amplitude*(1.97294*cos(angle));

    samples[i].r = tr > 1.0 ? 1.0 : (tr < 0 ? 0 : tr);
    samples[i].g = tg > 1.0 ? 1.0 : (tg < 0 ? 0 : tg);
    samples[i].b = tb > 1.0 ? 1.0 : (tb < 0 ? 0 : tb);
  }

  return samples;

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

  return 0;
}


