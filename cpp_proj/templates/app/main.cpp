#include <iostream>

#include "{{LIB.DIR}}/{{LIB.FILENAME}}.h"

int main(int argc, const char* argv[]) {
  std::cout << "App: Hello World !!!\n";
  {{LIB.DIR}}::{{LIB.CLASS}} lib;

  lib.PrintHello();
}
