#include "DataStruct.hpp"
#include "subTypes.hpp"
#include <string>

std::istream& haliullin::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  DataStruct tmp;
  char dummy = 0;
  int mask = 0;

  in >> DelimiterIO{ '(', dummy };
  if (!in)
  {
    return in;
  }

  while (in)
  {
    if (in.peek() == ')')
    {
      in >> DelimiterIO{ ')', dummy };
      break;
    }

    if (!(in >> DelimiterIO{ ':', dummy }))
    {
      in.setstate(std::ios::failbit);
      break;
    }

    std::string label;
    if (!(in >> label))
    {
      in.setstate(std::ios::failbit);
      break;
    }

    if (!(in >> DelimiterIO{ ':', dummy }))
    {
      in.setstate(std::ios::failbit);
      break;
    }

    Field field = static_cast< Field >(0);
    if (label == "key1")
    {
      field = KEY1;
    }
    else if (label == "key2")
    {
      field = KEY2;
    }
    else if (label == "key3")
    {
      field = KEY3;
    }
    else
    {
      in.setstate(std::ios::failbit);
      break;
    }

    if (mask & field)
    {
      in.setstate(std::ios::failbit);
      break;
    }

    switch (field)
    {
      case KEY1:
      {
        in >> UllLitIO{tmp.key1};
        break;
      }
      case KEY2:
      {
        in >> RatLspIO{tmp.key2};
        break;
      }
      case KEY3:
      {
        in >> StringIO{tmp.key3};
        break;
      }
      default:
      {
        in.setstate(std::ios::failbit);
        break;
      }
    }
    if (!in)
    {
      break;
    }
    mask |= field;
  }

  if (in && mask == ALL)
  {
    dest = tmp;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

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
  return static_cast< long double >(a.first) / a.second < static_cast< long double >(b.first) / b.second;
}

bool haliullin::key2_equal(const std::pair<long long, unsigned long long>& a,
                           const std::pair<long long, unsigned long long>& b)
{
  return static_cast< long double >(a.first) / a.second == static_cast< long double >(b.first) / b.second;
}

bool haliullin::key3_less(const std::string& a, const std::string& b)
{
  return a < b;
}
