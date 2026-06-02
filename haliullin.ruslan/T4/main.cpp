#include <iostream>
#include <string>
#include <vector>
#include "shape.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "diamond.hpp"
#include "functions.hpp"

int main()
{
  using namespace haliullin;
  std::vector< std::shared_ptr< Shape > > shapes;
  std::vector< std::string > names;

  try
  {
    shapes.push_back(std::make_shared< Rectangle >(7.0, 2.8, point_t(1.0, 2.0)));
    names.push_back("Rectangle");

    shapes.push_back(std::make_shared< Triangle >(point_t(0.0, 0.0), point_t(4.0, 0.0), point_t(2.0, 3.0)));
    names.push_back("Triangle");

    shapes.push_back(std::make_shared< Diamond >(6.0, 4.0, point_t(5.0, 5.0)));
    names.push_back("Diamond");
  }
  catch (const std::exception& e)
  {
    std::cerr << "Failed to create figures: " << e.what() << "\n";
    return 1;
  }

  std::vector< std::weak_ptr< Shape > > wshapes;
  for (const auto& shape: shapes)
  {
    wshapes.push_back(shape);
  }

  std::cout << "BEFORE:\n";
  try
  {
    displayAllFigures(wshapes, names);
    displayTotalFrame(getTotalFrame(wshapes));
  }
  catch (const std::exception& e)
  {
    std::cerr << "Failed to display figures: " << e.what() << "\n";
    return 1;
  }

  double x, y, k;
  std::cout << "Enter scale point (x y): ";
  std::cin >> x >> y;
  if (!std::cin)
  {
    if (std::cin.eof())
    {
      return 0;
    }
    else
    {
      std::cerr << "Invalid point coordinates\n";
      return 1;
    }
  }
  std::cout << "Enter scale coefficient: ";
  std::cin >> k;
  if (!std::cin)
  {
    std::cerr << "Invalid coefficient\n";
    return 1;
  }
  if (k <= 0.0)
  {
    std::cerr << "Scale coefficient must be positive\n";
    return 1;
  }
  try
  {
    scaleFigures(wshapes, point_t(x, y), k);
  }
  catch (const std::exception& e)
  {
    std::cerr << "Failed to scale figures: " << e.what() << "\n";
    return 1;
  }

  std::cout << "AFTER:\n";
  try
  {
    displayAllFigures(wshapes, names);
    displayTotalFrame(getTotalFrame(wshapes));
  }
  catch (const std::exception& e)
  {
    std::cerr << "Failed to display figures: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
