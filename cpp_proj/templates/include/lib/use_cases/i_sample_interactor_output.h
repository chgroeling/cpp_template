#pragma once

#include "{{lib.specs.dir}}/entities/sample_interactor_response.h"

namespace {{lib.specs.dir}} {
namespace use_cases {

class ISampleInteractorOutput {
public:
  virtual void PresentSomething(
      entities::SampleInteractorResponse response) = 0;
};

} // namespace use_cases
} // namespace {{lib.specs.dir}}
