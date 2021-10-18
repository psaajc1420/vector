#include <iostream>
#include <algorithm>
#include "vector.h"

template<typename RandomAccessIterator>
void BubbleSort(RandomAccessIterator first, RandomAccessIterator last) {
  for (auto i = first; i != last; ++i)
    for (auto j = first; j < i; ++j)
      if (*i < *j) std::swap(*i, *j);

}

template<typename ForwardIterator, typename T>
ForwardIterator Find(T key, ForwardIterator first, ForwardIterator last) {

  for (auto it = first; it != last; ++it) {
    if (*it == key) return it;
  }

  return last;
}

int main() {
  library::Vector<int> nums = {4, 5, 10, 1, 3, 45, 2};
  BubbleSort(nums.Begin(), nums.End());

  for (auto it = nums.Begin(); it != nums.End(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  auto it = Find(1, nums.Begin(), nums.End());
  std::cout << *it << std::endl;

  return 0;
}
