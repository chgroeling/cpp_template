#include "{{lib.specs.dir}}/{{lib.specs.filename}}.h"

{% if 'sqlitecpp_example' in lib%}
#include <SQLiteCpp/SQLiteCpp.h>
{% endif %}
{% if 'fmt_example' in lib%}
#include <fmt/core.h>
{% endif %}
#include <iostream>
{% if 'nlohmann_json_example' in lib%}
#include <nlohmann/json.hpp>
{% endif %}
{% if 'spdlog_example' in lib%}
#include <spdlog/sinks/stdout_color_sinks.h>
//#include <spdlog/sinks/null_sink.h>
#include <spdlog/spdlog.h>
{% endif %}

namespace {{lib.specs.dir}} {

{% if 'spdlog_example' in lib%}
{{lib.specs.class}}::{{lib.specs.class}}() {
  logger_ = spdlog::get("{{lib.specs.class}}");
  if (!logger_) { // logger was not initialized beforehand
    logger_ = spdlog::stdout_color_mt("{{lib.specs.class}}");
    // Usually it is good to provide a null sink in case no logger was
    // registered by the app
    //
    // logger_ = spdlog::null_logger_mt("BitStream");
  }
};
{% else %}
{{lib.specs.class}}::{{lib.specs.class}}(){};
{% endif %}

{{lib.specs.class}}::~{{lib.specs.class}}(){};

void {{lib.specs.class}}::PrintHello() {
  std::cout << "Lib: Hello World !!!\n";
{% if 'fmt_example' in lib%}
  fmt::print("Lib: Hello FMT\n");
{% endif %}
{% if 'spdlog_example' in lib%}
  LogTest();
{% endif %}
{% if 'nlohmann_json_example' in lib%}
  NlohmannJsonTest();
{% endif %}
{% if 'sqlitecpp_example' in lib%}
  SqliteCppTest();
{% endif %}
}

bool {{lib.specs.class}}::ReturnTrue() {
  return true;
}
{% if 'spdlog_example' in lib%}
void {{lib.specs.class}}::LogTest() {
  logger_->info("Welcome to spdlog!");
  logger_->error("Some error message with arg: {}", 1);
  
  logger_->warn("Easy padding in numbers like {:08d}", 12);
  logger_->critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
  logger_->info("Support for floats {:03.2f}", 1.23456);
  logger_->info("Positional args are {1} {0}..", "too", "supported");
  logger_->info("{:<30}", "left aligned");
  
  logger_->set_level(spdlog::level::debug); // Set global log level to debug
  logger_->debug("This message should be displayed..");
}

{% endif %}
{% if 'nlohmann_json_example' in lib%}
void {{lib.specs.class}}::NlohmannJsonTest() {
  using json = nlohmann::json;
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
{% if 'sqlitecpp_example' in lib%}
void {{lib.specs.class}}::SqliteCppTest() {
  try {
    SQLite::Database db("transaction.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    db.exec("DROP TABLE IF EXISTS test");

    // Begin transaction
    SQLite::Transaction transaction(db);

    db.exec("CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT)");

    int nb = db.exec("INSERT INTO test VALUES (NULL, \"test\")");
    std::cout << "INSERT INTO test VALUES (NULL, \"test\")\", returned " << nb << std::endl;

    // Commit transaction
    transaction.commit();
  } catch (std::exception &e) {
    std::cout << "exception: " << e.what() << std::endl;
  }
}
{% endif %}

} // namespace {{lib.specs.dir}}
