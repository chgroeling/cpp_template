#pragma once

{% if 'spdlog_example' in lib%}
#include <memory>
{% endif %}

{% if 'spdlog_example' in lib%}
namespace spdlog {
class logger;
}
{% endif %}
/// \brief namespace of example library
namespace {{lib.specs.dir}} {

/// \brief This is an example class.
///
/// The functions of this class are only examples.
/// * PrintHello() prints hello.
/// * ReturnTrue() return true.
/// 
/// Go back to \ref mainpage
class {{lib.specs.class}} {
public:
  /// Constructor
  {{lib.specs.class}}();

  /// Deconstructor
  virtual ~{{lib.specs.class}}();

  /// \brief This method prints hello to std::cout.
  void PrintHello();
  
  /// \return This method returns true.
  bool ReturnTrue();

private:
{% if 'nlohmann_json_example' in lib%}
  /// Json Test
  void NlohmannJsonTest();

{% endif %}
{% if 'sqlitecpp_example' in lib%}
  /// Test method for sqlitecpp
  void SqliteCppTest();

{% endif %}
{% if 'spdlog_example' in lib%}
  /// Print outs test logging messages
  void LogTest();

  std::shared_ptr<spdlog::logger> logger_;
{% endif %}
};

} // namespace {{lib.specs.dir}}
