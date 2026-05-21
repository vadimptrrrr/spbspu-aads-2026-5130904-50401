#ifndef TNODE_HPP
#define TNODE_HPP

namespace detail
{
  template < class Key, class Value >
  struct TNode
  {
    Key key_;
    Value value_;
    TNode *left_;
    TNode *right_;
    TNode *parent_;

    TNode(Key k, Value v);
  };

  template < class Key, class Value >
  TNode< Key, Value >::TNode(Key k, Value v):
    key_(k),
    value_(v),
    left_(nullptr),
    right_(nullptr),
    parent_(nullptr)
  {}
}

#endif
