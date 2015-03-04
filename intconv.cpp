#include "intconv.h"

int main (int argc, char *argv[]) {
	if (argc != 3 && argc != 4) {
		std::cout <<
		"Usage: conv OPTIONS INPUT [OUTPUT]" << std::endl <<
		"Converts INPUT from base OPTIONS to other bases." << std::endl <<
		"Options:" << std::endl <<
		"  -b    binary" << std::endl <<
		"  -o    octal" << std::endl <<
		"  -d    decimal" << std::endl <<
		"  -h    hex" << std::endl <<
		"  -c    ASCII char" << std::endl <<
		"If OUTPUT is specified, prints only that base." << std::endl;
		return 1;
	}
	unsigned num;
	if (!strcmp(argv[1], "-b")) {
		if (!isValidBinary(argv[2])) {
			errm("Invalid binary: " << argv[2]);
		}
		num = base2d(argv[2], BIN);
	}
	else if (!strcmp(argv[1], "-d")) {
		if (!isValidDecimal(argv[2])) {
			errm("Invalid decimal: " << argv[2]);
		}
		num = atoi(argv[2]);
	}
	else if (!strcmp(argv[1], "-c")) {
		if (!isValidChar(argv[2])) {
			errm("Invalid char: " << argv[2]);
		}
		num = (int)argv[2][0];
	}
	else if (!strcmp(argv[1], "-h")) {
		if (!isValidHex(argv[2])) {
			errm("Invalid hex: " << argv[2]);
		}
		num = base2d(argv[2], HEX);
	}
	else if (!strcmp(argv[1], "-o")) {
		if (!isValidOctal(argv[2])) {
			errm("Invalid octal: " << argv[2]);
		}
		num = base2d(argv[2], OCT);
	}
	else {
		errm("Invalid format");
	}
	if (argc == 3) {
		logd("Binary  : " << d2base(num, BIN));
		logd("Octal   : " << d2base(num, OCT));
		logd("Decimal : " << num);
		logd("Hex     : " << d2base(num, HEX));
		logd("ASCII   : " << (char)num);
		return 0;
	}
	if (!strcmp(argv[3], "-h"))
		logd(d2base(num, HEX));
	if (!strcmp(argv[3], "-b"))
		logd(d2base(num, BIN));
	if (!strcmp(argv[3], "-d"))
		logd(num);
	if (!strcmp(argv[3], "-o"))
		logd(d2base(num, OCT));
	if (!strcmp(argv[3], "-c"))
		logd((char)num);
	return 0;
}

unsigned base2d(std::string n, int b) {
	unsigned d = 0;
	int i = 0;
	for (int c = n.size() - 1; c >= 0; c--) {
		if (toupper(n[c]) > '9')
			d += (int)(10 + toupper(n[c])-'A')*pow(b,i++);
		else
			d += (int)(n[c] - '0')*pow(b,i++);
	}
	return d;
}

std::string d2base(unsigned d, int b) {
	if (d == 0)
		return "0";
	std::string base;
	int q = 0, r = 0;
	char v;
	while (d > 0) {
		q = d / b;
		r = (unsigned)d % b;
		if (r > 9)
			v = 'A' + r - 10;
		else 
			v = '0' + r;
		base = v + base;
		d = q;
	}
	return base;
}