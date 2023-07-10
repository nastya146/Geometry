#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdint>
#include <vector>

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
  os << p.x_ << " " << p.y_;
  return os;
}

class Vector {
 public:
  Vector() = default;

  Vector(const Point& e, const Point& b) : x_(e.x_ - b.x_), y_(e.y_ - b.y_) {
  }

  Vector(const Vector& other) = default;

  int64_t Vect(const Vector& other) const {
    return x_ * other.y_ - y_ * other.x_;
  }

  int SignVect(const Vector& other) const {
    int64_t value = Vect(other);
    if (value > 0) {
      return 1;
    }
    if (value < 0) {
      return -1;
    }
    return 0;
  }

  int64_t Scalar(const Vector& other) const {
    return x_ * other.x_ + y_ * other.y_;
  }

 public:
  int64_t x_;
  int64_t y_;
};

class Ray;
class Segment {
 public:
  Segment(const Point& a, const Point& b) : a_(a), b_(b) {
  }

  bool ContainsPoint(const Point& point) const;

 public:
  Point a_;
  Point b_;
};

class Line {
 public:
  Line(const Point& a, const Point& b) : a_(a), b_(b) {
  }

  int64_t Value(const Point& p) const {
    int64_t b = -a_.x_ + b_.x_;
    int64_t a = a_.y_ - b_.y_;
    int64_t c = -a * a_.x_ - b * a_.y_;
    return a * p.x_ + b * p.y_ + c;
  }

  bool CrossesSegment(const Segment& segment) const {
    return Value(segment.a_) * Value(segment.b_) <= 0;
  }

 private:
  Point a_;
  Point b_;
};

class Ray {
 public:
  Ray(const Point& begin, const Point& end) : begin_(begin), end_(end) {
  }

  bool ContainsPoint(const Point& point) const {
    Vector first(begin_, end_);
    Vector second(begin_, point);
    return first.Vect(second) == 0 && first.Scalar(second) >= 0;
  }

  bool CrossesSegment(const Segment& segment) const {
    if (ContainsPoint(segment.a_) || ContainsPoint(segment.b_)) {
      return true;
    }
    Line line(begin_, end_);
    if (!line.CrossesSegment(segment)) {
      return false;
    }
    Vector first(segment.a_, begin_);
    Vector second(segment.a_, segment.b_);
    Vector third(begin_, end_);
    int vect1 = first.SignVect(second);
    int vect2 = third.SignVect(second);
    return vect1 * vect2 <= 0 && vect2 != 0;
  }

 private:
  Point begin_;
  Point end_;
};

bool Segment::ContainsPoint(const Point& point) const {
  Ray first(a_, b_);
  Ray second(b_, a_);
  return first.ContainsPoint(point) && second.ContainsPoint(point);
}

class Polygon {
 public:
  explicit Polygon(const size_t& size) : size_(size), array_points_(size_) {
  }

  ~Polygon() = default;

  bool InPolygon(const Point& point) const {
    int64_t res = 0;
    Point other(point.x_ + 1, point.y_);
    Ray ray(point, other);
    for (int64_t i = 0; i < size_; ++i) {
      Segment side(array_points_[i], array_points_[(i + 1) % size_]);
      if (side.ContainsPoint(point)) {
        return true;
      }
      if (ray.ContainsPoint(array_points_[i]) && ray.ContainsPoint(array_points_[(i + 1) % size_])) {
      } else if (ray.ContainsPoint(array_points_[i])) {
        res += array_points_[(i + 1) % size_].y_ > array_points_[i].y_;
      } else if (ray.ContainsPoint(array_points_[(i + 1) % size_])) {
        res += array_points_[i].y_ > array_points_[(i + 1) % size_].y_;
      } else {
        int n = ray.CrossesSegment(side);
        res += n;
      }
    }
    return res % 2 == 1;
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
  os << '\n';
  return os;
}

int main() {
  int n;
  std::cin >> n;
  Point p;
  std::cin >> p;
  Polygon polygon(n);
  std::cin >> polygon;
  polygon.InPolygon(p) ? std::cout << "YES" : std::cout << "NO";
}