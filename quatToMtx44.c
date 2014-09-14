#include "gs_math.h"

void quatToMtx44(mtx44 *m, quat q)
{
  float ii = q.i*q.i;
  float ij = q.i*q.j;
  float ik = q.i*q.k;
  float jj = q.j*q.j;
  float jk = q.j*q.k;
  float kk = q.k*q.k;
  float ri = q.r*q.i;
  float rj = q.r*q.j;
  float rk = q.r*q.k;

  m->v[0*4+0] = 1.0f - (2.0f * (jj + kk));
  m->v[0*4+1] = 2.0f * (ij + rk);
  m->v[0*4+2] = 2.0f * (ik - rj);
  m->v[0*4+3] = 0.0f;

  m->v[1*4+0] = 2.0f * (ij - rk);
  m->v[1*4+1] = 1.0f - (2.0f * (ii + kk));
  m->v[1*4+2] = 2.0f * (jk + ri);
  m->v[1*4+3] = 0.0f;

  m->v[2*4+0] = 2.0f * (ik + rj);
  m->v[2*4+1] = 2.0f * (jk - ri);
  m->v[2*4+2] = 1.0f - (2.0f * (ii + jj));
  m->v[2*4+3] = 0.0f;

  m->v[3*4+0] = 0.0f;
  m->v[3*4+1] = 0.0f;
  m->v[3*4+2] = 0.0f;
  m->v[3*4+3] = 1.0f;
}
