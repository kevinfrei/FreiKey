#include <iostream>

#include "ardfs.h"

namespace fs = ard::filesystem;

int main(void) {
  std::string testStr = "a/test/string/";
  fs::path p1{"/usr/lib"};
  fs::path p2;
  fs::path p3{p1};
  fs::path p4{"file"};
  fs::path p5{p1 / p4};
  fs::path p6{++testStr.cbegin(), --testStr.cend()};
  fs::path p7{testStr.substr(1)};

  std::cout << "Construction:\n"
            << "p1 = " << p1 << '\n'
            << "p2 = " << p2 << '\n'
            << "p3 = " << p3 << '\n'
            << "p4 = " << p4 << '\n'
            << "p5 = " << p5 << '\n'
            << "p6 = " << p6 << '\n'
            << "p7 = " << p7 << '\n';

  p7 = p6;
  p6 = p1 / p4;
  p5 = testStr.substr(1);
  p4.assign(testStr.substr(1, testStr.size() - 2));
  p3.assign(++testStr.cbegin(), -- (--testStr.cend()));
  std::cout << "operator=/assign:\n"
            << "p1 = " << p1 << '\n'
            << "p2 = " << p2 << '\n'
            << "p3 = " << p3 << '\n'
            << "p4 = " << p4 << '\n'
            << "p5 = " << p5 << '\n'
            << "p6 = " << p6 << '\n'
            << "p7 = " << p7 << '\n';

  return 0;
}