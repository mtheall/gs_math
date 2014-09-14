#include "gs_math.h"

void mtx44Multiply(mtx44 *m, const mtx44 *lhs, const mtx44 *rhs)
{
  int i, j;

  for(i = 0; i < 4; ++i)
  {
    for(j = 0; j < 4; ++j)
    {
      m->v[i*4+j] = lhs->v[0*4+j]*rhs->v[i*4+0]
                  + lhs->v[1*4+j]*rhs->v[i*4+1]
                  + lhs->v[2*4+j]*rhs->v[i*4+2]
                  + lhs->v[3*4+j]*rhs->v[i*4+3];
    }
  }
}
