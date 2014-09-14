#pragma once

#ifdef ARM11
#include <3ds.h>
#else
#include <stdint.h>
typedef int32_t s32;
#endif

#include <math.h>

/*! 3D int vector */
typedef struct
{
  s32 x; /*!< x-component */
  s32 y; /*!< y-component */
  s32 z; /*!< z-component */
} vec3i;

/*! 3D float vector */
typedef struct
{
  float x; /*!< x-component */
  float y; /*!< y-component */
  float z; /*!< z-component */
} vec3f;

/*! 4x4 float matrix (column-major) */
typedef struct
{
  float v[16]; /*!< array of components */
} mtx44;

/*! Quaternion */
typedef struct
{
  float r; /*!< real component */
  float i; /*!< i-component */
  float j; /*!< j-component */
  float k; /*!< k-component */
} quat;

/*! Add two vec3i's component-wise
 *
 *  @param[in] lhs Left side
 *  @param[in] rhs Right side
 *
 *  @returns lhs+rhs
 */
static inline vec3i
vec3iAdd(vec3i lhs, vec3i rhs)
{
  return (vec3i){ lhs.x + rhs.x,
                  lhs.y + rhs.y,
                  lhs.z + rhs.z };
}

/*! Subtract two vec3i's component-wise
 *
 *  @param[in] lhs Left side
 *  @param[in] rhs Right side
 *
 *  @returns lhs+rhs
 */
static inline vec3i
vec3iSubtract(vec3i lhs, vec3i rhs)
{
  return (vec3i){ lhs.x - rhs.x,
                  lhs.y - rhs.y,
                  lhs.z - rhs.z };
}

/*! Scale a vec3i component-wise
 *
 *  @param[in] v Vector
 *  @param[in] s Scale
 *
 *  @returns v*s
 */
static inline vec3i
vec3iScale(vec3i v, s32 s)
{
  return (vec3i){ v.x*s, v.y*s, v.z*s };
}

/*! vec3i cross-product
 *
 *  @param[in] lhs Left side
 *  @param[in] rhs Right side
 *
 *  @returns lhs x rhs
 */
static inline vec3i
vec3iCross(vec3i lhs, vec3i rhs)
{
  return (vec3i){ lhs.y*rhs.z - lhs.z*rhs.y,
                  lhs.z*rhs.x - lhs.x*rhs.z,
                  lhs.x*rhs.y - lhs.y*rhs.x };
}

/*! Add two vec3f's component-wise
 *
 *  @param[in] lhs Left side
 *  @param[in] rhs Right side
 *
 *  @returns lhs+rhs
 */
static inline vec3f
vec3fAdd(vec3f lhs, vec3f rhs)
{
  return (vec3f){ lhs.x + rhs.x,
                  lhs.y + rhs.y,
                  lhs.z + rhs.z };
}

/*! Subtract two vec3f's component-wise
 *
 *  @param[in] lhs Left side
 *  @param[in] rhs Right side
 *
 *  @returns lhs+rhs
 */
static inline vec3f
vec3fSubtract(vec3f lhs, vec3f rhs)
{
  return (vec3f){ lhs.x - rhs.x,
                  lhs.y - rhs.y,
                  lhs.z - rhs.z };
}

/*! Scale a vec3f component-wise
 *
 *  @param[in] v Vector
 *  @param[in] s Scale
 *
 *  @returns v*s
 */
static inline vec3f
vec3fScale(vec3f v, float s)
{
  return (vec3f){ v.x*s, v.y*s, v.z*s };
}

/*! vec3f cross-product
 *
 *  @param[in] lhs Left side
 *  @param[in] rhs Right side
 *
 *  @returns lhs x rhs
 */
static inline vec3f
vec3fCross(vec3f lhs, vec3f rhs)
{
  return (vec3f){ lhs.y*rhs.z - lhs.z*rhs.y,
                  lhs.z*rhs.x - lhs.x*rhs.z,
                  lhs.x*rhs.y - lhs.y*rhs.x };
}

/*! Normaliaze a vec3f
 *
 *  @param[in] v Vector
 *
 *  @returns normalized v
 */
static inline vec3f
vec3fNormalize(vec3f v)
{
  float len = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
  return (vec3f){ v.x/len, v.y/len, v.z/len };
}

/*! Convert vec3i to vec3f
 *
 *  @param[in] v int vector
 *
 *  @returns float vector
 */
static inline vec3f
vec3iToVec3f(vec3i v)
{
  return (vec3f){ (float)v.x, (float)v.y, (float)v.z };
}

/*! Initialize a quaternion
 *
 *  @param[out] q Quaternion
 */
static inline void
quatIdentity(quat *q)
{
  q->r = 1.0f;
  q->i = q->j = q->k = 0.0f;
}

/*! Negate a quaternion component-wise
 *
 *  @param[in] q Quaternion
 *
 *  @returns negated q
 */
static inline quat
quatNegate(quat q)
{
  return (quat){ -q.r, -q.i, -q.j, -q.k };
}

/*! Add two quaternions component-wise
 *
 *  @param[in] lhs Left side
 *  @param[in] rhs Right side
 *
 *  @returns lhs+rhs
 */
static inline quat
quatAdd(quat lhs, quat rhs)
{
  return (quat){ lhs.r + rhs.r,
                 lhs.i + rhs.i,
                 lhs.j + rhs.j,
                 lhs.k + rhs.k };
}

/*! Subtract two quaternions component-wise
 *
 *  @param[in] lhs Left side
 *  @param[in] rhs Right side
 *
 *  @returns lhs-rhs
 */
static inline quat
quatSubtract(quat lhs, quat rhs)
{
  return (quat){ lhs.r - rhs.r,
                 lhs.i - rhs.i,
                 lhs.j - rhs.j,
                 lhs.k - rhs.k };
}

/*! Scale a quaternion component-wise
 *
 *  @param[in] lhs Left side
 *  @param[in] rhs Right side
 *
 *  @returns lhs+rhs
 */
static inline quat
quatScale(quat q, float s)
{
  return (quat){ q.r*s, q.i*s, q.j*s, q.k*s };
}

/*! Normaliaze a quaternion
 *
 *  @param[in] q Quaternion
 *
 *  @returns normalized q
 */
static inline quat
quatNormalize(quat q)
{
  float len = sqrtf(q.r*q.r + q.i*q.i + q.j*q.j + q.k*q.k);

  return (quat){ q.r/len, q.i/len, q.j/len, q.k/len };
}

/*! Quaternion dot-product
 *
 *  @param[in] lhs Left side
 *  @param[in] rhs Right side
 *
 *  @returns lhs . rhs
 */
static inline float
quatDot(quat lhs, quat rhs)
{
  return lhs.r*rhs.r
       + lhs.i*rhs.i
       + lhs.j*rhs.j
       + lhs.k*rhs.k;
}

/*! Quaternion conjugate
 *
 *  @param[in] q Quaternion
 *
 *  @returns conjugate of q
 */
static inline quat
quatConjugate(quat q)
{
  return (quat){ q.r, -q.i, -q.j, -q.k };
}

/*! Quaternion inverse
 *
 *  @param[in] q Quaternion
 *
 *  @returns inverse of q
 */
static inline quat
quatInverse(quat q)
{
  quat  c = quatConjugate(q);
  float d = quatDot(q, q);
  return (quat){ c.r/d,
                 c.i/d,
                 c.j/d,
                 c.k/d };
}

/*! Multiply two quaternions (concatenation)
 *
 *  @param[in] lhs Left side
 *  @param[in] rhs Right side
 *
 *  @returns lhs*rhs
 */
static inline quat
quatMultiply(quat lhs, quat rhs)
{
  return (quat){ lhs.r*rhs.r - lhs.i*rhs.i - lhs.j*rhs.j - lhs.k*rhs.k,
                 lhs.r*rhs.i + lhs.i*rhs.r + lhs.j*rhs.k - lhs.k*rhs.j,
                 lhs.r*rhs.j + lhs.j*rhs.r + lhs.k*rhs.i - lhs.i*rhs.k,
                 lhs.r*rhs.k + lhs.k*rhs.r + lhs.i*rhs.j - lhs.j*rhs.i };
}

/*! Multiply a quaternion with a vector
 *
 *  @param[in] lhs Left side
 *  @param[in] rhs Right side
 *
 *  @returns lhs*rhs
 */
static inline vec3f
quatMultiplyVec3f(quat lhs, vec3f rhs)
{
  vec3f qv  = (vec3f){ lhs.i, lhs.j, lhs.k };
  vec3f uv  = vec3fCross(qv, rhs);
  vec3f uuv = vec3fCross(qv, uv);

  uv  = vec3fScale(uv, 2.0f * lhs.r);
  uuv = vec3fScale(uuv, 2.0f);

  return vec3fAdd(rhs, vec3fAdd(uv, uuv));
}

/*! Rotate a quaternion about an an axis
 *
 *  @param[in] q       Quaternion
 *  @param[in] axis    Axis to rotate about
 *  @param[in] radians Angle to rotate
 *
 *  @returns transformed quaternion
 */
static inline quat
quatRotate(quat q, vec3f axis, float radians)
{
  float halfAngle = radians/2;
  float s = sinf(halfAngle);

  axis = vec3fNormalize(axis);

  quat tmp = { cosf(halfAngle),
               axis.x * s,
               axis.y * s,
               axis.z * s };

  return quatMultiply(q, tmp);
}

/*! Rotate a quaternion about the X-axis
 *
 *  @param[in] q       Quaternion
 *  @param[in] radians Angle to rotate
 *
 *  @returns transformed quaternion
 */
static inline quat
quatRotateX(quat q, float radians)
{
  float c = cosf(radians/2);
  float s = sinf(radians/2);

  return (quat){ q.r*c - q.i*s,
                 q.r*s + q.i*c,
                 q.j*c + q.k*s,
                 q.k*c - q.j*s };
}

/*! Rotate a quaternion about the Y-axis
 *
 *  @param[in] q       Quaternion
 *  @param[in] radians Angle to rotate
 *
 *  @returns transformed quaternion
 */
static inline quat quatRotateY(quat q, float radians)
{
  float c = cosf(radians/2);
  float s = sinf(radians/2);

  return (quat){ q.r*c - q.j*s,
                 q.i*c - q.k*s,
                 q.r*s + q.j*c,
                 q.k*c + q.i*s };

}

/*! Rotate a quaternion about the Z-axis
 *
 *  @param[in] q       Quaternion
 *  @param[in] radians Angle to rotate
 *
 *  @returns transformed quaternion
 */
static inline quat quatRotateZ(quat q, float radians)
{
  float c = cosf(radians/2);
  float s = sinf(radians/2);

  return (quat){ q.r*c - q.k*s,
                 q.i*c + q.j*s,
                 q.j*c - q.i*s,
                 q.r*s + q.k*c };
}

#ifdef __cplusplus
extern "C" {
#endif

/*! Fill in identity matrix
 *
 *  @param[out] m Result matrix
 */
void mtx44Identity(mtx44 *m);

/*! Multiply two mtx44's
 *
 *  @param[out] m   Result matrix
 *  @param[in]  lhs Left side
 *  @param[in]  rhs Right side
 */
void mtx44Multiply(mtx44 *m, const mtx44 *lhs, const mtx44 *rhs);

/*! Apply translation to a matrix
 *
 *  @param[in,out] m Matrix to transform
 *  @param[in]     x X-translation
 *  @param[in]     y Y-translation
 *  @param[in]     z Z-translation
 */
void mtx44Translate(mtx44 *m, float x, float y, float z);

/*! Apply rotation to a matrix
 *
 *  @param[in,out] m    Matrix to transform
 *  @param[in]     axis Axis to rotate about
 *  @param[in]     r    Angle to rotate (in radians)
 */
void mtx44Rotate(mtx44 *m, vec3f axis, float r);

/*! Apply rotation to a matrix about the X-Axis
 *
 *  @param[in,out] m Matrix to transform
 *  @param[in]     r Angle to rotate (in radians)
 */
void mtx44RotateX(mtx44 *m, float r);

/*! Apply rotation to a matrix about the Y-Axis
 *
 *  @param[in,out] m Matrix to transform
 *  @param[in]     r Angle to rotate (in radians)
 */
void mtx44RotateY(mtx44 *m, float r);

/*! Apply rotation to a matrix about the Z-Axis
 *
 *  @param[in,out] m Matrix to transform
 *  @param[in]     r Angle to rotate (in radians)
 */
void mtx44RotateZ(mtx44 *m, float r);

/*! Apply scale to a matrix
 *
 *  @param[in,out] m Matrix to transform
 *  @param[in]     x X-scale
 *  @param[in]     y Y-scale
 *  @param[in]     z Z-scale
 */
void mtx44Scale(mtx44 *m, float x, float y, float z);

/*! Fill in a projection matrix
 *
 *  @param[out] m      Result matrix
 *  @param[in]  fovy   Field-of-view angle (in radians), in the Y-direction
 *  @param[in]  aspect Aspect ratio (y/x)
 *  @param[in]  near   Near clipping plane
 *  @param[in]  far    Far clipping plane
 */
void mtx44Projection(mtx44 *m, float fovy, float aspect, float near, float far);

/*! Convert a quaternion into a 4x4 matrix
 *
 *  @param[out] m Result matrix
 *  @param[in]  q Quaternion
 */
void quatToMtx44(mtx44 *m, quat q);

#ifdef __cplusplus
}
#endif
