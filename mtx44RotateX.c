#include <math.h>
#include "gs_math.h"

void mtx44RotateX(mtx44 *m, float r)
{
  float s = sinf(r);
  float c = cosf(r);

  mtx44 tmp;

  int j;

  for(j = 0; j < 4; ++j)
    tmp.v[0*4+j] = m->v[0*4+j];

  for(j = 0; j < 4; ++j)
    tmp.v[1*4+j] = m->v[1*4+j]*c + m->v[2*4+j]*s;

  for(j = 0; j < 4; ++j)
    tmp.v[2*4+j] = m->v[1*4+j]*-s + m->v[2*4+j]*c;

  for(j = 0; j < 4; ++j)
    tmp.v[3*4+j] = m->v[3*4+j];

  *m = tmp;
}
