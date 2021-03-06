#include "gs_math.h"

void mtx44Scale(mtx44 *m, float x, float y, float z)
{
  int j;

  for(j = 0; j < 4; ++j)
    m->v[0*4+j] *= x;

  for(j = 0; j < 4; ++j)
    m->v[1*4+j] *= y;

  for(j = 0; j < 4; ++j)
    m->v[2*4+j] *= z;
}
