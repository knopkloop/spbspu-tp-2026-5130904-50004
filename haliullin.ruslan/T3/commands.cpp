#include "commands.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iostream>
#include <limits>
#include <iterator>
#include <functional>
#include <stdexcept>

std::vector<haliullin::Polygon> haliullin::readPolygonsFromFile(const std::string& filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    throw std::runtime_error("Cannot open file");
  }

  std::vector<Polygon> polygons;
  std::function< void(std::istream&) > readRecursive = [&](std::istream& is)
  {
    if (is.eof())
    {
      return;
    }
    Polygon p;
    if (is >> p)
    {
      polygons.push_back(p);
      readRecursive(is);
      return;
    }
    if (is.eof())
    {
      return;
    }
    is.clear();
    std::string trash;
    std::getline(is, trash);
    readRecursive(is);
  };

  readRecursive(file);
  return polygons;
}
