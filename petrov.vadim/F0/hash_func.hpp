#ifndef HASH_FUNC_HPP
#define HASH_FUNC_HPP

#include <cstddef>
#include <boost/functional/hash.hpp>

namespace petrov
{
  template <class Key>
  struct KKHash
  {
    size_t seed_;

    KKHash(size_t seed = 0):
      seed_(seed)
    {}

    size_t operator()(const Key& key) const
    {
      size_t hash_val = seed_;
      boost::hash_combine(hash_val, key);
      return hash_val;
    }
  };
}

#endif
