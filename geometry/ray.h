#ifndef RAY_H
#define RAY_H
#include "point.h"
#include "shape.h"

namespace geometry {
  class Segment;
  class Ray : public IShape {
   public:
    Ray();
    Ray(const Ray&);
    Ray(const Point&, const Point&);
    Ray& Move(const Vector&) override;
    bool ContainsPoint(const geometry::Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    std::shared_ptr<IShape> Clone() const override;
    Vector DirectVector() const;
    std::string ToString() const override;
    long double DistToPoint(const Point&) const;
   private:
    Point begin_;
    Point end_;
  };
}

#endif