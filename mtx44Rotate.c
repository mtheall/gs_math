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

#if 1
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
#else
  result.v[0*4+0] = m->v[0*4+0]*rhs.v[0*4+0] + m->v[1*4+0]*rhs.v[0*4+1] + m->v[2*4+0]*rhs.v[0*4+2];
  result.v[0*4+1] = m->v[0*4+1]*rhs.v[0*4+0] + m->v[1*4+1]*rhs.v[0*4+1] + m->v[2*4+1]*rhs.v[0*4+2];
  result.v[0*4+2] = m->v[0*4+2]*rhs.v[0*4+0] + m->v[1*4+2]*rhs.v[0*4+1] + m->v[2*4+2]*rhs.v[0*4+2];
  result.v[0*4+3] = m->v[0*4+3]*rhs.v[0*4+0] + m->v[1*4+3]*rhs.v[0*4+1] + m->v[2*4+3]*rhs.v[0*4+2];

  result.v[1*4+0] = m->v[0*4+0]*rhs.v[1*4+0] + m->v[1*4+0]*rhs.v[1*4+1] + m->v[2*4+0]*rhs.v[1*4+2];
  result.v[1*4+1] = m->v[0*4+1]*rhs.v[1*4+0] + m->v[1*4+1]*rhs.v[1*4+1] + m->v[2*4+1]*rhs.v[1*4+2];
  result.v[1*4+2] = m->v[0*4+2]*rhs.v[1*4+0] + m->v[1*4+2]*rhs.v[1*4+1] + m->v[2*4+2]*rhs.v[1*4+2];
  result.v[1*4+3] = m->v[0*4+3]*rhs.v[1*4+0] + m->v[1*4+3]*rhs.v[1*4+1] + m->v[2*4+3]*rhs.v[1*4+2];

  result.v[2*4+0] = m->v[0*4+0]*rhs.v[2*4+0] + m->v[1*4+0]*rhs.v[2*4+1] + m->v[2*4+0]*rhs.v[2*4+2];
  result.v[2*4+1] = m->v[0*4+1]*rhs.v[2*4+0] + m->v[1*4+1]*rhs.v[2*4+1] + m->v[2*4+1]*rhs.v[2*4+2];
  result.v[2*4+2] = m->v[0*4+2]*rhs.v[2*4+0] + m->v[1*4+2]*rhs.v[2*4+1] + m->v[2*4+2]*rhs.v[2*4+2];
  result.v[2*4+3] = m->v[0*4+3]*rhs.v[2*4+0] + m->v[1*4+3]*rhs.v[2*4+1] + m->v[2*4+3]*rhs.v[2*4+2];

  result.v[3*4+0] = m->v[3*4+0];
  result.v[3*4+1] = m->v[3*4+1];
  result.v[3*4+2] = m->v[3*4+2];
  result.v[3*4+3] = m->v[3*4+3];
#endif

  *m = result;
}
