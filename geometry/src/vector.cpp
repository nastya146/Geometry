#include "../vector.h"

#include "../point.h"

namespace geometry {
Vector::Vector() = default;

Vector::Vector(const Vector&) = default;

Vector& Vector::operator=(const Vector& other) = default;

Vector& Vector::operator=(Vector&& other) = default;

Vector::Vector(const Point& point) : x_(point.x_), y_(point.y_) {}

Vector::Vector(const Point& end, const Point& begin)
    : x_(end.x_ - begin.x_), y_(end.y_ - begin.y_) {}

Vector::Vector(const int64_t& x, const int64_t& y) : x_(x), y_(y) {}

int64_t Vector::SquaredModule() const {
  return x_ * x_ + y_ * y_;
}

int64_t Vector::Vect(const Vector& other) const {
  return x_ * other.y_ - y_ * other.x_;
}

int64_t Vector::Scalar(const Vector& other) const {
  return x_ * other.x_ + y_ * other.y_;
}

int64_t Vector::VectSign(const Vector& other) const {
  int64_t value = Vect(other);
  if (value > 0) {
    return 1;
  }
  if (value < 0) {
    return -1;
  }
  return 0;
}

Vector Vector::operator+() const {
  auto copy = *this;
  return copy;
}

Vector Vector::operator-() const {
  Point p(-x_, -y_);
  Vector copy(p);
  return copy;
}

Vector Vector::operator*(int64_t n) const {
  return Vector(x_ * n, y_ * n);
}

Vector Vector::operator*=(int64_t n) {
  *this = *this * n;
  return *this;
}

Vector Vector::operator/(int64_t n) const {
  return Vector(x_ / n, y_ / n);
}

Vector Vector::operator/=(int64_t n) {
  *this = *this / n;
  return *this;
}

Vector& Vector::operator+=(const Vector& other) {
  x_ += other.x_;
  y_ += other.y_;
  return *this;
}

Vector& Vector::operator-=(const Vector& other) {
  x_ -= other.x_;
  y_ -= other.y_;
  return *this;
}

bool Vector::operator==(const Vector& other) const {
  return x_ == other.x_ && y_ == other.y_;
}

std::string Vector::ToString() {
  return std::string ("Vector(" + std::to_string(x_) + ", " +
                       std::to_string(y_) + ")");
}

Vector Vector::operator+(const Vector& a) const {
  Vector res(x_ + a.x_, y_ + a.y_);
  return res;
}

Vector Vector::operator-(const Vector& a) const {
  Vector res(x_ - a.x_, y_ - a.y_);
  return res;
}
}