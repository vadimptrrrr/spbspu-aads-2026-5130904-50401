#ifndef BSTREE_HPP
#define BSTREE_HPP

#include "TNode.hpp"

namespace poetrov
{
  template < class Key, class Value, class Compare >
  struct BSTree
  {
    BSTree();
    BSTree(const BSTree& other);
    BSTree(BSTree&& other) noexcept;
    BSTree& operator=(const BSTree& other);
    BSTree& operator=(BSTree&& other) noexcept;
    ~BSTree();

    void push(const Key& k, const Value& v);
    Value& get(const Key& k);
    const Value& get(const Key& k) const;
    Value drop(Key k);

    using CIterator = BSTCIterator< Key, Value >;
    using Iterator = BSTIterator< Key, Value >;

    CIterator rotateLeft(CIterator it);
    CIterator rotateRight(CIterator it);

    CIterator rotateLargeLeft(CIterator it);
    CIterator rotateLargeRight(CIterator it);

    size_t height(CIterator it);
    size_t height();

    Iterator begin();
    Iterator end();
    CIterator begin() const;
    CIterator end() const;
    CIterator cbegin() const;
    CIterator cend() const;

    bool empty() const;

    private:
      TNode< Key, Value >* root_;
      TNode< Key, Value >* fake_leaf_;
      Compare comp_;
  };
}

#endif
