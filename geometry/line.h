#ifndef LINE_H
#define LINE_H
#include "point.h"

namespace geometry {
  class Point;
  class Vector;
  class Segment;
  class Line : public IShape {
   public:
    Line();
    Line(const Point& a, const Point& b);
    Line& Move(const Vector& vector) override;
    bool ContainsPoint(const Point& point) const override;
    bool CrossesSegment(const Segment& segment) const override;
    std::shared_ptr<IShape> Clone() const override;
    std::string ToString() const override;
    int64_t Value(const Point& p) const;
    long double DistToPoint(const Point&) const;
   private:
    Point a_;
    Point b_;
  };
}

#endif