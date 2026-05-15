#include "Grath.hpp"
#include "HIter.hpp"
#include "CHIter.hpp"

namespace petrov
{
  Grath::Grath():
    name_(""),
    edges_(),
    vertices_()
  {}

  Grath::Grath(const Grath& other):
    name_(other.name_),
    edges_(other.edges_),
    vertices_(other.vertices_)
  {}

  Grath::Grath(Grath&& other) noexcept:
    name_(std::move(other.name_)),
    edges_(std::move(other.edges_)),
    vertices_(std::move(other.vertices_))
  {}

  void Grath::addVertex(const std::string& name)
  {
    vertices_.add(name, true);
  }

  void Grath::addEdge(const std::string& from, const std::string& to, size_t w)
  {
    if (hasVertex(from) && hasVertex(to))
    {
      edges_.add({from, to}, Weight{w});
    }
    else
    {
      throw std::runtime_error("Vertex not found\n");
    }
  }

  void Grath::removeVertex(const std::string& name)
  {
    if (!hasVertex(name))
    {
      throw std::runtime_error("Vertex not found\n");
    }
    vertices_.drop(name);
  }

  void Grath::removeEdge(const std::string& from, const std::string& to, size_t w)
  {
    if (hasEdge(from, to))
    {
      Weight& wght = edges_.get({from, to});
      for (size_t i = 0; i < wght.getSize(); ++i)
      {
        if (wght[i] == w)
        {
          wght.erase(i);
          return;
        }
      }
      throw std::runtime_error("Edge with such weight not found\n");
    }
    else
    {
      throw std::runtime_error("Edge not found\n");
    }
  }

  bool Grath::hasVertex(const std::string& name) const
  {
    return vertices_.has(name);
  }

  bool Grath::hasEdge(const std::string& from, const std::string& to) const
  {
    return edges_.has({from, to});
  }

  topit::Vector< std::string > Grath::getVertices() const
  {
    CHIter< std::string, bool > it = vertices_.begin();
    topit::Vector< std::string > res;
    for (; it != vertices_.end(); ++it)
    {
      res.pushBack(it->key_);
    }
    return res;
  }

  topit::Vector< EdgeVec > Grath::getInputEdges(const std::string& name) const
  {
    topit::Vector< EdgeVec > res;
    CHIter< EdgeKey, Weight > it = edges_.begin();
    for (; it != edges_.end(); ++it)
    {
      if (it->key_.second == name)
      {
        res.pushBack({it->key_.first, it->value_});
      }
    }
    return res;
  }

  topit::Vector< EdgeVec > Grath::getOutputEdges(const std::string& name) const
  {
    topit::Vector< EdgeVec > res;
    CHIter< EdgeKey, Weight > it = edges_.begin();
    for (; it != edges_.end(); ++it)
    {
      if (it->key_.first == name)
      {
        res.pushBack({it->key_.second, it->value_});
      }
    }
    return res;
  }
}