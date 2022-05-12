#include <filesystem>
#include <iostream>

#include "ardfs.h"

namespace afs = ard::filesystem;
namespace sfs = std::filesystem;

// These are *not* extensive, and I should make them actually test afs vs sfs

int main(void) {
  std::string testStr = "a/test/string/";

  afs::path a1{"/usr/lib"};
  afs::path a2;
  afs::path a3{a1};
  afs::path a4{"file"};
  afs::path a5{a1 / a4};
  afs::path a6{++testStr.cbegin(), --testStr.cend()};
  afs::path a7{testStr.substr(1)};

  sfs::path s1{"/usr/lib"};
  sfs::path s2;
  sfs::path s3{s1};
  sfs::path s4{"file"};
  sfs::path s5{s1 / s4};
  sfs::path s6{++testStr.cbegin(), --testStr.cend()};
  sfs::path s7{testStr.substr(1)};

  std::cout << "Construction:\n"
            << "a1 = " << a1 << " should be " << s1 << '\n'
            << "a2 = " << a2 << " should be " << s2 << '\n'
            << "a3 = " << a3 << " should be " << s3 << '\n'
            << "a4 = " << a4 << " should be " << s4 << '\n'
            << "a5 = " << a5 << " should be " << s5 << '\n'
            << "a6 = " << a6 << " should be " << s6 << '\n'
            << "a7 = " << a7 << " should be " << s7 << '\n';

  a7 = a6;
  a6 = a1 / a4;
  a5 = testStr.substr(1);
  a4.assign(testStr.substr(1, testStr.size() - 2));
  a3.assign(++(++testStr.cbegin()), --(--testStr.cend()));

  s7 = s6;
  s6 = s1 / s4;
  s5 = testStr.substr(1);
  s4.assign(testStr.substr(1, testStr.size() - 2));
  s3.assign(++(++testStr.cbegin()), --(--testStr.cend()));

  std::cout << "operator= & assign:\n"
            << "a1 = " << a1 << " should be " << s1 << '\n'
            << "a2 = " << a2 << " should be " << s2 << '\n'
            << "a3 = " << a3 << " should be " << s3 << '\n'
            << "a4 = " << a4 << " should be " << s4 << '\n'
            << "a5 = " << a5 << " should be " << s5 << '\n'
            << "a6 = " << a6 << " should be " << s6 << '\n'
            << "a7 = " << a7 << " should be " << s7 << '\n';

  a7 = a1;
  a7 += a4;
  a1 /= testStr;
  a2 += testStr;
  a4 += a3;
  a4 += ".suf";

  s7 = s1;
  s7 += s4;
  s1 /= testStr;
  s2 += testStr;
  s4 += s3;
  s4 += ".suf";

  std::cout << "operator+, /=, +, +=:\n"
            << "a1 = " << a1 << " should be " << s1 << '\n'
            << "a2 = " << a2 << " should be " << s2 << '\n'
            << "a4 = " << a4 << " should be " << s4 << '\n'
            << "a7 = " << a7 << " should be " << s7 << '\n';

  std::cout << "Component tests:\n"
            << "Path considered: " << a4 << '\n'
            << "Root name:       " << a4.root_name() << " should be "
            << s4.root_name() << '\n'
            << "Root dir:        " << a4.root_directory() << " should be "
            << s4.root_directory() << '\n'
            << "Root path:       " << a4.root_path() << " should be "
            << s4.root_path() << '\n'
            << "Relative path:   " << a4.relative_path() << " should be "
            << s4.relative_path() << '\n'
            << "Parent path:     " << a4.parent_path() << " should be "
            << s4.parent_path() << '\n'
            << "Filename:        " << a4.filename() << " should be "
            << s4.filename() << '\n'
            << "Extension:       " << a4.extension() << " should be "
            << s4.extension() << '\n'
            << "Stem:            " << a4.stem() << " should be " << s4.stem()
            << '\n';

  return 0;
}