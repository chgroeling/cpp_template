{% if EXTERN.fmt %}
#include <fmt/core.h>
{% endif %}
#include <iostream>
#include <memory>
{% if EXTERN.spdlog %}
#include <spdlog/spdlog.h>
{% endif %}
{% if EXTERN.wxWidgets %}
#include <wx/wx.h>
{% endif %}
{% if EXTERN.cxxopts%}
#include <cxxopts.hpp>
{% endif %}

{% if PARTS.cleanarchitecture %}
#include "{{LIB.DIR}}/controller/sample_controller.h"
#include "{{LIB.DIR}}/db/sample_repository.h"
#include "{{LIB.DIR}}/presenter/sample_presenter.h"
#include "{{LIB.DIR}}/use_cases/sample_interactor.h"

{% endif %}
#include "{{LIB.DIR}}/{{LIB.FILENAME}}.h"

{% if EXTERN.spdlog%}
void LogTest() {
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
{% if EXTERN.cxxopts%}
int parse_command_line(int argc, const char *argv[]) {
  cxxopts::Options options("{{APP.TARGET}}", "One line description of \"{{APP.TARGET}}\"");

  options.positional_help("<filenames>");

  // clang-format off
  options.add_options()
    ("l,filelist", "Print out file list to be read") // a bool parameter
    ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
    ("h,help", "Print usage")
    ("input_files", "Input file(s) to concatenate",cxxopts::value<std::vector<std::string>>())
    ;
  // clang-format on

  // parse positional arguments into vector filenames
  options.parse_positional({"input_files"});

  cxxopts::ParseResult result;
  try {
    result = options.parse(argc, argv);
  } catch (const cxxopts::OptionParseException& x) {
    std::cerr << "{{APP.TARGET}}: " << x.what() << '\n';
    std::cerr << "usage: {{APP.TARGET}} [options] <filenames> ...\n";
    return EXIT_FAILURE;
  }

  // print out help if necessary
  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    return EXIT_SUCCESS;
  }

  // Enable logging
  switch (result.count("verbose")) {
    case 0:
      // no output
      break;
    case 1:
      std::cout << "verbose:1\n";
      break;
    case 2:
      std::cout << "verbose:2\n";
      break;
    default:
      std::cout << "verbose:?\n";
      break;
  }

  if (result.count("filelist")) {
    std::cout << "filelist command \n";
    const auto files = result["input_files"].as<std::vector<std::string>>();
    for (const auto &file : files) {
      std::cout<<"- "<<file<<"\n";
    }
  }
  return EXIT_SUCCESS;
}

{% endif %}
{% if PARTS.cleanarchitecture %}
void TestCleanArchitecture() {
  auto sample_repository = std::make_shared<{{LIB.DIR}}::db::SampleRepository>();

  auto sample_presenter = std::make_shared<{{LIB.DIR}}::presenter::SamplePresenter>();

  auto sample_interactor = std::make_shared<{{LIB.DIR}}::use_cases::SampleInteractor>(sample_repository);
  sample_interactor->SetOutput(sample_presenter);

  auto sample_controller = std::make_shared<{{LIB.DIR}}::controller::SampleController>();
  sample_controller->SetOutput(sample_interactor);

  sample_controller->DoSomething();
}

{% endif %}
{% if not EXTERN.wxWidgets %}
int main(int argc, const char *argv[]) {
  int ret = EXIT_SUCCESS;

  // Print welcome message
  std::cout << "App: Hello World !!!\n";

  // Test local library
  {{LIB.DIR}}::{{LIB.CLASS}} lib;
  lib.PrintHello();

{% if PARTS.cleanarchitecture %}
  // Test clean architecture implementation
  TestCleanArchitecture();

{% endif %}
{% if EXTERN.fmt %}
  // Test string format library
  fmt::print("App: Hello FMT\n");

{% endif %}
{% if EXTERN.spdlog%}
  // Test logging library
  LogTest();

{% endif %}
{% if EXTERN.cxxopts%}
  // Parse command line options
  ret = parse_command_line(argc, argv);

{% endif %}
  return ret;
}
{% else %}
class Simple : public wxFrame {
public:
  Simple(const wxString &title);
};

Simple::Simple(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150)) {
  Centre();
}

class MyApp : public wxApp {
public:
  virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
  // Print welcome message
  std::cout << "App: Hello World !!!\n";
  {{LIB.DIR}}::{{LIB.CLASS}} lib;
  lib.PrintHello();

{% if PARTS.cleanarchitecture %}
  // Test clean architecture implementation
  TestCleanArchitecture();

{% endif %}
{% if EXTERN.fmt %}
  // Test string format library
  fmt::print("App: Hello FMT\n");

{% endif %}
{% if EXTERN.spdlog%}
  // Test logging library
  LogTest();

{% endif %}
{% if EXTERN.cxxopts%}
  // Parse command line options
  // Currently not supported when using wxWdigets
  // ret = parse_command_line(argc, argv);

{% endif %}
  Simple *simple = new Simple(wxT("Simple"));
  simple->Show(true);

  return true;
}
{% endif %}

