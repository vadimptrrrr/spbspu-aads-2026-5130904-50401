#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <cstddef>
#include "HashNode.hpp"

namespace petrov
{
  template< class T >
  struct Equal
  {
    bool operator()(const T& lhs, const T& rhs) const;
  };

  template< class Key, class Value, class Hash, class Equal >
  struct HashTable
  {
    void add(const Key& k, const Value& v);
    Value drop(const Key& k);
    bool has(const Key& k);
    void rehash(size_t slots);

    private:
      HashNode<Key, Value>* data_;
      size_t size_;
      size_t capacity_;
      Hash hash_;
      Equal equal_;
  };
}
#endif
