#ifndef COMANDS_HPP
#define COMANDS_HPP

#include <iostream>
#include <string>
#include <cstddef>
#include "BSTree.hpp"

namespace petrov
{
  using dataset = BSTree< size_t, std::string >;
  using collection = BSTree< std::string, dataset >;

  void print(std::istream& in, std::ostream& out, collection& coll);
  void complement(std::istream& in, std::ostream& out, collection& coll);
  void intersect(std::istream& in, std::ostream& out, collection& coll);
  void unionn(std::istream& in, std::ostream& out, collection& coll);
}

#endif
