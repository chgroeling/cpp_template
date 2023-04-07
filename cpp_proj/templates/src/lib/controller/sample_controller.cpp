#include "{{LIB.DIR}}/controller/sample_controller.h"

using namespace {{LIB.DIR}}::controller;

SampleController::SampleController() {
}

void SampleController::SetOutput(std::shared_ptr<use_cases::ISampleInteractorInput> output) {
  output_ = output;
}

void SampleController::DoSomething() {
  entities::SampleInteractorRequest request;
  request.request_data = 12345;
  if (output_) {
    output_->DoSomething(request);
  }
}
