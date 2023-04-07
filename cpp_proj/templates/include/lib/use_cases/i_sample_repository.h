#pragma once

namespace {{LIB.DIR}} {
namespace use_cases {

class ISampleRepository {
public:
  virtual std::string Get(std::string key) = 0;
  virtual void Set(std::string key, std::string value) = 0;
};

} // namespace use_cases
} // namespace {{LIB.DIR}}
