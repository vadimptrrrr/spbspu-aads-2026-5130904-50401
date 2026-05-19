#include "foo.hpp"
#include <istream>
#include <iostream>
#include <algorithm>
#include <limits>

void petrov::mkData(std::istream& input, List< std::pair< std::string, List< size_t > > >& data)
{
  std::string name;
  while(input >> name)
  {
    List< size_t > nums;
    size_t num;
    LIter< size_t > inPos = nums.back();
    while (input >> num)
    {
      inPos = nums.insert_after(inPos, num);
    }
    data.insert_after(data.back(), {name, nums});

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

size_t petrov::maxLen(const List< std::pair< std::string, List< size_t > > >& data)
{
  size_t max = 0;
  LCIter< std::pair< std::string, List< size_t > > > it = data.begin();
  while (it != data.end())
  {
    max = std::max(max, it->second.size());
    ++it;
  }
  return max;
}

bool petrov::canShowItem(const List< size_t >& nums, size_t istr)
{
  return nums.size() >= istr;
}

void petrov::printAllList(List< std::pair< std::string, List< size_t > > >& data, std::ostream& out)
{
  if(data.size() < 1)
  {
    out << "0" << "\n";
  }
  else
  {
    LIter< std::pair< std::string, List< size_t > > > outIt = data.begin();
    out << outIt->first;
    ++outIt;
    for(; outIt != data.end(); ++outIt)
    {
      out << " " << outIt->first;
    }
    out << "\n";

    size_t maxListLen = maxLen(data);
    List< size_t > sums;
    LIter< size_t > s = sums.back();

    for(size_t i = 0; i < maxListLen; ++i)
    {
      outIt = data.begin();
      size_t sum = 0;

      while (outIt != data.end() && !canShowItem(outIt->second, i + 1))
      {
        ++outIt;
      }

      if (outIt != data.end())
      {
        LIter< size_t > n = outIt->second.begin();
        for(size_t j = 0; j < i; ++j)
        {
          ++n;
        }
        if (*n > std::numeric_limits< size_t >::max() - sum)
        {
          throw std::overflow_error("Overflow in sum calculation");
        }

        out << *n;
        sum += *n;
        ++outIt;

        while (outIt != data.end())
        {
          if(canShowItem(outIt->second, i + 1))
          {
            n = outIt->second.begin();
            for(size_t j = 0; j < i; ++j)
            {
              ++n;
            }

            if (*n > std::numeric_limits< size_t >::max() - sum)
            {
              throw std::overflow_error("Overflow in sum calculation");
            }

            out << " " << *n;
            sum += *n;
          }
          ++outIt;
        }
      }
      out << '\n';
      s = sums.insert_after(s, sum);
    }
    showSums(sums, out);
    sums.clear();
  }
  data.clear();
}

void petrov::showSums(List< size_t >& sums, std::ostream& out)
{
  if (sums.begin() != sums.end())
  {
    LIter< size_t > it = sums.begin();
    out << *it;
    ++it;
    while (it != sums.end())
    {
      out << " " << *it;
      ++it;
    }
    out << "\n";
  }
  else
  {
    out << "0\n";
  }
}
