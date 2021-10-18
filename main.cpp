#include <iostream>
#include <algorithm>
#include "vector.h"
#include <string>

template<typename RandomAccessIterator>
void BubbleSort(RandomAccessIterator first, RandomAccessIterator last) {
  for (auto i = first; i != last; ++i)
    for (auto j = first; j < i; ++j)
      if (*i < *j) std::swap(*i, *j);

}

template<typename RandomAccessIterator>
inline void MergeSort(RandomAccessIterator first, RandomAccessIterator last) {
  if (last <= first + 1) return;
  RandomAccessIterator middle = first + (last - first) / 2;
  MergeSort(first, middle);
  MergeSort(middle, last);
  std::inplace_merge(first, middle, last);
}

template<typename ForwardIterator, typename T>
ForwardIterator Find(T key, ForwardIterator first, ForwardIterator last) {

  for (auto it = first; it != last; ++it) {
    if (*it == key) return it;
  }

  return last;
}

void PrintVector(const library::Vector<int> &vec) {
  for (auto it = vec.cBegin(); it != vec.cEnd(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

int main() {

  std::cout << "Bubble Sort" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  library::Vector<int> nums = {4, 5, 10, 1, 3, 45, 2};
  PrintVector(nums);
  BubbleSort(nums.Begin(), nums.End());
  PrintVector(nums);
  std::cout << std::endl;

  std::cout << "Merge Sort" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  nums = {4, 5, 10, 1, 3, 45, 2};
  PrintVector(nums);
  MergeSort(nums.Begin(), nums.End());
  PrintVector(nums);
  std::cout << std::endl;

  std::cout << "Standard Library Sort" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  nums = {4, 5, 10, 1, 3, 45, 2};
  PrintVector(nums);
  std::sort(nums.Begin(), nums.End());
  PrintVector(nums);
  std::cout << std::endl;

  std::cout << "Find" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  auto it1 = Find(45, nums.Begin(), nums.End());
  auto it2 = Find(1, nums.Begin(), nums.End());
  it1 = nums.Begin() + (it1 - it2) / 2;
  std::cout << *it1 << std::endl;
  std::cout << std::endl;

  std::cout << "Const Iterator Functionality" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  library::Vector<std::string> words = {"hello", "world"};
  using ConstIterator = typename library::Vector<std::string>::const_iterator;
  for (ConstIterator it = words.cBegin(); it != words.cEnd(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;


  return 0;
}
