#include "vector.h"

struct Vector new_vector(double _x, double _y)
{
    struct Vector v_a;
    v_a.x = _x;
    v_a.y = _y;

    return v_a;
}

struct Vector equal(const int i)
{
    struct Vector mv;
    mv.x = i;
    mv.y = i;
    return mv;
}

struct Vector add(const struct Vector vec_a, const struct Vector vec_b)
{
    struct Vector mv;
    mv.x = vec_a.x + vec_b.x;
    mv.y = vec_a.y + vec_b.y;
    return mv;
}

struct Vector sub(const struct Vector vec_a, const struct Vector vec_b)
{
    struct Vector mv;
    mv.x = vec_a.x - vec_b.x;
    mv.y = vec_a.y - vec_b.y;
    return mv;
}

struct Vector multiply_vector(const struct Vector vec_a, const struct Vector vec_b)
{
    struct Vector mv;
    mv.x = vec_a.x * vec_b.x;
    mv.y = vec_a.y * vec_b.y;
    return mv;
}

struct Vector multiply_number(const struct Vector vec, const double d)
{
    struct Vector mv;
    mv.x = vec.x * d;
    mv.y = vec.y * d;
    return mv;
}

struct Vector devide_vector(const struct Vector vec_a, const struct Vector vec_b)
{
    struct Vector mv;
    mv.x = vec_a.x / vec_b.x;
    mv.y = vec_a.y / vec_b.y;
    return mv;
}

struct Vector devide_number(const struct Vector vec, const double d)
{
    struct Vector mv;
    mv.x = vec.x / d;
    mv.y = vec.y / d;
    return mv;
}

double absolute(const struct Vector vec)
{
    double x = vec.x;
    double y = vec.y;
    return sqrt(x * x + y * y);
}