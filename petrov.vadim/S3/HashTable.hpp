#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <cstddef>
#include <memory>
#include <iostream>
#include "HashNode.hpp"

namespace petrov
{
  struct Finder
  {
    size_t idx;
    bool found;
  };

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
    bool has(const Key& k) const;
    Value& get(const Key& k);
    const Value& get(const Key& k) const;
    void swap(HashTable& other) noexcept;

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

      size_t home(const Key& k) const;
      size_t probe(size_t home, size_t i) const;
      Finder find(const Key& k) const;
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
      return *this;
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
      return *this;
    }
    HashTable< Key, Value, Hash, Equal> cpy(std::move(other));
    swap(cpy);
    return *this;
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::add(const Key& k, const Value& v)
  {
    if (data_[home(k)].state_ != OCCUPIED)
    {
      data_[home(k)] = {k, v, OCCUPIED};
      ++size_;
    }
    else
    {
      Finder check = find(k);
      if (check.found)
      {
        data_[check.idx] = {k, v, OCCUPIED};
        ++size_;
      }
      else
      {
        std::cerr << "No slot for add element\n";
      }
    }
  }

  template< class Key, class Value, class Hash, class Equal >
  Value HashTable< Key, Value, Hash, Equal >::drop(const Key& k)
  {
    Finder check = find(k);
    if (!check.found)
    {
      return nullptr;
    }

    Value res = data_[check.idx].value_;
    data_[check.idx].key_ = nullptr;
    data_[check.idx].value_ = nullptr;
    data_[check.idx].state_ = TOMBSTONE;

    return res;
  }

  template< class Key, class Value, class Hash, class Equal >
  bool HashTable< Key, Value, Hash, Equal >::has(const Key& k) const
  {
    return find(k).found;
  }

  template< class Key, class Value, class Hash, class Equal >
  Value& HashTable< Key, Value, Hash, Equal >::get(const Key& k)
  {
    Finder f = find(k);

    if (f.found && data_[f.idx].state_ == OCCUPIED)
    {
      return data_[f.idx].value_;
    }
    return nullptr;
  }

  template< class Key, class Value, class Hash, class Equal >
  const Value& HashTable< Key, Value, Hash, Equal >::get(const Key& k) const
  {
    Finder f = find(k);

    if (f.found && data_[f.idx].state_ == OCCUPIED)
    {
      return data_[f.idx].value_;
    }
    return nullptr;
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::swap(HashTable& other) noexcept
  {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(hash_, other.equal_);
    std::swap(equal_, other.equal_);
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::rehash(size_t slots)
  {
    HashNode< Key, Value >* newData = new HashNode< Key, Value >[capacity_ + 16];
    for (size_t i = 0; i < capacity_; ++i)
    {
      newData[i] = data_[i];
    }

    delete[] data_;
    data_ = newData;
    capacity_ += 16;
  }

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

  template< class Key, class Value, class Hash, class Equal >
  size_t HashTable< Key, Value, Hash, Equal >::home(const Key& k) const
  {
    return hash_(k) % capacity_;
  }

  template< class Key, class Value, class Hash, class Equal >
  size_t HashTable< Key, Value, Hash, Equal >::probe(size_t home, size_t i) const
  {
    return home + i * i;
  }

  template< class Key, class Value, class Hash, class Equal >
  Finder HashTable< Key, Value, Hash, Equal >::find(const Key& k) const
  {
    size_t h = home(k);
    size_t first_tmbs = capacity_;
    for (size_t i = 0; i < capacity_ - 1; ++i)
    {
      size_t idx = probe(home, i);
      if (data_[idx].state == OCCUPIED && (equal_(data_[idx].key_, k)))
      {
        return {idx, true};
      }
      else if (data_[idx].state == TOMBSTONE && (first_tmbs == capacity_))
      {
        first_tmbs = idx;
      }
      else if (data_[idx].state_ == EMPTY)
      {
        return {first_tmbs == capacity_ ? idx : first_tmbs, false}
      }
    }
    return {first_tmbs == capacity_ ? h : first_tmbs, false}
  }

}
#endif
