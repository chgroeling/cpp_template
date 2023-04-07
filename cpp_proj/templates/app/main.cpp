#include <iostream>

#include "{{LIB.DIR}}/{{LIB.FILENAME}}.h"

int main(int argc, const char* argv[]) {
  std::cout << "Hello World\n";
  lib::Lib lib;

  lib.PrintHello();
}
