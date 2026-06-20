#include <fstream>
#include <iostream>
#include "commands.hpp"
#include "help_functions.hpp"

void petrov::FuncManage::mk_user(std::ostream&, std::istream& in, const std::string& str)
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

  using plans_t = KukuHashTable< User::train_ex_t, std::string, KKHash< std::string >, Equal< std::string > >;
  User u = User{h, w, o, 0, plans_t{}};
  u.stamina_ = petrov::detail::countStamina(u);
  users_.add(str, u);
}

void petrov::FuncManage::rm_user(std::ostream&, std::istream&, const std::string& str)
{
  if (!users_.has(str))
  {
    throw std::runtime_error("User invalid");
  }

  users_.drop(str);
}

void petrov::FuncManage::update_user(std::ostream&, std::istream& in, const std::string& str)
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

void petrov::FuncManage::show_users(std::ostream& out, std::istream&, const std::string&)
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

void petrov::FuncManage::save(std::ostream&, std::istream&, const std::string& str)
{
  std::ofstream file(str);
  if (!file.is_open())
  {
    throw std::runtime_error("File invalid");
  }

  file << users_.size() << '\n';
  for (auto it = users_.cbegin(); it != users_.cend(); ++it)
  {
    file << it->key_ << '\n';
    file << it->value_.height_ << ' ' << it->value_.weight_ << ' ' << it->value_.old_ << '\n';

    file << it->value_.plans_.size() << '\n';
    auto plans_it = it->value_.plans_.cbegin();
    for (; plans_it != it->value_.plans_.cend(); ++plans_it)
    {
      file << plans_it->key_ << ' ' << plans_it->value_.size() << '\n';
      auto ex_it = plans_it->value_.cbegin();
      if (plans_it->value_.size() > 0)
      {
        file << ex_it->key_ << ' '
        << ex_it->value_.sets_ << ' '
        << ex_it->value_.reps_ << ' '
        << ex_it->value_.muscleGroup_ << ' '
        << ex_it->value_.stamina_;
        ++ex_it;
      }

      for (; ex_it != plans_it->value_.cend(); ++ex_it)
      {
        file << ' ' << ex_it->key_
        << ' ' << ex_it->value_.sets_
        << ' ' << ex_it->value_.reps_
        << ' ' << ex_it->value_.muscleGroup_
        << ' ' << ex_it->value_.stamina_;
      }
      file << '\n';
    }
  }

  file << pools_.size() << '\n';
  auto pool_it = pools_.cbegin();
  for (; pool_it != pools_.cend(); ++pool_it)
  {
    file << pool_it->key_ << ' ' << pool_it->value_.size() << '\n';
    auto ex_it = pool_it->value_.cbegin();
    if (pool_it->value_.size() > 0)
    {
      file << ex_it->key_ << ' '
      << ex_it->value_.muscleGroup_ << ' '
      << ex_it->value_.stamina_;
      ++ex_it;
    }

    for (; ex_it != pool_it->value_.cend(); ++ex_it)
    {
      file << ' ' << ex_it->key_
      << ' ' << ex_it->value_.muscleGroup_
      << ' ' << ex_it->value_.stamina_;
    }
    file << '\n';
  }
}
