#pragma once

#include <memory>

#include "{{lib.specs.dir}}/use_cases/i_sample_interactor_input.h"

namespace {{lib.specs.dir}} {
namespace controller {

class SampleController {
public:
  SampleController();
  void SetOutput(std::shared_ptr<use_cases::ISampleInteractorInput> output);
  void DoSomething();

private:
  std::shared_ptr<use_cases::ISampleInteractorInput> output_;
};

} // namespace controller
} // namespace {{lib.specs.dir}}
