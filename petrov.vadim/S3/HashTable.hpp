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
    HashTable();
    HashTable(size_t cap);
    ~HashTable();
    HashTable(const HashTable& other);
    HashTable(HashTable&& other) noexcept;
    HashTable& operator=(const HashTable& other);
    HashTable& operator=(HashTable&& other) noexcept;

    void add(const Key& k, const Value& v);
    Value drop(const Key& k);
    bool has(const Key& k);
    Value& get(const Key& k);
    const Value& get(const Key& k) const;

    void rehash(size_t slots);
    void clear();

    private:
      HashNode<Key, Value>* data_;
      size_t size_;
      size_t capacity_;
      Hash hash_;
      Equal equal_;
  };
}
#endif
