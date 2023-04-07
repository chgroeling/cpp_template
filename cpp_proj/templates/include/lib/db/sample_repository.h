#pragma once

#include "{{LIB.DIR}}/use_cases/i_sample_repository.h"

namespace {{LIB.DIR}} {
namespace db {

class SampleRepository : public use_cases::ISampleRepository{
   public:
      virtual std::string Get(std::string key) {
         std::cout << "GET: "<< key <<"\n";
         return "";
      }

      virtual void Set(std::string key, std::string value) {
         std::cout << "SET: "<< key << " " << value <<"\n";
      }
};

}  // namespace use_cases
}  // namespace {{LIB.DIR}}
