#ifndef HITER_HPP
#define HITER_HPP

#include "HashTable.hpp"

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
    HIter< Key, Value >& operator--();
    bool operator==(const HIter< Key, Value >& rhs) const;
    bool operator!=(const HIter< Key, Value >& rhs) const;

    HashNode< Key, Value >& operator*() const;
    HashNode< Key, Value >* operator*() const;

    private:
      HashNode< Key, Value >* hode_;

      HTIter(HashNode< Key, Value > * node, HashNode< Key, Value > * end);
      void skipInvalid();
  };
}

#endif
