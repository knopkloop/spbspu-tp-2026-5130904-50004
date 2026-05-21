#ifndef IOFORMAT_HPP
#define IOFORMAT_HPP

#include <ios>

namespace haliullin
{
  struct DelimiterIO
  {
    char expected_;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);

  class IOguard
  {
  public:
    explicit IOguard(std::basic_ios<char>& s);
    ~IOguard();
  private:
    std::basic_ios<char>& s_;
    std::streamsize precision_;
    std::streamsize width_;
    std::basic_ios<char>::fmtflags fmt_;
    char fill_;
  };
}

#endif
