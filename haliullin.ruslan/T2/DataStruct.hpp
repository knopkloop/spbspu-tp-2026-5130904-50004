#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <utility>
#include <string>

namespace haliullin
{
  enum Field
  {
    KEY1 = 1,
    KEY2 = 2,
    KEY3 = 4,
    ALL  = KEY1 | KEY2 | KEY3
  };

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

  struct KeyValueInp
  {
    std::string key;
    int& mask;
    DataStruct& ds;
  };
  std::istream& operator>>(std::istream& in, KeyValueInp inp);
  std::istream& getValueByKey(std::istream& in, const std::string& key,
                              int& mask, DataStruct& ds);
}

#endif
