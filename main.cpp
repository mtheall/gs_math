#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "gs_math.h"

typedef std::mt19937                          generator_t;
typedef std::uniform_real_distribution<float> distribution_t;

static inline void
randomMatrix(mtx44 &m, generator_t &g, distribution_t &d)
{
  for(size_t i = 0; i < 16; ++i)
    m.v[i] = d(g);
}

static inline glm::vec3
randomVector(generator_t &g, distribution_t &d)
{
  return glm::vec3(d(g), d(g), d(g));
}

static inline float
randomAngle(generator_t &g, distribution_t &d)
{
  return d(g);
}

static inline quat
randomQuat(generator_t &g, distribution_t &d)
{
  return (quat){ d(g), d(g), d(g), d(g) };
}

static inline glm::mat4
loadMatrix(const mtx44 &m)
{
  return glm::mat4(m.v[ 0], m.v[ 1], m.v[ 2], m.v[ 3],
                   m.v[ 4], m.v[ 5], m.v[ 6], m.v[ 7],
                   m.v[ 8], m.v[ 9], m.v[10], m.v[11],
                   m.v[12], m.v[13], m.v[14], m.v[15]);
}

static inline glm::quat
loadQuat(const quat &q)
{
  return glm::quat(q.r, q.i, q.j, q.k);
}

static inline bool
operator==(const glm::vec3 &lhs, const vec3f &rhs)
{
  return std::abs(lhs.x - rhs.x) < 0.001f
      && std::abs(lhs.y - rhs.y) < 0.001f
      && std::abs(lhs.z - rhs.z) < 0.001f;
}

static inline bool
operator==(const vec3f &lhs, const glm::vec3 &rhs)
{
  return rhs == lhs;
}

static inline bool
operator==(const glm::mat4 &lhs, const mtx44 &rhs)
{
  for(size_t i = 0; i < 4; ++i)
  {
    for(size_t j = 0; j < 4; ++j)
    {
      if(std::abs(lhs[i][j] - rhs.v[i*4+j]) > 0.0001f)
        return false;
    }
  }

  return true;
}

static inline bool
operator==(const mtx44 &lhs, const glm::mat4 &rhs)
{
  return rhs == lhs;
}

static inline bool
operator==(const glm::quat &lhs, const quat &rhs)
{
  return std::abs(lhs.w - rhs.r) < 0.01f
      && std::abs(lhs.x - rhs.i) < 0.01f
      && std::abs(lhs.y - rhs.j) < 0.01f
      && std::abs(lhs.z - rhs.k) < 0.01f;
}

static inline bool
operator==(const quat &lhs, const glm::quat &rhs)
{
  return rhs == lhs;
}

static inline void
print(const vec3f &v)
{
  printf("%s:\n", __PRETTY_FUNCTION__);
  printf("%f %f %f\n", v.x, v.y, v.z);
}

static inline void
print(const glm::vec3 &v)
{
  printf("%s:\n", __PRETTY_FUNCTION__);
  printf("%f %f %f\n", v.x, v.y, v.z);
}

static inline void
print(const mtx44 &m)
{
  printf("%s:\n", __PRETTY_FUNCTION__);
  for(size_t j = 0; j < 4; ++j)
  {
    printf("%f %f %f %f\n",
           m.v[0*4+j],
           m.v[1*4+j],
           m.v[2*4+j],
           m.v[3*4+j]);
  }
}

static inline void
print(const glm::mat4 &m)
{
  printf("%s:\n", __PRETTY_FUNCTION__);
  for(size_t j = 0; j < 4; ++j)
  {
    printf("%f %f %f %f\n",
           m[0][j],
           m[1][j],
           m[2][j],
           m[3][j]);
  }
}

static inline void
print(const quat &q)
{
  printf("%s:\n", __PRETTY_FUNCTION__);
  printf("%f %f %f %f\n", q.r, q.i, q.j, q.k);
}

static inline void
print(const glm::quat &q)
{
  printf("%s:\n", __PRETTY_FUNCTION__);
  printf("%f %f %f %f\n", q.w, q.x, q.y, q.z);
}

static const glm::vec3 x_axis(1.0f, 0.0f, 0.0f);
static const glm::vec3 y_axis(0.0f, 1.0f, 0.0f);
static const glm::vec3 z_axis(0.0f, 0.0f, 1.0f);

static void
check_matrix(generator_t &gen, distribution_t &dist)
{
  // check identity
  {
    mtx44 m;
    mtx44Identity(&m);
    assert(m == glm::mat4());
  }

  for(size_t x = 0; x < 10000; ++x)
  {
    // check multiply
    {
      mtx44 m1, m2;
      randomMatrix(m1, gen, dist);
      randomMatrix(m2, gen, dist);

      glm::mat4 g1 = loadMatrix(m1);
      glm::mat4 g2 = loadMatrix(m2);

      mtx44 result;
      mtx44Multiply(&result, &m1, &m2);
      assert(result == g1*g2);
    }

    // check translate
    {
      mtx44 m;
      randomMatrix(m, gen, dist);

      glm::mat4 g = loadMatrix(m);
      glm::vec3 v = randomVector(gen, dist);

      mtx44Translate(&m, v.x, v.y, v.z);
      assert(m == glm::translate(g, v));
    }

    // check scale
    {
      mtx44 m;
      randomMatrix(m, gen, dist);

      glm::mat4 g = loadMatrix(m);
      glm::vec3 v = randomVector(gen, dist);

      mtx44Scale(&m, v.x, v.y, v.z);
      assert(m == glm::scale(g, v));
    }

    // check rotate
    {
      mtx44 m;
      randomMatrix(m, gen, dist);

      float r = randomAngle(gen, dist);

      glm::mat4 g = loadMatrix(m);
      glm::vec3 v = randomVector(gen, dist);

      mtx44Rotate(&m, (vec3f){ v.x, v.y, v.z }, r);
      assert(m == glm::rotate(g, r, v));
    }

    // check rotate X
    {
      mtx44 m;
      randomMatrix(m, gen, dist);

      float r = randomAngle(gen, dist);

      glm::mat4 g = loadMatrix(m);

      mtx44RotateX(&m, r);
      assert(m == glm::rotate(g, r, x_axis));
    }

    // check rotate Y
    {
      mtx44 m;
      randomMatrix(m, gen, dist);

      float r = randomAngle(gen, dist);

      glm::mat4 g = loadMatrix(m);

      mtx44RotateY(&m, r);
      assert(m == glm::rotate(g, r, y_axis));
    }

    // check rotate Z
    {
      mtx44 m;
      randomMatrix(m, gen, dist);

      float r = randomAngle(gen, dist);

      glm::mat4 g = loadMatrix(m);

      mtx44RotateZ(&m, r);
      assert(m == glm::rotate(g, r, z_axis));
    }
  }
}

static void
check_quaternion(generator_t &gen, distribution_t &dist)
{
  // check identity
  {
    quat      q;
    glm::quat g;

    quatIdentity(&q);
    assert(q == g);
  }

  for(size_t x = 0; x < 10000; ++x)
  {
    // check negation
    {
      quat      q = randomQuat(gen, dist);
      glm::quat g = loadQuat(q);

      assert(quatNegate(q) == -g);
    }

    // check addition
    {
      quat      q1 = randomQuat(gen, dist);
      quat      q2 = randomQuat(gen, dist);

      glm::quat g1 = loadQuat(q1);
      glm::quat g2 = loadQuat(q2);

      assert(quatAdd(q1, q2) == g1+g2);
    }

    // check subtraction
    {
      quat      q1 = randomQuat(gen, dist);
      quat      q2 = randomQuat(gen, dist);

      glm::quat g1 = loadQuat(q1);
      glm::quat g2 = loadQuat(q2);

      assert(quatSubtract(q1, q2) == g1 + (-g2));
    }

    // check scale
    {
      quat      q = randomQuat(gen, dist);
      glm::quat g = loadQuat(q);

      float f = dist(gen);

      assert(quatScale(q, f) == g*f);
    }

    // check normalize
    {
      quat      q = randomQuat(gen, dist);
      glm::quat g = loadQuat(q);

      assert(quatNormalize(q) == glm::normalize(g));
    }

    // check dot
    {
      quat      q1 = randomQuat(gen, dist);
      quat      q2 = randomQuat(gen, dist);
      glm::quat g1 = loadQuat(q1);
      glm::quat g2 = loadQuat(q2);

      assert(std::abs(quatDot(q1, q2) - glm::dot(g1, g2)) < 0.0001f);
    }

    // check conjugate
    {
      quat      q = randomQuat(gen, dist);
      glm::quat g = loadQuat(q);

      assert(quatConjugate(q) == glm::conjugate(g));
    }

    // check inverse
    {
      quat      q = randomQuat(gen, dist);
      glm::quat g = loadQuat(q);

      assert(quatInverse(q) == glm::inverse(g));
    }

    // check quaternion multiplication
    {
      quat      q1 = randomQuat(gen, dist);
      quat      q2 = randomQuat(gen, dist);
      glm::quat g1 = loadQuat(q1);
      glm::quat g2 = loadQuat(q2);

      assert(quatMultiply(q1, q2) == g1*g2);
    }

    // check vector multiplication
    {
      quat      q = randomQuat(gen, dist);
      glm::quat g = loadQuat(q);

      glm::vec3 v = randomVector(gen, dist);

      assert(quatMultiplyVec3f(q, (vec3f){ v.x, v.y, v.z }) == g*v);
    }

    // check rotation
    {
      quat      q = randomQuat(gen, dist);
      glm::quat g = loadQuat(q);

      glm::vec3 v = randomVector(gen, dist);
      float     r = randomAngle(gen, dist);

      assert(quatRotate(q, (vec3f){ v.x, v.y, v.z }, r) == glm::rotate(g, r, v));
    }

    // check rotate X
    {
      quat      q = randomQuat(gen, dist);
      glm::quat g = loadQuat(q);

      float     r = randomAngle(gen, dist);

      assert(quatRotateX(q, r) == glm::rotate(g, r, x_axis));
    }

    // check rotate Y
    {
      quat      q = randomQuat(gen, dist);
      glm::quat g = loadQuat(q);

      float     r = randomAngle(gen, dist);

      assert(quatRotateY(q, r) == glm::rotate(g, r, y_axis));
    }

    // check rotate Z
    {
      quat      q = randomQuat(gen, dist);
      glm::quat g = loadQuat(q);

      float     r = randomAngle(gen, dist);

      assert(quatRotateZ(q, r) == glm::rotate(g, r, z_axis));
    }

    // check conversion from matrix
    {
      quat      q = randomQuat(gen, dist);
      glm::quat g = loadQuat(q);

      mtx44 m;
      quatToMtx44(&m, q);

      assert(m == glm::mat4_cast(g));
    }
  }
}

int main(int argc, char *argv[])
{
  std::random_device rd;
  generator_t        gen(rd());
  distribution_t     dist(-10.0f, 10.0f);

  check_matrix(gen, dist);
  check_quaternion(gen, dist);

  return EXIT_SUCCESS;
}
