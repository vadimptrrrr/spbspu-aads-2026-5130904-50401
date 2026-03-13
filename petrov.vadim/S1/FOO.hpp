#ifndef FOO_HPP
#define FOO_HPP
#include "STRUCTS.hpp"
#include <string>
namespace petrov
{
  void mkData(std::istream& input, List< std::pair< std::string, List< size_t > > >& data);
  void printAllList(List< std::pair< std::string, List< size_t > > >& data);
  bool canShow(const List< size_t >& nums, size_t MAX);
  size_t maxLen(const List< std::pair< std::string, List< size_t > > >& data);
}
#endif