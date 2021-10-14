#include <iostream>
#include "vector.h"

using namespace std;

int main() {

  Vector<int> nums = {1, 2, 3, 4, 5};

  cout << nums.Size() << endl;

//  for (int i = 0; i < nums.Size(); i++) cout << nums[i] << endl;

  return 0;
}
