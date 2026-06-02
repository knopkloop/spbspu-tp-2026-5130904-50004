#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <memory>
#include <string>
#include "shape.hpp"

namespace haliullin
{
  point_t getRightBottomFrame(const rectangle_t& frame);

  void displayFigure(const std::weak_ptr< Shape >& figure, const std::string& name, size_t id);
  void displayAllFigures(const std::vector< std::weak_ptr< Shape > >& figures, const std::vector< std::string >& names);
  rectangle_t getTotalFrame(const std::vector< std::weak_ptr< Shape > >& figures);
  void displayTotalFrame(const rectangle_t& frame);

  void scaleFigures(std::vector< std::weak_ptr< Shape > >& figures, const point_t& scaleCenter, double coef);
}

#endif
