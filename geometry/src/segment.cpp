#include "../segment.h"
#include "../ray.h"
#include "../line.h"


namespace geometry {
  Segment::Segment() = default;

  Segment::Segment(const Point& begin, const Point& end) : begin_(begin), end_(end) {
  }

  Segment::Segment(const Segment&) = default;
 
  Segment& Segment::Move(const Vector& vector) {
    end_.Move(vector);
    begin_.Move(vector);
    return *this;
  }

  bool Segment::ContainsPoint(const Point& point) const {
    if (begin_ == end_) {
      return begin_ == point;
    }
    Ray ray_first(begin_, end_);
    Ray ray_second(end_, begin_);
    return ray_first.ContainsPoint(point) && ray_second.ContainsPoint(point);
  }

  bool Segment::CrossesSegment(const Segment& segment) const {
    Line line_f(begin_, end_);
    Line line_s(segment.begin_, segment.end_);
    Segment segment_f(begin_, end_);
    Segment segment_s(segment.begin_, segment.end_);
    if (line_f.ContainsPoint(segment.begin_) && line_f.ContainsPoint(segment.end_)) {
      return ((segment_f.ContainsPoint(segment.begin_) || segment_f.ContainsPoint(segment.end_)) &&
              (segment_s.ContainsPoint(begin_) || segment_s.ContainsPoint(end_))) ||
              (segment_s.ContainsPoint(begin_) && segment_s.ContainsPoint(end_)) ||
              ((segment_f.ContainsPoint(segment.begin_) && segment_f.ContainsPoint(segment.end_)));
    }
    return line_f.Value(segment.begin_) * line_f.Value(segment.end_) <= 0 && line_s.Value(begin_) * line_s.Value(end_) <= 0;
  }

  bool Segment::CrossesLine(const Line& line) const {
    return line.Value(end_) * line.Value(begin_) <= 0;
  }

  int64_t Segment::SquaredModule() const {
    return Vector(end_, begin_).SquaredModule();
  }

  std::shared_ptr<IShape> Segment::Clone() const {
    std::shared_ptr<Segment> ptr_to_copy = std::make_shared<Segment>(*this);
    return ptr_to_copy;
  }

  std::string Segment::ToString() const {
    return std::string ("Segment(" + begin_.ToString() + ", " + end_.ToString() + ')');
  }

  long double Segment::DistToPoint(const Point& point) const {
    Ray first(begin_, end_);
    Ray second(end_, begin_);
    return std::max(first.DistToPoint(point), second.DistToPoint(point));    
  }
}