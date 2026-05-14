#include "DataStruct.hpp"
#include "subTypes.hpp"

std::istream& haliullin::operator>>(std::istream& in, DataStruct& dest);

std::ostream& haliullin::operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  IOguard guard(out);

  out << "(:key1 " << UllLitIO{const_cast< unsigned long long& >(src.key1)}
      << ":key2 " << RatLspIO{const_cast< std::pair< long long, unsigned long long >& >(src.key2)}
      << ":key3 \"" << src.key3 << "\":)";
  return out;
}

bool haliullin::operator<(const DataStruct& lhs, const DataStruct& rhs)
{

}
