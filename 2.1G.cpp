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

  Vector(const Vector& other) = default;

  int SignVect(const Vector& other) const {
    int64_t value = x_ * other.y_ - y_ * other.x_;
    if (value > 0) {
      return 1;
    }
    if (value < 0) {
      return -1;
    }
    return 0;
  }

 private:
  int64_t x_;
  int64_t y_;
};

class Polygon {
 public:
  explicit Polygon(const int& size) : size_(size), array_points_(new Point[size_]) {
  }

  ~Polygon() {
    delete[] array_points_;
  }

  bool IsConvex() const {
    Vector vector1(array_points_[2], array_points_[1]);
    Vector vector0(array_points_[1], array_points_[0]);
    int sign_temp = vector0.SignVect(vector0);
    int sign;
    for (int i = 1; i < size_; ++i) {
      Vector cur(array_points_[(i + 2) % size_], array_points_[(i + 1) % size_]);
      sign = cur.SignVect(vector1);
      vector1 = cur;
      if (sign == 0) {
        continue;
      }
      if (sign * sign_temp < 0) {
        return false;
      }
      sign_temp = sign;
    }
    return true;
  }

  friend std::istream& operator>>(std::istream& is, Polygon& polygon);

 private:
  int size_;
  Point* array_points_;
};

std::istream& operator>>(std::istream& is, Polygon& polygon) {
  for (int i = 0; i < polygon.size_; ++i) {
    is >> polygon.array_points_[i];
  }
  return is;
}

int main() {
  int n;
  std::cin >> n;
  Polygon polygon(n);
  std::cin >> polygon;
  polygon.IsConvex() ? std::cout << "YES" : std::cout << "NO";
}