#include <iostream>

#include "lib/lib.h"

int main(int argc, const char* argv[]) {
  std::cout << "Hello World\n";
  lib::Lib lib;

  lib.PrintHello();
}
