#include "gs_math.h"

void mtx44Identity(mtx44 *m)
{
  int i, j;
  for(i = 0; i < 4; ++i)
  {
    for(j = 0; j < 4; ++j)
    {
      m->v[i*4+j] = (i == j) ? 1.0f : 0.0f;
    }
  }
}
