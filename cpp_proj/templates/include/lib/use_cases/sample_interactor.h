#pragma once

#include <memory>
#include <string>

#include "{{lib.specs.dir}}/use_cases/i_sample_interactor_input.h"
#include "{{lib.specs.dir}}/use_cases/i_sample_interactor_output.h"
#include "{{lib.specs.dir}}/use_cases/i_sample_repository.h"

namespace {{lib.specs.dir}} {
namespace use_cases {

class SampleInteractor : public ISampleInteractorInput {
public:
  SampleInteractor(std::shared_ptr<ISampleRepository> repo);
  void SetOutput(std::shared_ptr<ISampleInteractorOutput> output);
  void DoSomething(entities::SampleInteractorRequest request) override;
  
private:
  std::shared_ptr<ISampleInteractorOutput> output_;
  std::shared_ptr<ISampleRepository> repo_;
};

} // namespace use_cases
} // namespace {{lib.specs.dir}}
