#include <algorithm>
#include <cmath>
#include <stdexcept>
#include "triangle.hpp"

haliullin::Triangle::Triangle(const point_t& p1, const point_t& p2, const point_t& p3):
  p1_(p1),
  p2_(p2),
  p3_(p3),
  pos_(point_t((p1.x_ + p2.x_ + p3.x_) / 3.0, (p1.y_ + p2.y_ + p3.y_) / 3.0))
{

  double a = p1_.x_ * (p2_.y_ - p3_.y_);
  double b = p2_.x_ * (p3_.y_ - p1_.y_);
  double c = p3_.x_ * (p1_.y_ - p2_.y_);

  double area = std::abs(a + b + c) / 2.0;

  if (area == 0.0)
  {
    throw std::invalid_argument("Triangle vertices are collinear");
  }
}

double haliullin::Triangle::getArea() const
{
  double a = p1_.x_ * (p2_.y_ - p3_.y_);
  double b = p2_.x_ * (p3_.y_ - p1_.y_);
  double c = p3_.x_ * (p1_.y_ - p2_.y_);

  return (a + b + c) / 2.0;
}

haliullin::rectangle_t haliullin::Triangle::getFrameRect() const
{
  double minX = std::min({p1_.x_, p2_.x_, p3_.x_});
  double maxX = std::max({p1_.x_, p2_.x_, p3_.x_});
  double minY = std::min({p1_.y_, p2_.y_, p3_.y_});
  double maxY = std::max({p1_.y_, p2_.y_, p3_.y_});

  double width = maxX - minX;
  double height = maxY - minY;
  point_t center = {minX + width / 2.0, minY + height / 2.0};

  return rectangle_t(width, height, center);
}

void haliullin::Triangle::move(const point_t& pt)
{
  double dx = pt.x_ - pos_.x_;
  double dy = pt.y_ - pos_.y_;
  move(dx, dy);
}

void haliullin::Triangle::move(double dx, double dy)
{
  p1_.x_ += dx;
  p1_.y_ += dy;

  p2_.x_ += dx;
  p2_.y_ += dy;

  p3_.x_ += dx;
  p3_.y_ += dy;

  pos_.x_ += dx;
  pos_.y_ += dy;
}

void haliullin::Triangle::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("Scale coefficient must be positive");
  }

  p1_.x_ = pos_.x_ + (p1_.x_ - pos_.x_) * k;
  p1_.y_ = pos_.y_ + (p1_.y_ - pos_.y_) * k;

  p2_.x_ = pos_.x_ + (p2_.x_ - pos_.x_) * k;
  p2_.y_ = pos_.y_ + (p2_.y_ - pos_.y_) * k;

  p3_.x_ = pos_.x_ + (p3_.x_ - pos_.x_) * k;
  p3_.y_ = pos_.y_ + (p3_.y_ - pos_.y_) * k;
}
