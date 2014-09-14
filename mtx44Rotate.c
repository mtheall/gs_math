#include <math.h>
#include "gs_math.h"

void mtx44Rotate(mtx44 *m, vec3f axis, float r)
{
  axis = vec3fNormalize(axis);

  mtx44 rhs, result;

  int i, j;

  float s = sinf(r);
  float c = cosf(r);
  float t = 1 - c;

  float x = axis.x;
  float y = axis.y;
  float z = axis.z;

  rhs.v[0*4+0] = t*x*x + c;
  rhs.v[0*4+1] = t*x*y + s*z;
  rhs.v[0*4+2] = t*x*z - s*y;

  rhs.v[1*4+0] = t*y*x - s*z;
  rhs.v[1*4+1] = t*y*y + c;
  rhs.v[1*4+2] = t*y*z + s*x;

  rhs.v[2*4+0] = t*z*x + s*y;
  rhs.v[2*4+1] = t*z*y - s*x;
  rhs.v[2*4+2] = t*z*z + c;

  for(i = 0; i < 3; ++i)
  {
    for(j = 0; j < 4; ++j)
    {
      result.v[i*4+j] = m->v[0*4+j]*rhs.v[i*4+0]
                      + m->v[1*4+j]*rhs.v[i*4+1]
                      + m->v[2*4+j]*rhs.v[i*4+2];
    }
  }

  for(j = 0; j < 4; ++j)
    result.v[3*4+j] = m->v[3*4+j];

  *m = result;
}
