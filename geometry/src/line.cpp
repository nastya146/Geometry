#include "../vector.h"
#include "../segment.h"
#include "../line.h"

namespace geometry {
  Line::Line() = default;

  Line::Line(const Point& a, const Point& b) : a_(a), b_(b) {
  }

  Line& Line::Move(const Vector& vector) {
    a_.Move(vector);
    b_.Move(vector);
    return *this;
  }

  bool Line::ContainsPoint(const Point& point) const {
    Vector first(a_, point);
    Vector second(a_, b_);
    return first.Vect(second) == 0;
  }

  bool Line::CrossesSegment(const Segment& segment) const {
    return segment.CrossesLine(*this);
  }

  std::shared_ptr<IShape> Line::Clone() const {
    std::shared_ptr<Line> ptr_to_copy = std::make_shared<Line>(*this);
    return ptr_to_copy;
  }

  std::string Line::ToString() const {
    int64_t b = -a_.x_ + b_.x_;
    int64_t a = a_.y_ - b_.y_;
    int64_t c = -a * a_.x_ - b * a_.y_;
    return  std::string("Line(" + std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(c) + ')');
  }

  int64_t Line::Value(const Point& p) const {
    int64_t b = -a_.x_ + b_.x_;
    int64_t a = a_.y_ - b_.y_;
    int64_t c = -a * a_.x_ - b * a_.y_;
    return a * p.x_ + b * p.y_ + c;
  }

  long double Line::DistToPoint(const Point& point) const {
    int64_t b = -a_.x_ + b_.x_;
    int64_t a = a_.y_ - b_.y_;
    int64_t val = Value(point);
    return static_cast<long double> (val * val) / (a * a + b * b);
  }
}