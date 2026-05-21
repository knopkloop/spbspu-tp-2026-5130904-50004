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

haliullin::data_t haliullin::readPolygonsFromFile(const std::string& filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    throw std::runtime_error("Cannot open file");
  }

  std::vector< Polygon > polygons;
  std::function< void() > readRecursive = [&]()
  {
    Polygon p;
    if (file >> p)
    {
      polygons.push_back(p);
      readRecursive();
      return;
    }
    if (file.eof())
    {
      return;
    }
    file.clear();
    file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    readRecursive();
  };

  readRecursive();
  return polygons;
}

void haliullin::area(std::istream& in, std::ostream& out, const data_t& polygons)
{
  std::string param;
  if (!(in >> param))
  {
    out << "<INVALID COMMAND>\n";
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    return;
  }

  out << std::fixed << std::setprecision(1);

  if (param == "EVEN")
  {
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double s, const Polygon& p)
      {
        return s + (p.points_.size() % 2 == 0 ? getArea(p) : 0.0);
      });
    out << sum << "\n";
  }
  else if (param == "ODD")
  {
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double s, const Polygon& p)
      {
        return s + (p.points_.size() % 2 != 0 ? getArea(p) : 0.0);
      });
    out << sum << "\n";
  }
  else if (param == "MEAN")
  {
    if (polygons.empty())
    {
      out << "<INVALID COMMAND>\n";
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      return;
    }
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double s, const Polygon& p) { return s + getArea(p); });
    out << sum / polygons.size() << "\n";
  }
  else
  {
    if (!std::all_of(param.begin(), param.end(), ::isdigit))
    {
      out << "<INVALID COMMAND>\n";
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      return;
    }
    size_t n = std::stoull(param);
    if (n < 3)
    {
      out << "<INVALID COMMAND>\n";
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      return;
    }
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [n](double s, const Polygon& p)
      {
        return s + (p.points_.size() == n ? getArea(p) : 0.0);
      });
    out << sum << "\n";
  }
}

void haliullin::max(std::istream& in, std::ostream& out, const data_t& polygons)
{
  std::string param;
  if (!(in >> param))
  {
    out << "<INVALID COMMAND>\n";
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    return;
  }

  if (polygons.empty())
  {
    out << "<INVALID COMMAND>\n";
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    return;
  }

  if (param == "AREA")
  {
    auto it = std::max_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) { return getArea(a) < getArea(b); });
    out << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
  }
  else if (param == "VERTEXES")
  {
    auto it = std::max_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) { return a.points_.size() < b.points_.size(); });
    out << it->points_.size() << "\n";
  }
  else
  {
    out << "<INVALID COMMAND>\n";
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}

void haliullin::min(std::istream& in, std::ostream& out, const data_t& polygons)
{
  std::string param;
  if (!(in >> param))
  {
    out << "<INVALID COMMAND>\n";
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    return;
  }

  if (polygons.empty())
  {
    out << "<INVALID COMMAND>\n";
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    return;
  }

  if (param == "AREA")
  {
    auto it = std::min_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) { return getArea(a) < getArea(b); });
    out << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
  }
  else if (param == "VERTEXES")
  {
    auto it = std::min_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) { return a.points_.size() < b.points_.size(); });
    out << it->points_.size() << "\n";
  }
  else
  {
    out << "<INVALID COMMAND>\n";
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}

void haliullin::count(std::istream& in, std::ostream& out, const data_t& polygons)
{
  std::string param;
  if (!(in >> param))
  {
    out << "<INVALID COMMAND>\n";
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    return;
  }

  if (param == "EVEN")
  {
    auto cnt = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& p) { return p.points_.size() % 2 == 0; });
    out << cnt << "\n";
  }
  else if (param == "ODD")
  {
    auto cnt = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& p) { return p.points_.size() % 2 != 0; });
    out << cnt << "\n";
  }
  else
  {
    if (!std::all_of(param.begin(), param.end(), ::isdigit))
    {
      out << "<INVALID COMMAND>\n";
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      return;
    }
    size_t n = std::stoull(param);
    if (n < 3)
    {
      out << "<INVALID COMMAND>\n";
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      return;
    }
    auto cnt = std::count_if(polygons.begin(), polygons.end(),
      [n](const Polygon& p) { return p.points_.size() == n; });
    out << cnt << "\n";
  }
}

void haliullin::rightshapes(std::istream& in, std::ostream& out, const data_t& polygons)
{
  std::string extra;
  if (in >> extra)
  {
    out << "<INVALID COMMAND>\n";
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    return;
  }
  auto cnt = std::count_if(polygons.begin(), polygons.end(), hasRightAngle);
  out << cnt << "\n";
}

void haliullin::intersections(std::istream& in, std::ostream& out, const data_t& polygons)
{
  Polygon target;
  if (!(in >> target) || target.points_.size() < 3)
  {
    out << "<INVALID COMMAND>\n";
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    return;
  }
  std::string extra;
  if (in >> extra)
  {
    out << "<INVALID COMMAND>\n";
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return;
  }
  auto cnt = std::count_if(polygons.begin(), polygons.end(),
    [&target](const Polygon& p) { return polygonsIntersect(target, p); });
  out << cnt << "\n";
}
