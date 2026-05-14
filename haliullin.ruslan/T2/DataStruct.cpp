#include "DataStruct.hpp"

std::istream& haliullin::operator>>(std::istream& in, DataStruct& dest);
std::ostream& haliullin::operator<<(std::ostream& out, const DataStruct& dest);
bool haliullin::operator<(const DataStruct& lhs, const DataStruct& rhs);
