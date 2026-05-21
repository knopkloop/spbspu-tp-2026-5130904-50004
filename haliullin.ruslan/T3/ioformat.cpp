#include "ioformat.hpp"
#include <iostream>

std::istream& haliullin::operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.expected_))
  {
    in.setstate(std::ios_base::failbit);
  }
  return in;
}

haliullin::IOguard::IOguard(std::basic_ios<char>& s):
  s_(s),
  precision_(s.precision()),
  width_(s.width()),
  fmt_(s.flags()),
  fill_(s.fill())
{}

haliullin::IOguard::~IOguard()
{
  s_.precision(precision_);
  s_.width(width_);
  s_.flags(fmt_);
  s_.fill(fill_);
}