#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <sstream>
#include <vector>
#include <functional>
#include "shapes.hpp"

namespace haliullin
{
  using data_t = std::vector< Polygon >;
  using cf_t = std::function< void(std::istream&, std::ostream&) >;

  data_t readPolygonsFromFile(const std::string& filename);

  void area(std::istream& in, std::ostream& out, const data_t& polygons);
  void max(std::istream& in, std::ostream& out, const data_t& polygons);
  void min(std::istream& in, std::ostream& out, const data_t& polygons);
  void count(std::istream& in, std::ostream& out, const data_t& polygons);
  void intersections(std::istream& in, std::ostream& out, const data_t& polygons);
  void rightshapes(std::istream& in, std::ostream& out, const data_t& polygons);
}

#endif
