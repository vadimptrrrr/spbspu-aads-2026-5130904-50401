#include "FOO.hpp"
#include <istream>
#include <iostream>
#include <algorithm>

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

  size_t maxLen(const List< std::pair< std::string, List< size_t > > >& data)
  {
    size_t max = 0;
    LCIter< std::pair< std::string, List< size_t > > > it = data.begin();
    while (it.hasNext())
    {
      max = std::max(max, (*it).second.size());
      it = it.next();
    }
    return max;
  }

  bool canShowItem(const List< size_t >& nums, size_t istr)
  {
    return nums.size() >= istr;
  }

  void printAllList(List< std::pair< std::string, List< size_t > > >& data, std::ostream& out)
  {
    if(data.size() < 1)
    {
      out << "0\n";
    }
    else
    {
      LIter< std::pair< std::string, List< size_t > > > outIt = data.begin();
      for(; outIt != data.end(); outIt = outIt.next())
      {
        out << (*outIt).first;
        if(outIt.hasNext())
        {
          out << " ";
        }
      }
      out << "\n";

      size_t maxListLen = maxLen(data);
      List< size_t > sums;
      LIter< size_t > s = sums.begin();
      for(size_t i = 0; i < maxListLen; i++)
      {
        outIt = data.begin();
        size_t sum = 0;
        bool firstInRow = true;
        while (outIt.hasNext())
        {
          if(canShowItem((*outIt).second, i + 1))
          {
            LIter< size_t > n = (*outIt).second.begin();
            for(size_t j = 0; j < i; ++j)
            {
              n = n.next();
            }
            if (!firstInRow)
            {
              out << " ";
            }
            out << *n;
            sum += *n;
            firstInRow = false;
          }
          outIt = outIt.next();
        }
        out << "\n";
        s = sums.insert(s, sum);
      }
      showSums(sums, out);
      sums.clear();
    }
    data.clear();
  }

  void showSums(List< size_t >& sums, std::ostream& out)
  {
    if (sums.begin() != sums.end())
    {
      LIter< size_t > it = sums.begin();
      out << *it;
      it = it.next();
      while (it != sums.end())
      {
        out << " " << *it;
        it = it.next();
      }
      out << "\n";
    }
  }
}
