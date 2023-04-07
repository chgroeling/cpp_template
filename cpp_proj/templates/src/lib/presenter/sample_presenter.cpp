#include "{{LIB.DIR}}/presenter/sample_presenter.h"

using namespace {{LIB.DIR}}::presenter;

SamplePresenter::SamplePresenter() {
}

void SamplePresenter::PresentSomething(entities::SampleInteractorResponse response) {
  std::cout << "SamplePresenter::PresentSomething called with response "
            << response.response_data << "\n";
}
