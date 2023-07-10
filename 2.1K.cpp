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

  int64_t Vect(const Vector& other) const {
    return x_ * other.y_ - y_ * other.x_;
  }

  bool IsRightRotation(const Vector& other) const {
    return Vect(other) > 0;
  }

  void Move(Point& point) const {
    point.x_ -= x_;
    point.y_ -= y_;
  }

  void Move(std::vector<Point>& vector) const {
    size_t size = vector.size();
    for (size_t i = 0; i < size; ++i) {
      Move(vector[i]);
    }
  }

  Vector operator-() const {
    Vector temp(-x_, -y_);
    return temp;
  }

 public:
  int64_t x_;
  int64_t y_;
};

class Polygon {
 public:
  explicit Polygon(const size_t& size) : size_(size), array_points_(size_) {
  }

  ~Polygon() = default;

  int64_t DoubleArea() const {
    int64_t area = 0;
    for (size_t i = 0; i < size_; ++i) {
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
  size_t size_;
  std::vector<Point> array_points_;
};

std::istream& operator>>(std::istream& is, Polygon& polygon) {
  for (size_t i = 0; i < polygon.size_; ++i) {
    is >> polygon.array_points_[i];
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const Polygon& polygon) {
  for (size_t i = 0; i < polygon.size_; ++i) {
    os << polygon.array_points_[i];
  }
  return os;
}

struct Cmp {
  bool operator()(const Point& f, const Point& s) {
    Vector first(f);
    Vector second(s);
    int64_t res = first.Vect(second);
    if (res == 0) {
      return f.x_ <= s.x_ && f.y_ <= s.y_;
    }
    return res > 0;
  }
};

Polygon GrahamConvexHull(std::vector<Point>& vector) {
  std::sort(vector.begin(), vector.end(), [](const Point& a, const Point& b) { return a.x_ < b.x_; });
  size_t ptr = 0;
  for (size_t i = 1; vector[i].x_ == vector[0].x_; ++i) {
    if (vector[i].y_ < vector[ptr].y_) {
      ptr = i;
    }
  }
  std::swap(vector[0], vector[ptr]);
  Vector vect(vector[0]);
  vect.Move(vector);
  std::sort(vector.begin() + 1, vector.end(), Cmp());
  size_t k = 1;
  size_t size = vector.size();
  for (size_t p = 2; p < size; ++p) {
    Vector first(vector[k], vector[k - 1]);
    Vector second(vector[p], vector[k]);
    while (k > 0 && (!first.IsRightRotation(second))) {
      --k;
      if (k > 0) {
        first = Vector(vector[k], vector[k - 1]);
        second = Vector(vector[p], vector[k]);
      }
    }
    std::swap(vector[p], vector[k + 1]);
    ++k;
  }
  vect = -vect;
  vect.Move(vector);
  size_t hull_size = k + 1;
  Polygon convex_hull(hull_size);
  for (size_t i = 0; i < hull_size; ++i) {
    convex_hull[i] = vector[(hull_size - i) % hull_size];
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
  Polygon convex_hull(GrahamConvexHull(vector));
  std::cout << convex_hull.Size() << '\n';
  std::cout << convex_hull;
  std::cout << std::fixed << std::setprecision(1) << static_cast<long double>(convex_hull.DoubleArea()) / 2;
}