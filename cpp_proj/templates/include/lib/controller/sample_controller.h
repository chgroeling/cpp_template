#pragma once

#include <memory>

#include "{{LIB.DIR}}/use_cases/i_sample_interactor_input.h"

namespace controller {

class SampleController {
 public:
  void SetOutput(std::shared_ptr<use_cases::ISampleInteractorInput> output) {
    output_ = output;
  }

  void DoSomething() {
    entities::SampleInteractorRequest request;
    request.request_data = 12345;
    if (output_) {
      output_->DoSomething(request);
    }
  }

 private:
  std::shared_ptr<use_cases::ISampleInteractorInput> output_;
};

}  // namespace controller
