#include "../polygon.h"
#include "../segment.h"
#include "../vector.h"
#include "../ray.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>

namespace geometry {
  Polygon::Polygon() = default;
  Polygon::Polygon(const Polygon&) = default;
  Polygon::Polygon(const std::vector<Point>& vector) : size_(vector.size()), polygon_(vector) {
  }

  Polygon& Polygon::Move(const Vector& vector) {
    for (int64_t i = 0; i < size_; ++i) {
      polygon_[i].Move(vector);
    }
    return *this;
  }

  bool Polygon::ContainsPoint(const Point& point) const {
    int64_t intersection_number = 0;
    Point other(point.x_ + 1, point.y_);
    Ray ray(point, other);
    for (int64_t i = 0; i < size_; ++i) {
      Segment side(polygon_[i], polygon_[(i + 1) % size_]);
      if (side.ContainsPoint(point)) {
        return true;
      }
      if (ray.ContainsPoint(polygon_[i]) && ray.ContainsPoint(polygon_[(i + 1) % size_])) {
      } else if (ray.ContainsPoint(polygon_[i])) {
        intersection_number += polygon_[(i + 1) % size_].y_ > polygon_[i].y_;
      } else if (ray.ContainsPoint(polygon_[(i + 1) % size_])) {
        intersection_number += polygon_[i].y_ > polygon_[(i + 1) % size_].y_;
      } else {
        int n = ray.CrossesSegment(side);
        intersection_number += n;
      }
    }
    return intersection_number % 2 == 1;
  }

  bool Polygon::CrossesSegment(const Segment& segment) const {
    for (int64_t i = 0; i < size_; ++i) {
      Segment side(polygon_[i], polygon_[(i + 1) % size_]);
      if (side.CrossesSegment(segment)) {
        return true;
      }
    }
    return false;
  }

  std::shared_ptr<IShape> Polygon::Clone() const {
    std::shared_ptr<Polygon> ptr_to_copy = std::make_shared<Polygon>(*this);
    return ptr_to_copy;
  }

  std::string Polygon::ToString() const {
    std::string str = "Polygon(" + polygon_[0].ToString();
    for (int i = 1; i < size_; ++i) {
      str += ", " + polygon_[i].ToString();
    }
    str += ')';
    return str;
  }
}