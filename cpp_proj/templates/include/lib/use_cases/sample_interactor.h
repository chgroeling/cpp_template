#pragma once

#include <memory>

#include "{{LIB.DIR}}/use_cases/i_sample_interactor_input.h"
#include "{{LIB.DIR}}/use_cases/i_sample_interactor_output.h"
#include "{{LIB.DIR}}/use_cases/i_sample_repository.h"

namespace {{LIB.DIR}} {
namespace use_cases {

class SampleInteractor : public ISampleInteractorInput {
 public:
  SampleInteractor(std::shared_ptr<ISampleRepository> repo): repo_(repo) {}

  void SetOutput(std::shared_ptr<ISampleInteractorOutput> output) {
    output_ = output;
  }

  void DoSomething(entities::SampleInteractorRequest request) override {
    entities::SampleInteractorResponse response;
    response.response_data = request.request_data;

    repo_->Get("KEY1");
    repo_->Set("KEY2", "VALUE2");

    if (output_) {
      output_->PresentSomething(response);
    }
  };

 private:
  std::shared_ptr<ISampleInteractorOutput> output_;
  std::shared_ptr<ISampleRepository> repo_;
};

}  // namespace use_cases
}  // namespace {{LIB.DIR}}
