#ifndef BASIC_HPP
#define BASIC_HPP

namespace haliullin
{
  class point_t
  {
  public:
    double x_ = 0.0;
    double y_ = 0.0;

    point_t(double x, double y):
      x_(x),
      y_(y)
    {}
  };

  class rectangle_t
  {
  public:
    double width_ = 0.0;
    double height_ = 0.0;
    point_t pos_ = {0.0, 0.0};

    rectangle_t(double width, double height, const point_t& pos):
      width_(width),
      height_(height),
      pos_(pos)
    {}
  };
}

#endif
