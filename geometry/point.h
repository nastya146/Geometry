#ifndef POINT_H
#define POINT_H
#include "shape.h"
#include "vector.h"


namespace geometry {
  class Segment;
  class Point : public IShape {
   public:
    Point();

    Point(const Point&);

    Point(int64_t x, int64_t y);

    Point& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& segment) const override;

    std::shared_ptr<IShape> Clone() const override;

    bool operator==(const Point& other) const;

    std::string ToString() const override;

    Vector operator-(const Point& other) const;

   public:
    int64_t x_;
    int64_t y_;
  };
}

#endif