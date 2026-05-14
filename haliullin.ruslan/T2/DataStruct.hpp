#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <utility>
#include <string>

namespace haliullin
{
  struct DataStruct
  {
    unsigned long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& src);
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);

  bool key1_less(unsigned long long a, unsigned long long b);
  bool key1_equal(unsigned long long a, unsigned long long b);
  bool key2_less(const std::pair<long long, unsigned long long>& a,
                 const std::pair<long long, unsigned long long>& b);
  bool key2_equal(const std::pair<long long, unsigned long long>& a,
                  const std::pair<long long, unsigned long long>& b);
  bool key3_less(const std::string& a, const std::string& b);

}

#endif
