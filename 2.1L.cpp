#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <iterator>

class Point {
 public:
  Point() = default;

  Point(const int64_t& x, const int64_t& y) : x_(x), y_(y) {
  }

  bool operator==(const Point& other) const {
    return other.x_ == x_ && other.y_ == y_;
  }

 public:
  int64_t x_;
  int64_t y_;
};

std::istream& operator>>(std::istream& is, Point& p) {
  is >> p.x_ >> p.y_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << p.x_ << " " << p.y_ << "\n";
  return os;
}

class Vector {
 public:
  Vector() = default;

  explicit Vector(const Point& e) : x_(e.x_), y_(e.y_) {
  }

  Vector(const int64_t& x, const int64_t& y) : x_(x), y_(y) {
  }

  Vector(const Point& e, const Point& b) : x_(e.x_ - b.x_), y_(e.y_ - b.y_) {
  }

  int64_t SquareMod() const {
    return x_ * x_ + y_ * y_;
  }

  int64_t Vect(const Vector& other) const {
    return x_ * other.y_ - y_ * other.x_;
  }

 public:
  int64_t x_;
  int64_t y_;
};

class Polygon {
 public:
  explicit Polygon(const int64_t& size) : size_(size), array_points_(size_) {
  }

  ~Polygon() = default;

  int64_t DoubleArea() const {
    int64_t area = 0;
    for (int64_t i = 0; i < size_; ++i) {
      Vector first(array_points_[i], array_points_[0]);
      Vector second(array_points_[(i + 1) % size_], array_points_[i]);
      area += first.Vect(second);
    }
    return std::abs(area);
  }

  Point& operator[](size_t i) {
    return array_points_[i];
  }

  size_t Size() const {
    return size_;
  }

  friend std::istream& operator>>(std::istream& is, Polygon& polygon);
  friend std::ostream& operator<<(std::ostream& os, const Polygon& polygon);

 private:
  int64_t size_;
  std::vector<Point> array_points_;
};

std::istream& operator>>(std::istream& is, Polygon& polygon) {
  for (int64_t i = 0; i < polygon.size_; ++i) {
    is >> polygon.array_points_[i];
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const Polygon& polygon) {
  for (int64_t i = 0; i < polygon.size_; ++i) {
    os << polygon.array_points_[i];
  }
  return os;
}

Polygon JarvisConvexHull(std::vector<Point>& vector) {
  std::sort(vector.begin(), vector.end(), [](const Point& a, const Point& b) { return a.x_ < b.x_; });
  int64_t ptr = 0;
  for (int64_t i = 1; vector[i].x_ == vector[0].x_; ++i) {
    if (vector[i].y_ < vector[ptr].y_) {
      ptr = i;
    }
  }
  std::swap(vector[0], vector[ptr]);
  vector.push_back(vector[0]);
  int64_t size = vector.size();
  int64_t convex_hull_size = 0;
  for (int64_t i = 0; i < size - 1; ++i) {
    Point point(vector[i]);
    int64_t ptr = i + 1;
    for (int64_t p = i + 2; p < size; ++p) {
      Vector v1(vector[ptr], point);
      Vector v2(vector[p], point);
      int64_t res = v1.Vect(v2);
      if (res == 0) {
        ptr = v1.SquareMod() < v2.SquareMod() ? p : ptr;
        continue;
      }
      ptr = res < 0 ? ptr : p;
    }
    std::swap(vector[i + 1], vector[ptr]);
    if (vector[i + 1] == vector[0]) {
      convex_hull_size = ++i;
      break;
    }
  }
  Polygon convex_hull(convex_hull_size);
  for (int64_t i = 0; i < convex_hull_size; ++i) {
    convex_hull[i] = vector[i];
  }
  return convex_hull;
}

int main() {
  size_t n;
  std::cin >> n;
  std::vector<Point> vector(n);
  for (auto& point : vector) {
    std::cin >> point;
  }
  Polygon convex_hull(JarvisConvexHull(vector));
  std::cout << convex_hull.Size() << '\n';
  std::cout << convex_hull;
  std::cout << std::fixed << std::setprecision(1) << static_cast<long double>(convex_hull.DoubleArea()) / 2;
}