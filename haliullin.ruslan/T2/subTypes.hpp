#ifndef SUBTYPES_HPP
#define SUBTYPES_HPP

#include <ios>
#include <sstream>
#include <string>
#include <cctype>
#include <utility>

namespace haliullin
{

  struct DelimiterIO
  {
    char expected_;
    char &last_;
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
  in >> dest.last_;
  if (in && (std::tolower(dest.last_) != std::tolower(dest.expected_)))
  {
    in.setstate(std::ios_base::failbit);
  }
  return in;
}

std::istream& haliullin::operator>>(std::istream& in, UllLitIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  unsigned long long value = 0;
  char c1 = 0, c2 = 0, c3 = 0;
  in >> value >> DelimiterIO{'U', c1} >> DelimiterIO{'L', c2} >> DelimiterIO{'L', c3};
  std::string lit = std::string("") + c1 + c2 + c3;
  if (in && (lit != "ull" && lit != "ULL"))
  {
    in.setstate(std::ios_base::failbit);
  }
  if (in)
  {
    dest.ref_ = value;
  }

  return in;
}

std::ostream& haliullin::operator<<(std::ostream& out, const UllLitIO& dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << dest.ref_ << "ull";
  return out;
}

std::istream& haliullin::operator>>(std::istream& in, RatLspIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) return in;

  long long num = 0;
  unsigned long long den = 0;
  char last = 0;

  in >> DelimiterIO{ '(', last }
      >> DelimiterIO{ ':', last } >> LabelIO{ "N" } >> num
      >> DelimiterIO{ ':', last } >> LabelIO{ "D" } >> den
      >> DelimiterIO{ ':', last } >> DelimiterIO{ ')', last };

  if (in && den != 0)
  {
    dest.ref_ = std::make_pair(num, den);
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& haliullin::operator<<(std::ostream& out, const RatLspIO& dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << "(:N " << dest.ref_.first << ":D " << dest.ref_.second << ":)";
  return out;
}

std::istream& haliullin::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char last = 0;
  return std::getline(in >> DelimiterIO{ '"', last }, dest.ref_ , '"');
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
