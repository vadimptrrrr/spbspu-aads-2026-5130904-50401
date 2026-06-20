#ifndef TRAIN_STRUCTS_HPP
#define TRAIN_STRUCTS_HPP

#include <cstddef>
#include <string>
#include "kuku_hash_table.hpp"
#include "hash_func.hpp"

namespace petrov
{
  struct Exercise
  {
    std::string muscleGroup_;
    int stamina_;
  };

  struct UExercise: Exercise
  {
    size_t sets;
    size_t reps;
  };

  struct User
  {
    size_t height_;
    size_t weight_;
    size_t old_;
    int stamina_;

    using train_ex_t = topit::Vector< std::string >;
    KukuHashTable< train_ex_t, std::string, KKHash< std::string >, Equal< std::string > > plans_; 
  };
}

#endif
