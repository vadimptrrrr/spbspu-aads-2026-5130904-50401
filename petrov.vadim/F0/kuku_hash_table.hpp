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
    hash1_(0),
    hash2_(1234),
    equal_(),
    load_(),
    maxKicks_(50)
  {}

  template< class V, class K, class H, class E >
  KukuHashTable< V, K, H, E >::KukuHashTable(size_t cap):
    data1_(topit::Vector< detail::HashNode< K, V > >(cap / 2)),
    data2_(topit::Vector< detail::HashNode< K, V > >(cap - cap / 2)),
    size_(0),
    capacity_(cap),
    hash1_(0),
    hash2_(1234),
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
    capacity_(other.capacity_),
    hash1_(other.hash1_),
    hash2_(other.hash2_),
    equal_(other.equal_),
    load_(other.load_),
    maxKicks_(other.maxKicks_)
  {}

  template< class V, class K, class H, class E >
  KukuHashTable< V, K, H, E >::KukuHashTable(KukuHashTable&& other) noexcept:
    data1_(std::move(other.data1_)),
    data2_(std::move(other.data2_)),
    size_(other.size_),
    capacity_(other.capacity_),
    hash1_(std::move(other.hash1_)),
    hash2_(std::move(other.hash2_)),
    equal_(std::move(other.equal_)),
    load_(other.load_),
    maxKicks_(other.maxKicks_)
  {
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
    KukuHashTable< V, K, H, E> cpy(std::move(other));
    swap(cpy);
    return *this;
  }

  template< class V, class K, class H, class E >
  void KukuHashTable< V, K, H, E >::add(const K& k, const V& v)
  {
    if (load_ > 0.5)
    {
      rehash(capacity_ * 2);
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
      size_t idx1 = hash1_(curr_k) % data1_.getCapacity();
      if (data1_[idx1].state_ == detail::EMPTY)
      {
        data1_[idx1].value_ = curr_v;
        data1_[idx1].key_ = curr_k;
        data1_[idx1].state_ = detail::OCCUPIED;
        ++size_;
        load_ = static_cast< double >(size_) / capacity_;
        return;
      }
      std::swap(curr_k, data1_[idx1].key_);
      std::swap(curr_v, data1_[idx1].value_);


      size_t idx2 = hash2_(curr_k) % data2_.getCapacity();
      
      if (data2_[idx2].state_ == detail::EMPTY)
      {
        data2_[idx2].value_ = curr_v;
        data2_[idx2].key_ = curr_k;
        data2_[idx2].state_ = detail::OCCUPIED;
        ++size_;
        load_ = static_cast< double >(size_) / capacity_;
        return;
      }
      std::swap(curr_k, data2_[idx2].key_);
      std::swap(curr_v, data2_[idx2].value_);
    }

    rehash(capacity_ * 2);
    add(curr_k, curr_v);
  }
}

#endif
