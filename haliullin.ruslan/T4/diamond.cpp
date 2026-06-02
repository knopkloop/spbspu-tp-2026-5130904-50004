#include <cmath>
#include <stdexcept>
#include "diamond.hpp"

haliullin::Diamond::Diamond(double d1, double d2, const point_t& pos):
  d1_(d1),
  d2_(d2),
  pos_(pos)
{
  if (d1_ <= 0.0 || d2_ <= 0.0)
  {
    throw std::invalid_argument("Diagonals must be positive");
  }
}

double haliullin::Diamond::getArea() const
{
  return (d1_ * d2_) / 2.0;
}

haliullin::rectangle_t haliullin::Diamond::getFrameRect() const
{
  return rectangle_t(d1_, d2_, pos_);
}

void haliullin::Diamond::move(const point_t& pt)
{
  pos_ = pt;
}

void haliullin::Diamond::move(double dx, double dy)
{
  pos_.x_ += dx;
  pos_.y_ += dy;
}

void haliullin::Diamond::scale(double k)
{
  if (k <= 0.0)
  {
    throw std::invalid_argument("Scale coefficient must be positive");
  }
  d1_ *= k;
  d2_ *= k;
}
