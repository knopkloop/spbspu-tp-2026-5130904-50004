#include <stdexcept>
#include "rectangle.hpp"

haliullin::Rectangle::Rectangle(double width, double height, const point_t& pos):
  width_(width),
  height_(height),
  pos_(pos)
{
  if (width_ <= 0.0 || height_ <= 0.0)
  {
    throw std::invalid_argument("Sizes must be positive");
  }
}

double haliullin::Rectangle::getArea() const
{
  return width_ * height_;
}

haliullin::rectangle_t haliullin::Rectangle::getFrameRect() const
{
  return rectangle_t(width_, height_, pos_);
}

void haliullin::Rectangle::move(const point_t& pt)
{
  pos_ = pt;
}

void haliullin::Rectangle::move(double dx, double dy)
{
  pos_.x_ += dx;
  pos_.y_ += dy;
}

void haliullin::Rectangle::scale(double k)
{
  if (k <= 0.0)
  {
    throw std::invalid_argument("Scale coefficient must be positive");
  }
  width_ *= k;
  height_ *= k;
}
