#ifndef CIRCLE_H
#define CIRCLE_H
#include "point.h"

namespace geometry {
  class Circle : public IShape {
   public:
    Circle();

    Circle(const Point&, int radius);

    Circle& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& segment) const override;

    std::shared_ptr<IShape> Clone() const override;

    std::string ToString() const override;

   private:
    Point center_;
    int radius_; 
  };
}

#endif