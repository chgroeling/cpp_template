#pragma once

#include "{{LIB.DIR}}/entities/sample_interactor_request.h"

namespace {{LIB.DIR}} {
namespace use_cases {

class ISampleInteractorInput {
public:
  virtual void DoSomething(entities::SampleInteractorRequest request) = 0;
};


} // namespace use_cases
} // namespace {{LIB.DIR}}
