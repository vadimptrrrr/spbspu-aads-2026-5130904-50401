#include <iostream>
#include <fstream>
#include "stack.hpp"
#include "functions.hpp"
#include "math.hpp"

int main(int argc, char* argv[])
{
  using namespace petrov;

  Stack< Queue<std::string> > infix;
  Stack< Queue<std::string> > postfix;
  Stack< ll > results;

  std::ifstream file;
  std::istream* in = &std::cin;

  if (argc > 1)
  {
    file.open(argv[1]);
    if (!file)
    {
      std::cerr << "Error: cannot open file\n";
      return 1;
    }
    in = &file;
  }

  try
  {
    infix = details::getInfix(*in);
    postfix = details::infixToPostfix(infix);

    while (!postfix.empty())
    {
      Queue<std::string> expr = postfix.top();
      postfix.pop();
      ll value = calculatePostfix(expr);
      results.push(value);
    }

    while (!results.empty())
    {
      std::cout << results.top();
      results.pop();
      if (!results.empty())
      {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << "Overflow error: " << e.what() << "\n";
    return 1;
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << "Math error: " << e.what() << "\n";
    return 1;
  }
  catch (const std::logic_error& e)
  {
    std::cerr << "Logic error: " << e.what() << "\n";
    return 1;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
