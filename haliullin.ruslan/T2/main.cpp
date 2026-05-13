#include "IOguard.hpp"

#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

int main()
{
  using haliullin::DataStruct;
  std::vector< DataStruct > data;

  using iit_t = std::istream_iterator< DataStruct >;
  std::copy(iit_t{std::cin}, iit_t{}, std::back_inserter(data));

  std::sort(data.begin(), data.end());

  using oit_t = std::ostream_iterator< DataStruct >;
  std::copy(std::begin(data), std::end(data), oit_t{std::cout, "\n"});
}
