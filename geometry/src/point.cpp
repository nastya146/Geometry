#include "../vector.h"
#include "../point.h"
#include "../segment.h"

namespace geometry {
  Point::Point() = default;

  Point::Point(const Point&) = default;

  Point::Point(int64_t x, int64_t y) : x_(x), y_(y) {
  }

  Point& Point::Move(const Vector& vector) {
    x_ += vector.x_;
    y_ += vector.y_;
    return *this;
  }

  bool Point::ContainsPoint(const Point& point) const {
    return point.x_ == x_ && point.y_ == y_;
  }

  bool Point::CrossesSegment(const Segment& segment) const {
    return segment.ContainsPoint(*this);
  }

  std::shared_ptr<IShape> Point::Clone() const {
    std::shared_ptr<Point> ptr_to_copy = std::make_shared<Point>(*this);
    return ptr_to_copy;
  }

  bool Point::operator==(const Point& other) const {
    return other.x_ == x_ && other.y_ == y_;
  }

  std::string Point::ToString() const {
    return std::string ("Point(" + std::to_string(x_) + ", " + std::to_string(y_) + ')');
  }

  Vector Point::operator-(const Point& other) const {
    return {x_ - other.x_, y_ - other.y_};
  }

  Point operator+(const Point& a, const Point& b) {
    return Point {a.x_ + b.x_, a.y_ + b.y_};
  }

  Vector operator-(const Point& a, const Point& b) {
    return Vector {a.x_ - b.x_, a.y_ - b.y_};
  }
}