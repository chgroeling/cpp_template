#pragma once

#include <iostream>
#include <memory>

#include "{{LIB.DIR}}/use_cases/i_sample_interactor_output.h"

namespace {{LIB.DIR}} {
namespace presenter {

class SamplePresenter : public use_cases::ISampleInteractorOutput {
 public:
  void PresentSomething(entities::SampleInteractorResponse response) {
    std::cout << "SamplePresenter::PresentSomething called with response "
              << response.response_data << "\n";
  }
};

}  // namespace presenter
}  // namespace {{LIB.DIR}}
