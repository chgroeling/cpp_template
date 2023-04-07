#pragma once

#include <iostream>
#include <memory>

#include "{{lib.specs.dir}}/use_cases/i_sample_interactor_output.h"

namespace {{lib.specs.dir}} {
namespace presenter {

class SamplePresenter : public use_cases::ISampleInteractorOutput {
public:
  SamplePresenter();
  void PresentSomething(entities::SampleInteractorResponse response);
};

} // namespace presenter
} // namespace {{lib.specs.dir}}
