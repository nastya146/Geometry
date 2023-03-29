#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <string>

namespace geometry {
  class Point;

  class Vector {
   public:
    Vector();

    Vector(const Vector&);

    Vector& operator=(const Vector& other);

    Vector& operator=(Vector&& other);

    explicit Vector(const Point& point);
    
    Vector(const Point& end, const Point& begin);

    Vector(const int64_t& x, const int64_t& y);

    int64_t SquaredModule() const;

    int64_t Vect(const Vector& other) const;

    int64_t Scalar(const Vector& other) const;

    int64_t VectSign(const Vector& other) const;

    Vector operator+() const;

    Vector operator-() const;

    Vector operator*(int64_t n) const;

    Vector operator*=(int64_t n);

    Vector operator/(int64_t n) const;

    Vector operator/=(int64_t n);

    Vector& operator+=(const Vector& other);

    Vector& operator-=(const Vector& other);

    bool operator==(const Vector& other) const;

    std::string ToString();

    Vector operator+(const Vector&) const;

    Vector operator-(const Vector&) const;

   public:
    int64_t x_;
    int64_t y_;
  };
}

#endif