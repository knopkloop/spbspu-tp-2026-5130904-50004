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
  unsigned long long key1_copy = src.key1;
  std::pair< long long, unsigned long long > key2_copy = src.key2;

  out << "(:key1 " << UllLitIO{ key1_copy }
      << ":key2 " << RatLspIO{ key2_copy }
      << ":key3 \"" << src.key3 << "\":)";
  return out;
}

bool haliullin::operator<(const DataStruct& lhs, const DataStruct& rhs)
{
  bool c1 = key1_less(lhs.key1, rhs.key1);
  bool c1_eq = key1_equal(lhs.key1, rhs.key1);
  bool c2 = key2_less(lhs.key2, rhs.key2);
  bool c2_eq = key2_equal(lhs.key2, rhs.key2);
  bool c3 = key3_less(lhs.key3, rhs.key3);

  return c1 || (c1_eq && c2) || (c1_eq && c2_eq && c3);
}

bool haliullin::key1_less(unsigned long long a, unsigned long long b)
{
  return a < b;
}

bool haliullin::key1_equal(unsigned long long a, unsigned long long b)
{
  return a == b;
}

bool haliullin::key2_less(const std::pair<long long, unsigned long long>& a,
                const std::pair<long long, unsigned long long>& b)
{
  return (long double)a.first / a.second < (long double)b.first / b.second;
}

bool haliullin::key2_equal(const std::pair<long long, unsigned long long>& a,
                const std::pair<long long, unsigned long long>& b)
{
  return (long double)a.first / a.second == (long double)b.first / b.second;
}

bool haliullin::key3_less(const std::string& a, const std::string& b)
{
  return a < b;
}
