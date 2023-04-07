#include "{{LIB.DIR}}/{{LIB.FILENAME}}.h"

{% if EXTERN.fmt %}
#include <fmt/core.h>
{% endif %}
{% if EXTERN.spdlog %}
#include <spdlog/spdlog.h>
{% endif %}

#include <iostream>

namespace {{LIB.DIR}} {

void {{LIB.CLASS}}::PrintHello() { 
  std::cout << "Lib: Hello World !!!\n"; 
{% if EXTERN.fmt %}
  fmt::print("Lib: Hello FMT\n");
{% endif %}
}

bool {{LIB.CLASS}}::ReturnTrue() { 
  return true;
}

} // namespace {{LIB.DIR}}
