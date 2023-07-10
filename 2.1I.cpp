#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdint>

class Point {
 public:
  Point() = default;

  Point(const int64_t& x, const int64_t& y) : x_(x), y_(y) {
  }

  const int64_t& X() const {
    return x_;
  }

  const int64_t& Y() const {
    return y_;
  }

  friend std::istream& operator>>(std::istream& is, Point& p);

 private:
  int64_t x_;
  int64_t y_;
};

std::istream& operator>>(std::istream& is, Point& p) {
  is >> p.x_ >> p.y_;
  return is;
}

class Vector {
 public:
  Vector() = default;

  Vector(const Point& e, const Point& b) : x_(e.X() - b.X()), y_(e.Y() - b.Y()) {
  }

  int64_t Vect(const Vector& other) const {
    return x_ * other.y_ - y_ * other.x_;
  }

 private:
  int64_t x_;
  int64_t y_;
};

class Polygon {
 public:
  explicit Polygon(const size_t& size) : size_(size), array_points_(new Point[size_]) {
  }

  ~Polygon() {
    delete[] array_points_;
  }

  int64_t DoubleArea() const {
    int64_t area = 0;
    for (size_t i = 0; i < size_; ++i) {
      Vector first(array_points_[i], array_points_[0]);
      Vector second(array_points_[(i + 1) % size_], array_points_[i]);
      area += first.Vect(second);
    }
    return std::abs(area);
  }

  friend std::istream& operator>>(std::istream& is, Polygon& polygon);

 private:
  size_t size_;
  Point* array_points_;
};

std::istream& operator>>(std::istream& is, Polygon& polygon) {
  for (size_t i = 0; i < polygon.size_; ++i) {
    is >> polygon.array_points_[i];
  }
  return is;
}

int main() {
  size_t n;
  std::cin >> n;
  Polygon polygon(n);
  std::cin >> polygon;

  long double res = static_cast<long double>(polygon.DoubleArea()) / 2;
  std::cout << std::fixed << std::setprecision(1) << res;
}