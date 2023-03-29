#ifndef POLYGON_H
#define POLYGON_H
#include "point.h"
#include <vector>

namespace geometry {
  class Segment;
  class Polygon : public IShape {
   public:
    Polygon();
    Polygon(const Polygon&);
    explicit Polygon(const std::vector<Point>& vector);

    Polygon& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& segment) const override;

    std::shared_ptr<IShape> Clone() const override;

    std::string ToString() const override;

   private:
    int64_t size_;
    std::vector<Point> polygon_; 
  };
}

#endif