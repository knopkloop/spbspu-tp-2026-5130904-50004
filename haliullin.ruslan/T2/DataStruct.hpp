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
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);
}

#endif
