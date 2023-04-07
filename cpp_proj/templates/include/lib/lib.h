#pragma once

/// \brief namespace of example library
namespace {{LIB.DIR}} {

/// \brief This is an example class.
///
/// The functions of this class are only examples.
/// * PrintHello() prints hello.
/// * ReturnTrue() return true.
/// 
/// Go back to \ref mainpage
class {{LIB.CLASS}} {
 public:
  {{LIB.CLASS}}(){};

  /// \brief This method prints hello to std::cout.
  void PrintHello();
  
  /// \return This method returns true.
  bool ReturnTrue();
};

} // namespace {{LIB.DIR}}
