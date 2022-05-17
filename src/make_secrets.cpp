#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

uint8_t rotl(char c, int num) {
  if (num > 7 || num < 1)
    return 0;
  return (static_cast<uint8_t>(c) << num) |
         (static_cast<uint8_t>(c) >> (8 - num));
}
char rotr(char c, int num) {
  if (num > 7 || num < 1)
    return 0;
  return static_cast<char>((static_cast<uint8_t>(c) >> num) |
                           (static_cast<uint8_t>(c) << (8 - num)));
}

int main(int argc, const char* argv[]) {
  do {
    std::string txt;
    std::cout << "Please enter the value for a secret:" << std::endl;
    std::getline(std::cin, txt);
    if (txt.empty())
      break;
    std::cout << "Here's the value, modified: " << std::endl << "\"";
    int r = 1;
    std::vector<char> vals;
    for (char v : txt) {
      uint8_t c = rotl(v, r);
      r = (r + v) % 6 + 1;
      if (c < 32 || c > 0x7e) {
        std::cout << "\\" << std::oct << std::setw(3) << std::setfill('0')
                  << static_cast<int32_t>(c);
      } else if (c == '\\') {
        std::cout << "\\\\";
      } else {
        std::cout << static_cast<char>(c);
      }
      vals.push_back(c);
    }
    std::cout << "\"" << std::endl << "Validated: " << std::endl << "\"";
    // And now to validate it can be undone:
    r = 1;
    for (char v : vals) {
      char nc = rotr(v, r);
      r = (r + nc) % 6 + 1;
      std::cout << nc;
    }
    std::cout << "\"" << std::endl;
  } while (true);
  return 0;
}
