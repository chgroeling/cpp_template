#pragma once

#include "{{LIB.DIR}}/entities/sample_interactor_response.h"

namespace {{LIB.DIR}} {
namespace use_cases {

class ISampleInteractorOutput {
   public:
    virtual void PresentSomething(
        entities::SampleInteractorResponse response) = 0;
};

}  // namespace use_cases
}  // namespace {{LIB.DIR}}
