#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

namespace haliullin
{
  class Triangle: public Shape
  {
  public:
    Triangle(const point_t& p1, const point_t& p2, const point_t& p3);
    ~Triangle() override = default;

    double getArea() const override;
    rectangle_t getFrameRect() const override;

    void move(const point_t& pt) override;
    void move(double dx, double dy) override;

    void scale(double k) override;

  private:
    point_t p1_;
    point_t p2_;
    point_t p3_;
    point_t pos_;
  };
}

#endif
