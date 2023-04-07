#include "{{LIB.DIR}}/use_cases/sample_interactor.h"

using namespace {{LIB.DIR}}::use_cases;

SampleInteractor::SampleInteractor(std::shared_ptr<ISampleRepository> repo) : repo_(repo) {}

void SampleInteractor::SetOutput(std::shared_ptr<ISampleInteractorOutput> output) {
  output_ = output;
}

void SampleInteractor::DoSomething(entities::SampleInteractorRequest request) {
  entities::SampleInteractorResponse response;
  response.response_data = request.request_data;

  repo_->Get("KEY1");
  repo_->Set("KEY2", "VALUE2");

  if (output_) {
    output_->PresentSomething(response);
  }
};

