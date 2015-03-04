#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <stdlib.h>

#define HEX 16
#define OCT 8
#define BIN 2

#define logd(msg) std::cout << msg << std::endl;
#define errm(msg) logd(msg); return -1;

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
	if (s.size() != 1)
		return false;
	if ((int)s[0] < 0 || (int)s[0] > 255)
		return false;
	return true;
}
bool isValidOctal(std::string s) {
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