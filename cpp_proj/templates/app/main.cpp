{% if 'cxxopts_example' in app%}
#include <cxxopts.hpp>
{% endif %}
{% if 'fmt_example' in app%}
#include <fmt/core.h>
{% endif %}
#include <iostream>
#include <memory>
{% if 'nlohmann_json_example' in app%}
#include <nlohmann/json.hpp>
{% endif %}
{% if 'spdlog_example' in app%}
#include <spdlog/spdlog.h>
{% endif %}
{% if 'wxwidgets' in extern %}
#include <wx/wx.h>
{% endif %}

{% if 'lib_example' in app%}
#include "{{lib.specs.dir}}/{{lib.specs.filename}}.h"
{% endif %}
{% if 'clean_architecture_example' in app %}
#include "{{lib.specs.dir}}/controller/sample_controller.h"
#include "{{lib.specs.dir}}/db/sample_repository.h"
#include "{{lib.specs.dir}}/presenter/sample_presenter.h"
#include "{{lib.specs.dir}}/use_cases/sample_interactor.h"

{% endif %}
{% if 'nlohmann_json_example' in app%}
using json = nlohmann::json;

void NlohmannJsonTest() {
  // or even nicer with a raw string literal
  auto j = R"(
    {
      "happy": true,
      "pi": 3.141
    }
  )"_json;

  // serialization with pretty printing
  // pass in the amount of spaces to indent
  std::cout << j.dump(4) << std::endl;
}
{% endif %}

{% if 'spdlog_example' in app%}
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
{% if 'cxxopts_example' in app%}
int ParseCommandLine(int argc, const char **argv) {
  cxxopts::Options options("{{app.specs.target}}", "One line description of \"{{app.specs.target}}\"");

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
  } catch (const cxxopts::OptionParseException &x) {
    std::cerr << "{{app.specs.target}}: " << x.what() << '\n';
    std::cerr << "usage: {{app.specs.target}} [options] <filenames> ...\n";
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
      std::cout << "- " << file << "\n";
    }
  }
  return EXIT_SUCCESS;
}

{% endif %}
{% if 'clean_architecture_example' in app %}
void TestCleanArchitecture() {
  std::cout << "Test Clean Architecture" << std::endl;
  auto sample_repository = std::make_shared<{{lib.specs.dir}}::db::SampleRepository>();

  auto sample_presenter = std::make_shared<{{lib.specs.dir}}::presenter::SamplePresenter>();

  auto sample_interactor = std::make_shared<{{lib.specs.dir}}::use_cases::SampleInteractor>(sample_repository);
  sample_interactor->SetOutput(sample_presenter);

  auto sample_controller = std::make_shared<{{lib.specs.dir}}::controller::SampleController>();
  sample_controller->SetOutput(sample_interactor);

  sample_controller->DoSomething();
}

{% endif %}
{% if not 'wxwidgets' in extern %}
int main(int argc, const char *argv[]) {
  int ret = EXIT_SUCCESS;

  // Print welcome message
  std::cout << "App: Hello World !!!\n";
{% if 'fmt_example' in app%}
  // Test string format library
  fmt::print("App: Hello FMT\n");

{% endif %}
{% if 'spdlog_example' in app%}
  // Test logging library
  LogTest();

{% endif %}
{% if 'nlohmann_json_example' in app%}
  // Nlohmanns json lib test
  NlohmannJsonTest();

{% endif %}
{% if 'lib_example' in app%}
  // Test local library
  {{lib.specs.dir}}::{{lib.specs.class}} lib;
  lib.PrintHello();

{% endif %}
{% if 'clean_architecture_example' in app %}
  // Test clean architecture implementation
  TestCleanArchitecture();

{% endif %}
{% if 'cxxopts_example' in app%}
  // Parse command line options
  ret = ParseCommandLine(argc, argv);

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
{% if 'fmt_example' in app%}
  // Test string format library
  fmt::print("App: Hello FMT\n");

{% endif %}
{% if 'spdlog_example' in app%}
  // Test logging library
  LogTest();

{% endif %}
{% if 'lib_example' in app%}
  {{lib.specs.dir}}::{{lib.specs.class}} lib;
  lib.PrintHello();

{% endif %}
{% if 'nlohmann_json_example' in app%}
  // Nlohmanns json lib test
  NlohmannJsonTest();

{% endif %}
{% if 'clean_architecture_example' in app %}
  // Test clean architecture implementation
  TestCleanArchitecture();

{% endif %}
{% if 'cxxopts_example' in app%}
  // Parse command line options
  // Currently not supported when using wxWdigets

  // the argv type has an overload so that it can be casted safely to (char**)
  char** cargv = ( char**)argv; 

  // ugly hack ... assume that the values will not change in the future
  const char ** ccargv = const_cast<const char **>(cargv);

  static_cast<void>(ParseCommandLine(argc, ccargv));

{% endif %}
  Simple *simple = new Simple(wxT("Simple"));
  simple->Show(true);

  return true;
}
{% endif %}

