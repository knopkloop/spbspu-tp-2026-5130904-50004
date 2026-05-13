#ifndef SUBTYPES_CPP
#define SUPTYPES_CPP

#include <ios>
#include <sstream>

namespace haliullin
{
  struct DelimiterIO
  {
    char expected_;
  };
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);

  struct StringIO
  {
    std::string &ref_;
  };
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

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

std::istream& haliullin::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref_ , '"');
}

#endif
