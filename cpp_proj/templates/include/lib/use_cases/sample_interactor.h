#pragma once

#include <memory>

#include "{{LIB.DIR}}/use_cases/i_sample_interactor_input.h"
#include "{{LIB.DIR}}/use_cases/i_sample_interactor_output.h"

namespace use_cases {
class SampleInteractor : public ISampleInteractorInput {
 public:
  SampleInteractor() {}

  void SetOutput(std::shared_ptr<ISampleInteractorOutput> output) {
    output_ = output;
  }

  void DoSomething(entities::SampleInteractorRequest request) override {
    entities::SampleInteractorResponse response;
    response.response_data = request.request_data;

    if (output_) {
      output_->PresentSomething(response);
    }
  };

 private:
  std::shared_ptr<ISampleInteractorOutput> output_;
};

}  // namespace use_cases
