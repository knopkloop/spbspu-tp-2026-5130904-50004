#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace haliullin
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(double width, double height, const point_t& pos);
    ~Rectangle() override = default;

    double getArea() const override;
    rectangle_t getFrameRect() const override;

    void move(const point_t& pt) override;
    void move(double dx, double dy) override;

    void scale(double k) override;

  private:
    double width_;
    double height_;
    point_t pos_;
  };
}

#endif
