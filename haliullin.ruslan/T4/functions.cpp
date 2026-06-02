#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include "functions.hpp"

haliullin::point_t haliullin::getRightBottomFrame(const rectangle_t& frame)
{
  double halfWidth = frame.width_ / 2.0;
  double halfHeight = frame.height_ / 2.0;
  return point_t(frame.pos_.x_ + halfWidth, frame.pos_.y_ + halfHeight);
}

void haliullin::displayFigure(const std::weak_ptr< Shape >& figure, const std::string& name, size_t id)
{
  auto shape = figure.lock();
  if (!shape)
  {
    throw std::runtime_error("Expired weak pointer");
  }

  rectangle_t frame = shape->getFrameRect();

  std::cout << id << ". " << name << "\n";
  std::cout << "area = " << shape->getArea() << "\n";
  std::cout << "frame: (" << frame.pos_.x_ << ";" << frame.pos_.y_ << "), width = "
  << frame.width_ << ", height = " << frame.height_ << "\n";
}

void haliullin::displayAllFigures(const std::vector< std::weak_ptr< Shape > >& figures, const std::vector< std::string >& names)
{
  double total = 0.0;
  std::cout << std::fixed << std::setprecision(2);

  for (size_t i = 0; i < figures.size(); ++i)
  {
    auto shape = figures[i].lock();
    if (shape)
    {
      displayFigure(figures[i], names[i], i + 1);
      total += shape->getArea();
    }
  }

  std::cout << "\n";
  std::cout << "Total area = " << total << "\n";
}

haliullin::rectangle_t haliullin::getTotalFrame(const std::vector< std::weak_ptr< Shape > >& figures)
{
  if (figures.empty())
  {
    return rectangle_t(0.0, 0.0, point_t(0.0, 0.0));
  }

  double minX = std::numeric_limits< double >::max();
  double minY = std::numeric_limits< double >::max();
  double maxX = std::numeric_limits< double >::lowest();
  double maxY = std::numeric_limits< double >::lowest();

  for (const auto& wptr: figures)
  {
    auto shape = wptr.lock();
    if (!shape)
    {
      continue;
    }

    rectangle_t frame = shape->getFrameRect();

    double halfWidth = frame.width_ / 2.0;
    double halfHeight = frame.height_ / 2.0;

    double left = frame.pos_.x_ - halfWidth;
    double right = frame.pos_.x_ + halfWidth;

    double bottom = frame.pos_.y_ - halfHeight;
    double top = frame.pos_.y_ + halfHeight;

    if (left < minX)
    {
      minX = left;
    }
    if (right > maxX)
    {
      maxX = right;
    }
    if (bottom < minY)
    {
      minY = bottom;
    }
    if (top > maxY)
    {
      maxY = top;
    }
  }

  double width = maxX - minX;
  double height = maxY - minY;
  point_t center = point_t((minX + maxX) / 2.0, (minY + maxY) / 2.0);

  return rectangle_t(width, height, center);
}

void haliullin::displayTotalFrame(const rectangle_t& frame)
{
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Total frame: (" << frame.pos_.x_ << ";" << frame.pos_.y_ << ") ";
  std::cout << "width = " << frame.width_ << ", height = " << frame.height_ << "\n";
}

void haliullin::scaleFigures(std::vector< std::weak_ptr< Shape > >& figures, const point_t& scaleCenter, double coef)
{
  for (const auto& wptr: figures)
  {
    auto shape = wptr.lock();
    if (!shape)
    {
      continue;
    }

    rectangle_t frameBefore = shape->getFrameRect();
    point_t anchor = getRightBottomFrame(frameBefore);

    shape->move(scaleCenter.x_ - anchor.x_, scaleCenter.y_ - anchor.y_);
    shape->scale(coef);

    rectangle_t frameAfter = shape->getFrameRect();
    point_t anchorAfter = getRightBottomFrame(frameAfter);

    shape->move(anchor.x_ - anchorAfter.x_, anchor.y_ - anchorAfter.y_);
  }
}

