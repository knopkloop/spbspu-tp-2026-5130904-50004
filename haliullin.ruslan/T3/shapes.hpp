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

  struct Polygon
  {
    std::vector< Point > points_;
  };
  std::istream& operator>>(std::istream& in, Polygon& dest);
  std::ostream& operator<<(std::ostream& out, const Polygon& src);

  double getArea(const Polygon& poly);
  bool hasRightAngle(const Polygon& poly);
  bool polygonsIntersect(const Polygon& a, const Polygon& b);
  bool pointInPolygon(const Point& point, const Polygon& poly);


  using iit_t = std::istream_iterator< Point >;
  using oit_t = std::ostream_iterator< Point> ;

  int orientation(const Point& a, const Point& b, const Point& c);
  bool onSegment(const Point& a, const Point&b, const Point& c);
  bool segmentsIntersect(const Point& p1, const Point& p2, const Point& q1, const Point& q2);
}

#endif
