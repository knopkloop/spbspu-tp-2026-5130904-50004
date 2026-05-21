#include "shapes.hpp"
#include "ioformat.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>

std::istream& haliullin::operator>>(std::istream& in, Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{'('} >> dest.x_ >> DelimiterIO{';'} >> dest.y_ >> DelimiterIO{')'};
  if (!in)
  {
    in.setstate(std::ios_base::failbit);
  }
  return in;
}

std::ostream& haliullin::operator<<(std::ostream& out, const Point& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << src.x_ << ';' << src.y_ << ')';
  return out;
}

std::istream& haliullin::operator>>(std::istream& in, Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t count = 0;
  in >> count;
  if (!in)
  {
    in.setstate(std::ios_base::failbit);
  }
  std::vector< Point > temp;
  temp.reserve(count);
  std::generate_n(std::back_inserter(temp), count,
    [&in]()
    {
      Point p;
      in >> p;
      return p;
    }
  );
  if (in)
  {
    dest.points_ = std::move(temp);
  }
  else
  {
    in.setstate(std::ios_base::failbit);
  }
  return in;
}
