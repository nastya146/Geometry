#include "../circle.h"
#include "../segment.h"
#include <cmath>
#include <iomanip>

namespace geometry {
  Circle::Circle() : center_(Point(0, 0)), radius_(0) {
  }

  Circle::Circle(const Point& center, int radius) : center_(center), radius_(radius) {
  }

  Circle& Circle::Move(const Vector& vector) {
    center_.Move(vector);
    return *this;
  }

  bool Circle::ContainsPoint(const Point& point) const {
    Vector vector(point, center_);
    return (radius_ * radius_) >= vector.SquaredModule();
  }

  bool Circle::CrossesSegment(const Segment& segment) const {
    Vector first(center_, segment.begin_);
    Vector second(center_, segment.end_);
    int64_t len_bo = first.SquaredModule();
    int64_t len_eo = second.SquaredModule();
    int64_t r = radius_ * radius_;
    if (r > len_bo && r > len_eo) {
      return false;
    }
    return segment.DistToPoint(center_) <= r;
  }

  std::shared_ptr<IShape> Circle::Clone() const {
    std::shared_ptr<Circle> ptr_to_copy = std::make_shared<Circle>(*this);
    return ptr_to_copy;
  }

  std::string Circle::ToString() const {
    return std::string("Circle(" + center_.ToString() + ", " + std::to_string(radius_) + ')');
  }
}