#ifndef KUKU_HASH_TABLE
#define KUKU_HASH_TABLE

#include <cstddef>
#include "../common/vector/top-it-vector.hpp"
#include "hash_node.hpp"

namespace petrov
{
  template< class Value, class Key, class Hash, class Equal > 
  struct KukuHashTable
  {
    KukuHashTable();
    KukuHashTable(size_t cap);
    ~KukuHashTable();
    KukuHashTable(const KukuHashTable& other);
    KukuHashTable(KukuHashTable&& other) noexcept;
    KukuHashTable& operator=(const KukuHashTable& other);
    KukuHashTable& operator=(KukuHashTable&& other) noexcept;

    void add(const Key& k, const Value& v);
    Value drop(const Key& k);
    bool has(const Key& k) const;
    Value& get(const Key& k);
    const Value& get(const Key& k) const;
    void swap(KukuHashTable& other) noexcept;

    void rehash(size_t slots);
    void clear();

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    bool empty() const noexcept;

    // HIter< Key, Value > begin();
    // HIter< Key, Value > end();
    // CHIter< Key, Value > begin() const;
    // CHIter< Key, Value > end() const;

    private:
      topit::Vector< detail::HashNode< Key, Value > > data1_;
      topit::Vector< detail::HashNode< Key, Value > > data2_;
      size_t size_;
      size_t capacity_;
      Hash hash1_;
      Hash hash2_;
      Equal equal_;
      double load_;
      size_t kicks_;

      size_t h1(const Key& key) const;
      size_t h2(const Key& key) const;
      Finder find(const Key& k) const;
  };
}


#endif