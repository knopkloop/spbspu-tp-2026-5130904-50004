#ifndef SUBTYPES_CPP
#define SUPTYPES_CPP

#include <ios>
#include <sstream>
#include <string>

namespace haliullin
{

  struct DelimiterIO
  {
    char expected_;
  };
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);

  struct UllLitIO
  {
    unsigned long long &ref_;
  };
  std::istream& operator>>(std::istream& in, UllLitIO&& dest);
  std::ostream& operator<<(std::ostream& out, const UllLitIO& dest);

  struct RatLspIO
  {
    std::pair< long long, unsigned long long >& ref_;
  };
  std::istream& operator>>(std::istream& in, RatLspIO&& dest);
  std::ostream& operator<<(std::ostream& out, const RatLspIO& dest);

  struct StringIO
  {
    std::string &ref_;
  };
  std::istream& operator>>(std::istream& in, StringIO&& dest);

  struct LabelIO
  {
    std::string expected_;
  };
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
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

std::istream& haliullin::operator>>(std::istream& in, RatLspIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{ '(' } >> DelimiterIO{ 'N' } >> dest.ref_.first  >> DelimiterIO{ ':' }
  >> DelimiterIO{ 'D' } >> dest.ref_.second >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
}

std::ostream& haliullin::operator>>(std::ostream& out, const RatLspIO& dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << "(:N " << dest.ref_.first << ":D " << dest.ref_.second << ":)";
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

std::istream& haliullin::operator>>(std::istream& in, LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string data = "";
  in >> data;
  if (in && (data != dest.expected_))
  {
    in.setstate(std::ios_base::failbit);
  }
  return in;
}

#endif
