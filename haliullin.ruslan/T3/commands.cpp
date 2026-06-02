#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <limits>
#include <functional>
#include <stdexcept>
#include "commands.hpp"
#include "ioformat.hpp"

void haliullin::require(std::istream& in, bool condition)
{
  if (!condition)
  {
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    throw std::logic_error("<INVALID COMMAND>");
  }
}

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
  require(in, static_cast< bool >(in >> param));

  IOguard guard(out);
  out << std::fixed << std::setprecision(1);

  if (param == "EVEN")
  {
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double s, const Polygon& p)
      {
        return s + (p.points_.size() % 2 == 0 ? getArea(p) : 0.0);
      }
    );
    out << sum << "\n";
  }
  else if (param == "ODD")
  {
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double s, const Polygon& p)
      {
        return s + (p.points_.size() % 2 != 0 ? getArea(p) : 0.0);
      }
    );
    out << sum << "\n";
  }
  else if (param == "MEAN")
  {
    require(in, !polygons.empty());
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double s, const Polygon& p)
      {
        return s + getArea(p);
      }
    );
    out << sum / polygons.size() << "\n";
  }
  else
  {
    require(in, std::all_of(param.begin(), param.end(), ::isdigit));
    size_t n = std::stoull(param);
    require(in, n >= 3);
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [n](double s, const Polygon& p)
      {
        return s + (p.points_.size() == n ? getArea(p) : 0.0);
      }
    );
    out << sum << "\n";
  }
}

void haliullin::max(std::istream& in, std::ostream& out, const data_t& polygons)
{
  std::string param;
  require(in, static_cast< bool >(in >> param));
  require(in, !polygons.empty());

  if (param == "AREA")
  {
    auto it = std::max_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b)
      {
        return getArea(a) < getArea(b);
      }
    );
    IOguard guard(out);
    out << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
  }
  else if (param == "VERTEXES")
  {
    auto it = std::max_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b)
      {
        return a.points_.size() < b.points_.size();
      }
    );
    out << it->points_.size() << "\n";
  }
  else
  {
    require(in, false);
  }
}

void haliullin::min(std::istream& in, std::ostream& out, const data_t& polygons)
{
  std::string param;
  require(in, static_cast< bool >(in >> param));
  require(in, !polygons.empty());

  if (param == "AREA")
  {
    auto it = std::min_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b)
      {
        return getArea(a) < getArea(b);
      }
    );
    IOguard guard(out);
    out << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
  }
  else if (param == "VERTEXES")
  {
    auto it = std::min_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b)
      {
        return a.points_.size() < b.points_.size();
      }
    );
    out << it->points_.size() << "\n";
  }
  else
  {
    require(in, false);
  }
}

void haliullin::count(std::istream& in, std::ostream& out, const data_t& polygons)
{
  std::string param;
  require(in, static_cast< bool >(in >> param));

  if (param == "EVEN")
  {
    auto cnt = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& p)
      {
        return p.points_.size() % 2 == 0;
      }
    );
    out << cnt << "\n";
  }
  else if (param == "ODD")
  {
    auto cnt = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& p)
      {
        return p.points_.size() % 2 != 0;
      }
    );
    out << cnt << "\n";
  }
  else
  {
    require(in, std::all_of(param.begin(), param.end(), ::isdigit));
    size_t n = std::stoull(param);
    require(in, n >= 3);
    auto cnt = std::count_if(polygons.begin(), polygons.end(),
      [n](const Polygon& p)
      {
        return p.points_.size() == n;
      }
    );
    out << cnt << "\n";
  }
}

void haliullin::rightshapes(std::istream& in, std::ostream& out, const data_t& polygons)
{
  require(in, in.peek() == '\n' || in.peek() == EOF);
  auto cnt = std::count_if(polygons.begin(), polygons.end(), hasRightAngle);
  out << cnt << "\n";
}

void haliullin::intersections(std::istream& in, std::ostream& out, const data_t& polygons)
{
  Polygon target;
  require(in, static_cast< bool >(in >> target));
  require(in, target.points_.size() >= 3);
  require(in, in.peek() == '\n' || in.peek() == EOF);

  auto cnt = std::count_if(polygons.begin(), polygons.end(),
    [&target](const Polygon& p)
    {
      return polygonsIntersect(target, p);
    }
  );
  out << cnt << "\n";
}
