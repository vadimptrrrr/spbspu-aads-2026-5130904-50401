#ifndef TNODE_HPP
#define TNODE_HPP

namespace detail
{
  template < class Key, class Value >
  struct TNode
  {
    Key key;
    Value value;
    TNode *left;
    TNode *right;

    TNode(Key k, Value v);
  };

  template < class Key, class Value >
  TNode< Key, Value >::TNode(Key k, Value v):
    key(k),
    value(v),
    left(nullptr),
    right(nullptr)
  {}
}

#endif
