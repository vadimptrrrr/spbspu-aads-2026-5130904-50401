#include <fstream>
#include <iostream>
#include "commands.hpp"
#include "help_functions.hpp"

void petrov::FuncManage::mk_user(std::ostream& out, std::istream& in, const std::string& str)
{
  size_t h, w, o;
  in >> h >> w >> o;
  if (!in)
  {
    throw std::runtime_error("Read invalid");
  }

  if (users_.has(str))
  {
    throw std::runtime_error("User invalid");
  }

  User u = User{h, w, o};
  u.stamina_ = petrov::detail::countStamina(u);
  users_.add(str, u);
}

void petrov::FuncManage::rm_user(std::ostream& out, std::istream& in, const std::string& str)
{
  if (!users_.has(str))
  {
    throw std::runtime_error("User invalid");
  }

  users_.drop(str);
}

void petrov::FuncManage::update_user(std::ostream& out, std::istream& in, const std::string& str)
{
  size_t h, w, o;
  in >> h >> w >> o;
  if (!in)
  {
    throw std::runtime_error("Read invalid");
  }

  if (!users_.has(str))
  {
    throw std::runtime_error("User invalid");
  }

  User& u = users_.get(str);
  u.height_ = h;
  u.weight_ = w;
  u.old_ = o;
  u.stamina_ = petrov::detail::countStamina(u);
}

void petrov::FuncManage::show_users(std::ostream& out, std::istream& in, const std::string& str)
{
  out << "<USERS>\n";
  if (users_.empty())
  {
    return;
  }

  using citer_t = CKKHTIterator<User, std::string, KKHash< std::string >, Equal< std::string > >;
  for (citer_t it = users_.cbegin(); it != users_.cend(); ++it)
  {
    out << it->key_ << '\n'
    << "Height: " << it->value_.height_ << '\n'
    << "Weight: " << it->value_.weight_ << '\n'
    << "Old: " << it->value_.old_ << '\n';
  }
}

void petrov::FuncManage::save(std::ostream& out, std::istream& in, const std::string& str)
{
  std::string file_name;
  in >> file_name;
  if (!in)
  {
    throw std::runtime_error("Read invalid");
  }

  std::ofstream file(file_name);
  if (!file.is_open())
  {
    throw std::runtime_error("File invalid");
  }

  file << users_.size();
  using citer_t = CKKHTIterator<User, std::string, KKHash< std::string >, Equal< std::string > >;
  for (citer_t it = users_.cbegin(); it != users_.cend(); ++it)
  {
    file << it->key_ << '\n';
    file << it->value_.height_ << ' ' << it->value_.weight_ << ' ' << it->value_.old_ << '\n';

    file << it->value_.plans_.size() << '\n';
    using citer_t = CKKHTIterator< User::train_ex_t, std::string, KKHash< std::string >, Equal< std::string > >;
    citer_t itt = it->value_.plans_.cbegin();
    for (; itt != it->value_.plans_.cend(); ++itt)
    {
      file << itt->key_ << ' ' << itt->value_.getSize() << '\n';
      if (itt->value_.getSize() > 0)
      {
        file << itt->value_[0];
      }
      for (size_t i = 1; i < itt->value_.getSize(); ++i)
      {
        file << ' ' << itt->value_[i];
      }
      file << '\n';
    }
  }
}
