#include "intconv.h"

int main (int argc, char *argv[]) {
  char base_in, base_out, word[128], buffer[BUFFER_SIZE];

  if (!isatty(fileno(stdin))) {
    if (argc != 2 && argc != 3) {
      usage();
      return -1;
    }
    base_in = (argv[1][0] == '-')? argv[1][1] : '?';
    base_out = (argc == 3)? (argv[2][0] == '-')? argv[2][1] : '?' : '?';

    while (fgets(buffer, BUFFER_SIZE, stdin)) {
      buffer[strlen(buffer) - 1] = 
        (buffer[strlen(buffer) - 1] == '\n')? '\0' : buffer[strlen(buffer) - 1];
      std::string line(buffer);
      std::istringstream parser(line);
      if (base_in == 'c') {
        int i = 0;
        while (line[i] != '\0') {
          formatted_output(base_in, base_out, &line[i]);
          i++;
        }
      } else {
        while (parser >> word)
          formatted_output(base_in, base_out, word);
      }
    }
    if (base_out != '?')
      logdn("");
    return 0;
  } else if (argc < 3) {
    usage();
    return -1;
  }
  
  base_in = (argv[1][0] == '-')? argv[1][1] : '?';
  base_out = (argv[2][0] == '-')? argv[2][1] : '?';
  for (int i = (base_out == '?')? 2 : 3; i < argc; i++) {
    if (base_in == 'c') {
      char space[2] = {' '};
      int j = 0;
      while (argv[i][j] != '\0') {
        formatted_output(base_in, base_out, &argv[i][j]);
        j++;
      }
      if (i != argc - 1)
        formatted_output(base_in, base_out, space);
    } else {
      formatted_output(base_in, base_out, argv[i]);
    }
  }
  if (base_out != '?')
    logdn("");
  return 0;
}

void formatted_output(char base_in, char base_out, char *input) {
  unsigned num;
  switch (base_in) {
    case 'b':
      if (!isValidBinary(input)) {
        errm("Invalid binary");
      }
      num = base2d(input, BIN);
      break;
    case 'd':
      if (!isValidDecimal(input)) {
        errm("Invalid decimal");
      }
      num = atoi(input);
      break;
    case 'c':
      if (!isValidChar(input)) {
        errm("Invalid char");
      }
      num = (int)input[0];
      break;
    case 'h':
      if (!isValidHex(input)) {
        errm("Invalid hex");
      }
      num = base2d(input, HEX);
      break;
    case 'o':
      if (!isValidOctal(input)) {
        errm("Invalid octal");
      }
      num = base2d(input, OCT);
      break;
    default: errm("Invalid format");
  }
  switch (base_out) {
    case 'b': logds(d2base(num, BIN)); break;
    case 'd': logds(num); break;
    case 'c': logd((char)num); break;
    case 'h': logds(d2base(num, HEX)); break;
    case 'o': logds(d2base(num, OCT)); break;
    case '?': out_all(num); break;
    default: errm("Invalid format");
  }
}

void out_all(int num) {
  logdn("Binary  : " << d2base(num, BIN));
  logdn("Octal   : " << d2base(num, OCT));
  logdn("Decimal : " << num);
  logdn("Hex     : " << d2base(num, HEX));
  logdn("ASCII   : " << (char)num);
}

void usage() {
  std::cout <<
    "Usage: conv INPUT_BASE [OUTPUT_BASE] INPUT(S)" << std::endl <<
    "Converts INPUT from base INPUT_BASE to other bases." << std::endl <<
    "Base options:" << std::endl <<
    "  -b    binary" << std::endl <<
    "  -o    octal" << std::endl <<
    "  -d    decimal" << std::endl <<
    "  -h    hex" << std::endl <<
    "  -c    ASCII char" << std::endl <<
    "If OUTPUT is specified, prints only that base." << std::endl;
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
