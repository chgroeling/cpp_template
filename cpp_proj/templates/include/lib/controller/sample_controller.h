#pragma once

#include <memory>

#include "{{LIB.DIR}}/use_cases/i_sample_interactor_input.h"

namespace {{LIB.DIR}} {
namespace controller {

class SampleController {
public:
  void SetOutput(std::shared_ptr<use_cases::ISampleInteractorInput> output);
  void DoSomething();

private:
  std::shared_ptr<use_cases::ISampleInteractorInput> output_;
};

} // namespace controller
} // namespace {{LIB.DIR}}
