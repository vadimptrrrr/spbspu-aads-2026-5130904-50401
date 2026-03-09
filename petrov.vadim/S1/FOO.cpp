#include "FOO.hpp"
#include <istream>

namespace petrov
{
  void mkData(std::istream& input, List< std::pair< std::string, List< size_t > > >& data)
  {
    std::string name;
    while(input >> name)
    {
      List< size_t > nums;
      size_t num;
      LIter< size_t > inPos = nums.getLast();
      while (input >> num)
      {
        inPos = nums.insert(inPos, num);
      }
      data.insert(data.getLast(), {name, nums});

      if(input.eof())
      {
        break;
      }
      else
      {
        input.clear();
      }
    }
  }
}
