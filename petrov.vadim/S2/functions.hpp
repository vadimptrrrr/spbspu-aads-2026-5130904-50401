#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <cstddef>
#include <istream>
#include "stack.hpp"
#include "queue.hpp"
#include "math.hpp"

namespace details
{
  using ll = long long;
  using namespace petrov;

  bool isOperator(const std::string& token);
  size_t getPriority(const std::string& op);
  Stack< Queue < std::string > > getInfix(std::istream& in);
  Stack< Queue < std::string > > infixToPostfix(Stack< Queue < std::string > >& data);
}

namespace petrov
{
  ll pickOperation(ll a, ll b, const std::string& op);
  ll calculatePostfix(Queue<std::string> postfix);
}

#endif
