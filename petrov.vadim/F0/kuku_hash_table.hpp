#ifndef KUKU_HASH_TABLE
#define KUKU_HASH_TABLE

#include <cstddef>
#include "../common/vector/top-it-vector.hpp"
#include "hash_node.hpp"

namespace petrov
{
  struct Finder
  {
    size_t idx_;
    bool found_;
  };

  template< class T >
  struct Equal
  {
    bool operator()(const T& lhs, const T& rhs) const;
  };

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
      size_t maxKicks_;

      size_t h1(const Key& key) const;
      size_t h2(const Key& key) const; 
      Finder find(const Key& k, size_t data_id) const;
  };

  template< class T >
  bool Equal< T >::operator()(const T& lhs, const T& rhs) const
  {
    return lhs == rhs;
  }

  template< class V, class K, class H, class E >
  KukuHashTable< V, K, H, E >::KukuHashTable():
    data1_(topit::Vector< detail::HashNode< K, V > >(16)),
    data2_(topit::Vector< detail::HashNode< K, V > >(16)),
    size_(0),
    capacity_(32),
    hash1_(),
    hash2_(),
    equal_(),
    load_(),
    maxKicks_(50)
  {}

  template< class V, class K, class H, class E >
  KukuHashTable< V, K, H, E >::KukuHashTable(size_t cap):
    data1_(topit::Vector< detail::HashNode< K, V > >(cap / 2)),
    data2_(topit::Vector< detail::HashNode< K, V > >(cap - cap / 2)),
    size_(0),
    capacity_(32),
    hash1_(),
    hash2_(),
    equal_(),
    load_(),
    maxKicks_(50)
  {}

  template< class V, class K, class H, class E >
  KukuHashTable< V, K, H, E >::~KukuHashTable()
  {
    clear();
  }

  template< class V, class K, class H, class E >
  KukuHashTable< V, K, H, E >::KukuHashTable(const KukuHashTable& other):
    data1_(other.data1_),
    data2_(other.data2_),
    size_(other.size_),
    capacity_(other.size_),
    hash1_(other.hash1_),
    hash2_(other.hash2_),
    equal_(other.equal_)
  {}

  template< class V, class K, class H, class E >
  KukuHashTable< V, K, H, E >::KukuHashTable(KukuHashTable&& other) noexcept:
    data1_(other.data1_),
    data2_(other.data2_),
    size_(other.size_),
    capacity_(other.size_),
    hash1_(other.hash1_),
    hash2_(other.hash2_),
    equal_(other.equal_)
  {
    other.data1_.~Vector();
    other.data2_.~Vector();
    other.size_ = 0;
    other.capacity_ = 0;
  }

  template< class V, class K, class H, class E >
  KukuHashTable< V, K, H, E >& KukuHashTable< V, K, H, E >::operator=(const KukuHashTable& other)
  {
    if (this == std::addressof(other))
    {
      return *this;
    }
    KukuHashTable< V, K, H, E > cpy = other;
    swap(cpy);
    return *this;
  }


  template< class V, class K, class H, class E >
  KukuHashTable< V, K, H, E >& KukuHashTable< V, K, H, E >::operator=(KukuHashTable&& other) noexcept
  {
    if (this == std::addressof(other))
    {
      return *this;
    }
    KukuHashTable< K, V, H, E> cpy(std::move(other));
    swap(cpy);
    return *this;
  }

  template< class V, class K, class H, class E >
  void KukuHashTable< V, K, H, E >::add(const K& k, const V& v)
  {
    if (load_ > 0.5)
    {
      rehash();
    }

    if (has(k))
    {
      get(k) = v;
      return;
    }

    K curr_k = k;
    V curr_v = v;
    for (size_t i = 0; i < maxKicks_; ++i)
    {
      Finder f = find(curr_k, 1);
      if (f.found_)
      {
        data1_[f.idx_].value_ = curr_v;
        data1_[f.idx_].key_ = curr_k;
        data1_[f.idx_].state_ = OCCUPIED;
        ++size_;
        return;
      }
      std::swap(curr_k, data1_[idx1].key_);
      std::swap(curr_v, data1_[idx1].value_);

      f = find(curr_k, 2);
      if (f.found_)
      {
        data2_[f.idx_].value_ = curr_v;
        data2_[f.idx_].key_ = curr_k;
        data2_[f.idx_].state_ = OCCUPIED;
        ++size_;
        return;
      }
      std::swap(curr_k, data1_[idx1].key_);
      std::swap(curr_v, data1_[idx1].value_);
    }

    rehash(capacity_ * 2);
    add(curr_k, curr_v);
  }
}


#endif