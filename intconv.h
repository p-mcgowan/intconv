#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>

#define HEX 16
#define OCT 8
#define BIN 2

#define BUFFER_SIZE 128

#define logd(msg) std::cout << msg;
#define logds(msg) std::cout << msg << ' ';
#define logdn(msg) std::cout << msg << std::endl;
#define errm(msg) logdn(msg); exit(-1);

// Help message
void usage();

// Output formatting
void formatted_output(char base_in, char base_out, char *input, int argc);
void out_all(int num);

// Conversions
std::string d2base(unsigned d, int b);
unsigned base2d(std::string n, int b);

// Valid input format
bool isValidBinary(std::string s) {
  for (size_t c = 0; c < s.size(); c++) {
    if (s[c] != '1' && s[c] != '0')
      return false;
  }
  return true;
}

bool isValidDecimal(std::string s) {
  for (size_t c = 0; c < s.size(); c++) {
    if (s[c] < '0' || s[c] > '9')
      return false;
  }
  return true;
}

bool isValidChar(std::string s) {
  if ((int)s[0] < 0 || (int)s[0] > 255)
    return false;
  return true;
}
bool
 isValidOctal(std::string s) {
  for (size_t c = 0; c < s.size(); c++) {
    if (s[c] < '0' || s[c] > '7')
      return false;
  }
  return true;
}

bool isValidHex(std::string s) {
  for (size_t c = 0; c < s.size(); c++) {
    if (!((tolower(s[c]) >= 'a' && tolower(s[c]) <= 'f') ||  (s[c] >= '0' && s[c] <= '9')))
      return false;
  }
  return true;
}
