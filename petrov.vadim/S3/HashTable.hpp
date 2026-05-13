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

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    bool empty() const noexcept;

    private:
      HashNode< Key, Value >* data_;
      size_t size_;
      size_t capacity_;
      Hash hash_;
      Equal equal_;
  };

  template< class T >
  bool Equal< T >::operator()(const T& lhs, const T& rhs) const
  {
    return lhs == rhs;
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::HashTable():
    data_(new HashNode< Key, Value > [8]),
    size_(0),
    capacity_(8),
    hash_(),
    equal_()
  {}

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::HashTable(size_t cap):
    data_(new HashNode< Key, Value > [cap]),
    size_(0),
    capacity_(cap),
    hash_(),
    equal_()
  {}

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::~HashTable()
  {
    delete[] data_;
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::HashTable(const HashTable& other):
    data_(new HashNode< Key, Value > [other.capacity_]),
    size_(other.size_),
    capacity_(other.capacity_),
    hash_(other.hash_),
    equal_(other.equal_)
  {
    for (size_t i = 0; i < capacity_; ++i)
    {
      data_[i] = other.data_[i];
    }
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::HashTable(HashTable&& other) noexcept:
    data_(other.data_),
    size_(other.size_),
    capacity_(other.capacity_),
    hash_(other.hash_),
    equal_(other.equal_)
  {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >& HashTable< Key, Value, Hash, Equal >::operator=(const HashTable& other)
  {
    if (this == std::addressof(other))
    {
      returnq *this;
    }
    HashTable< Key, Value, Hash, Equal> cpy = other;
    swap(cpy);
    return *this;
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >& HashTable< Key, Value, Hash, Equal>::operator=(HashTable&& other) noexcept
  {
    if (this == std::addressof(other))
    {
      returnq *this;
    }
    HashTable< Key, Value, Hash, Equal> cpy(std::move(other));
    swap(cpy);
    return *this;
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::add(const Key& k, const Value& v)
  {}

  template< class Key, class Value, class Hash, class Equal >
  Value HashTable< Key, Value, Hash, Equal >::drop(const Key& k)
  {}

  template< class Key, class Value, class Hash, class Equal >
  bool HashTable< Key, Value, Hash, Equal >::has(const Key& k)
  {}

  template< class Key, class Value, class Hash, class Equal >
  Value& HashTable< Key, Value, Hash, Equal >::get(const Key& k)
  {}

  template< class Key, class Value, class Hash, class Equal >
  const Value& HashTable< Key, Value, Hash, Equal >::get(const Key& k) const
  {}

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::rehash(size_t slots)
  {}

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::clear()
  {
    for (size_t i = 0; i < capacity_; ++i)
    {
      data_[i].state_ = EMPTY;
    }
    size_ = 0;
  }

  template< class Key, class Value, class Hash, class Equal >
  size_t HashTable< Key, Value, Hash, Equal >::size() const noexcept
  {
    return size_;
  }

  template< class Key, class Value, class Hash, class Equal >
  size_t HashTable< Key, Value, Hash, Equal >::capacity() const noexcept
  {
    return capacity_;
  }

  template< class Key, class Value, class Hash, class Equal >
  bool HashTable< Key, Value, Hash, Equal >::empty() const noexcept
  {
    return size_ == 0;
  }

}
#endif
