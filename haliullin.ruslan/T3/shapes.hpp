#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <iosfwd>
#include <vector>
#include <iterator>

namespace haliullin
{
  struct Point
  {
    int x_, y_;
  };

  std::istream& operator>>(std::istream& in, Point& dest);
  std::ostream& operator<<(std::ostream& out, const Point& src);

}

#endif
