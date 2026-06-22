#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../common/List/list_struct.hpp"
#include <stdexcept>
#include <cstddef>
#include <utility>

namespace petrov
{
  template< typename T >
  class Queue {
  public:
    Queue() = default;
    Queue(const Queue< T >& q) = default;
    Queue(Queue< T >&& q) noexcept = default;

    Queue< T >& operator=(const Queue< T >& q) = default;
    Queue< T >& operator=(Queue< T >&& q) noexcept = default;
    ~Queue() = default;

    void push(const T& rhs);
    void push(T&& rhs);

    const T& front() const;
    T& front();

    void pop();

    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear() noexcept;

  private:
    List< T > list_;
  };

  template< typename T >
  void Queue< T >::push(const T& rhs)
  {
    list_.insert_after(list_.end(), rhs);
  }

  template< typename T >
  void Queue< T >::push(T&& rhs)
  {
    list_.insert_after(list_.end(), std::forward(rhs));
  }

  template< typename T >
  const T& Queue< T >::front() const
  {
    if (empty())
    {
      throw std::runtime_error("Queue is empty");
    }
    return *list_.begin();
  }

  template< typename T >
  T& Queue< T >::front()
  {
    if (empty())
    {
      throw std::runtime_error("Queue is empty");
    }
    return *list_.begin();
  }

  template< typename T >
  void Queue< T >::pop()
  {
    if (empty())
    {
      throw std::runtime_error("Queue is empty");
    }
    list_.pop_front();
  }

  template< typename T >
  bool Queue< T >::empty() const noexcept
  {
    return list_.size() == 0;
  }

  template< typename T >
  size_t Queue< T >::size() const noexcept
  {
    return list_.size();
  }

  template< typename T >
  void Queue< T >::clear() noexcept
  {
    list_.clear();
  }
}
#endif
