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

std::ostream& haliullin::operator<<(std::ostream& out, const Polygon& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  IOguard guard(out);
  out << src.points_.size();
  if (!src.points_.empty())
  {
    out << ' ' << src.points_.front();
    std::copy(std::next(src.points_.begin()), src.points_.end(), oit_t(out, " "));
  }
  return out;
}

double haliullin::getArea(const Polygon& poly)
{
  const auto& pts = poly.points_;
  if (pts.size() < 3)
  {
    return 0.0;
  }

  std::vector<double> triAreas(pts.size() - 2);
  const Point& p0 = pts[0];

  std::generate(triAreas.begin(), triAreas.end(),
    [&pts, &p0, idx = 1]() mutable
    {
      const Point& p1 = pts[idx];
      const Point& p2 = pts[idx + 1];
      ++idx;
      double area = (p1.x_ - p0.x_) * (p2.y_ - p0.y_) - (p2.x_ - p0.x_) * (p1.y_ - p0.y_);
      return std::abs(area) / 2.0;
    }
  );

  return std::accumulate(triAreas.begin(), triAreas.end(), 0.0);
}

bool haliullin::hasRightAngle(const Polygon& poly)
{
  const auto& pts = poly.points_;
  size_t n = pts.size();
  if (n < 3)
  {
    return false;
  }

  std::vector<size_t> indices(n);
  std::generate(indices.begin(), indices.end(), [i = 0]() mutable { return i++; });

  return std::any_of(indices.begin(), indices.end(),
    [&pts, n](size_t i)
    {
      size_t prev = (i + n - 1) % n;
      size_t next = (i + 1) % n;
      const Point& a = pts[prev];
      const Point& b = pts[i];
      const Point& c = pts[next];
      int dx1 = a.x_ - b.x_;
      int dy1 = a.y_ - b.y_;
      int dx2 = c.x_ - b.x_;
      int dy2 = c.y_ - b.y_;
      return (dx1 * dx2 + dy1 * dy2) == 0;
    });
}

bool haliullin::polygonsIntersect(const Polygon& a, const Polygon& b)
{
  const auto& ptsA = a.points_;
  const auto& ptsB = b.points_;
  size_t nA = ptsA.size();
  size_t nB = ptsB.size();
  if (nA < 3 || nB < 3)
  {
    return false;
  }

  std::vector<size_t> indicesA(nA);
  std::generate(indicesA.begin(), indicesA.end(), [i = 0]() mutable { return i++; });

  return std::any_of(indicesA.begin(), indicesA.end(),
    [&](size_t i)
    {
      const Point& p1 = ptsA[i];
      const Point& p2 = ptsA[(i + 1) % nA];

      std::vector<size_t> indicesB(nB);
      std::generate(indicesB.begin(), indicesB.end(), [j = 0]() mutable { return j++; });

      return std::any_of(indicesB.begin(), indicesB.end(),
        [&](size_t j)
        {
          const Point& q1 = ptsB[j];
          const Point& q2 = ptsB[(j + 1) % nB];
          return segmentsIntersect(p1, p2, q1, q2);
        });
    });
}
