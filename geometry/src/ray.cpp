#include "../segment.h"
#include "../ray.h"
#include "../line.h"
#include "../vector.h"

namespace geometry {
  Ray::Ray() = default;

  Ray::Ray(const Ray&) = default;

  Ray::Ray(const Point& a, const Point& b) : begin_(a), end_(b) {
  }

  Ray& Ray::Move(const Vector& vector) {
    end_.Move(vector);
    begin_.Move(vector);
    return *this;
  }

  bool Ray::ContainsPoint(const Point& point) const {
    Vector first(end_, begin_);
    Vector second(point, begin_);
    return (first.Vect(second) == 0 && first.Scalar(second) >= 0);    
  }

  bool Ray::CrossesSegment(const Segment& segment) const {
    if (ContainsPoint(segment.begin_) || ContainsPoint(segment.end_)) {
      return true;
    }
    Line line(begin_, end_);
    if (!line.CrossesSegment(segment)) {
      return false;
    }
    Vector first(segment.begin_, begin_);
    Vector second(segment.begin_, segment.end_);
    Vector third(begin_, end_);
    int vect1 = first.VectSign(second);
    int vect2 = third.VectSign(second);
    return vect1 * vect2 <= 0 && vect2 != 0;
  }

  std::shared_ptr<IShape> Ray::Clone() const {
    std::shared_ptr<Ray> ptr_to_copy = std::make_shared<Ray>(*this);
    return ptr_to_copy;
  }

  Vector Ray::DirectVector() const {
    return Vector(end_, begin_);
  }

  std::string Ray::ToString() const {
    return std::string ("Ray(" + begin_.ToString() + ", " + DirectVector().ToString() + ')');
  }

  long double Ray::DistToPoint(const Point& point) const {
    Vector vector_first(point, begin_);
    Vector vector_second(end_, begin_);
    Line line(begin_, end_);
    Vector vect(begin_, point);
    return vector_first.Scalar(vector_second) >= 0 ? line.DistToPoint(point) : vect.SquaredModule();
  }
}