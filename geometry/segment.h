#ifndef SEGMENT_H
#define SEGMENT_H
#include "point.h"

namespace geometry {
  class Line;
  class Segment : public IShape {
   public:
    Segment();
    Segment(const Point&, const Point&);
    Segment(const Segment&);
    Segment& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    bool CrossesLine(const Line&) const;
    int64_t SquaredModule() const;
    std::shared_ptr<IShape> Clone() const override;
    std::string ToString() const override;
    long double DistToPoint(const Point&) const;

   public:
    Point begin_; 
    Point end_;
  };
}

#endif