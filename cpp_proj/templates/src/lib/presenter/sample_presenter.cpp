#include "{{lib.specs.dir}}/presenter/sample_presenter.h"

using namespace {{lib.specs.dir}}::presenter;

SamplePresenter::SamplePresenter() {
}

void SamplePresenter::PresentSomething(entities::SampleInteractorResponse response) {
  std::cout << "SamplePresenter::PresentSomething called with response "
            << response.response_data << "\n";
}
