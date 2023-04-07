#pragma once

#include "{{lib.specs.dir}}/entities/sample_interactor_request.h"

namespace {{lib.specs.dir}} {
namespace use_cases {

class ISampleInteractorInput {
public:
  virtual void DoSomething(entities::SampleInteractorRequest request) = 0;
};

} // namespace use_cases
} // namespace {{lib.specs.dir}}
