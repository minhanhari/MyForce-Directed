#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

struct Vector
{
  double x;
  double y;
};

struct Vector new_vector(double x, double y);

struct Vector equal(const int i);

struct Vector add(const struct Vector vec_a, const struct Vector vec_b);

struct Vector sub(const struct Vector vec_a, const struct Vector vec_b);

struct Vector multiply_vector(const struct Vector vec_a, const struct Vector vec_b);

struct Vector multiply_number(const struct Vector vec, double d);

#define multiply(_1, _2) _Generic((_2),               \
                                  const struct Vector \
                                  : multiply_vector,  \
                                    double            \
                                  : multiply_number)(_1, _2)

struct Vector devide_vector(const struct Vector vec_a, const struct Vector vec_b);

struct Vector devide_number(const struct Vector vec, double d);

#define devide(_1, _2) _Generic((_2),               \
                                const struct Vector \
                                : devide_vector,    \
                                  double            \
                                : devide_number)(_1, _2)

double absolute(const struct Vector vec);

#endif // VECTOR_H