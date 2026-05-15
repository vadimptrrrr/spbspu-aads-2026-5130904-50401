#ifndef CHITER_HPP
#define CHITER_HPP

#include "HashNode.hpp"
#include <memory>
#include <cassert>

namespace petrov
{
  template< class K, class V, class Hash, class Equal >
  struct HashTable;

  template< class Key, class Value >
  struct HIter
  {
    template< class K, class V, class Hash, class Equal >
    friend struct HashTable;

    HIter();

    HIter< Key, Value >& operator++();
    HIter< Key, Value >& operator++(int);
    bool operator==(const HIter< Key, Value >& rhs) const;
    bool operator!=(const HIter< Key, Value >& rhs) const;

    HashNode< Key, Value >& operator*() const;
    HashNode< Key, Value >* operator->() const;

    private:
      const HashNode< Key, Value >* node_;
      const HashNode< Key, Value >* end_;

      HIter(const HashNode< Key, Value > * node, const HashNode< Key, Value > * end);
      void skipInvalid();
  };

  
}

#endif
