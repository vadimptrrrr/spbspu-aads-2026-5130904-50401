#ifndef STRUCTS_HPP
#define STRUCTS_HPP
#include <cstddef>
namespace petrov
{
  template< class T >
  struct Node
  {
    T val;
    Node< T >* next;
  };

  template< class T >
  class List;

  template< class T >
  class LIter
  {
    friend class List< T >;
    Node< T >* nd;

    public:
      LIter() noexcept;
      LIter(Node< T >* p) noexcept;
      bool hasNext() const noexcept;
      LIter< T > next() const;
      T& operator*() const;
      bool operator==(const LIter< T >& it) const noexcept;
      bool operator!=(const LIter< T >& it) const noexcept;
  };

  template< class T >
  class LCIter
  {
    friend class List< T >;
    const Node< T >* nd;

    public:
      LCIter() noexcept;
      LCIter(const Node< T >* p) noexcept;
      bool hasNext() const noexcept;
      LCIter< T > next() const;
      const T& operator*() const;
      bool operator==(const LCIter< T >& it) const noexcept;
      bool operator!=(const LCIter< T >& it) const noexcept;
  };

  template< class T >
  class List
  {
    Node< T >* fake;
    Node< T >* mkFake();
    void delFake() noexcept;

    public:
      List();
      List(const List< T >& l);
      List(List< T >&& l);
      List< T >& operator=(const List< T >& l);
      List< T >& operator=(List< T >&& l);
      ~List();
      void clear() noexcept;

      LIter< T > begin() noexcept;
      LCIter< T > begin() const noexcept;
      LIter< T > end() noexcept;
      LCIter< T > end() const noexcept;

      LIter< T > getLast() noexcept;
      LCIter< T > getLast() const noexcept;

      LIter< T > addStart(const T& a);
      void popStart() noexcept;

      LIter< T > insert(LIter< T > id, const T& a);
      LIter< T > insert(LIter< T > id, const T&& a);
  };
}
#endif
