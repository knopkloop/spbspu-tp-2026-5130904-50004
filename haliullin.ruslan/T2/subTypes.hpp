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

  class IOguard
  {
  public:
    explicit IOguard(std::basic_ios< char >& s);
    ~IOguard();
  private:
    std::basic_ios< char >& s_;
    std::streamsize width_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
    char fill_;
  };
}

#endif
