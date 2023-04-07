{% if EXTERN.fmt %}
#include <fmt/core.h>
{% endif %}
{% if EXTERN.spdlog %}
#include <spdlog/spdlog.h>
{% endif %}

#include <memory>
#include <iostream>

#include "{{LIB.DIR}}/controller/sample_controller.h"
#include "{{LIB.DIR}}/{{LIB.FILENAME}}.h"
#include "{{LIB.DIR}}/presenter/sample_presenter.h"
#include "{{LIB.DIR}}/use_cases/sample_interactor.h"
#include "{{LIB.DIR}}/db/sample_repository.h"

{% if EXTERN.spdlog%}
void log_test() {
  spdlog::info("Welcome to spdlog!");
  spdlog::error("Some error message with arg: {}", 1);
  
  spdlog::warn("Easy padding in numbers like {:08d}", 12);
  spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
  spdlog::info("Support for floats {:03.2f}", 1.23456);
  spdlog::info("Positional args are {1} {0}..", "too", "supported");
  spdlog::info("{:<30}", "left aligned");
  
  spdlog::set_level(spdlog::level::debug); // Set global log level to debug
  spdlog::debug("This message should be displayed.."); 
}
{% endif %}

int main(int argc, const char* argv[]) {
  std::cout << "App: Hello World !!!\n";
  {{LIB.DIR}}::{{LIB.CLASS}} lib;

  lib.PrintHello();
{% if EXTERN.fmt %}
  fmt::print("App: Hello FMT\n");
{% endif %}
{% if EXTERN.spdlog%}
  log_test();
{% endif %}

  auto sample_repository = std::make_shared<{{LIB.DIR}}::db::SampleRepository>();

  auto sample_presenter = std::make_shared<{{LIB.DIR}}::presenter::SamplePresenter>();

  auto sample_interactor = std::make_shared<{{LIB.DIR}}::use_cases::SampleInteractor>(sample_repository);
  sample_interactor->SetOutput(sample_presenter);

  auto sample_controller = std::make_shared<{{LIB.DIR}}::controller::SampleController>();
  sample_controller->SetOutput(sample_interactor);

  sample_controller->DoSomething();
}
