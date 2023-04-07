#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

#include "{{lib.specs.dir}}/use_cases/i_sample_interactor_output.h"
#include "{{lib.specs.dir}}/use_cases/i_sample_repository.h"
#include "{{lib.specs.dir}}/use_cases/sample_interactor.h"

using namespace {{lib.specs.dir}};

using ::testing::_;
using ::testing::NiceMock; // ignores uninteresting function calls.
using ::testing::StrictMock; // uninteresting function calls lead to failure.
//using ::testing::AtLeast;
using ::testing::Field;

class MockSampleRepository : public use_cases::ISampleRepository {
public:
  MOCK_METHOD(std::string, Get, (std::string), (override));
  MOCK_METHOD(void, Set, (std::string key, std::string value), (override));
};

class MockSampleInteractorOutput : public use_cases::ISampleInteractorOutput {
public:
  MOCK_METHOD(void, PresentSomething, (entities::SampleInteractorResponse response), (override));
};

class SampleInteractorTest : public ::testing::Test {
protected:
  void SetUp() override {
    sample_repository_ = std::make_shared<NiceMock<MockSampleRepository>>();
    sample_interactor_output_ = std::make_shared<MockSampleInteractorOutput>();

    sample_interactor_ = std::make_shared<use_cases::SampleInteractor>(sample_repository_);
    sample_interactor_->SetOutput(sample_interactor_output_);
  }

  std::shared_ptr<NiceMock<MockSampleRepository>> sample_repository_;
  std::shared_ptr<MockSampleInteractorOutput> sample_interactor_output_;
  std::shared_ptr<use_cases::SampleInteractor> sample_interactor_;
};

TEST(SampleInteractorTestWithoutPresenter, DoSomethingDefaultCallNoExceptionStrict) {
  auto sample_repository = std::make_shared<StrictMock<MockSampleRepository>>();

  // The calls must have a expect because its a StrictMock
  EXPECT_CALL(*sample_repository, Get(_));
  EXPECT_CALL(*sample_repository, Set(_,_));
  auto sample_interactor = std::make_shared<use_cases::SampleInteractor>(sample_repository);
  EXPECT_NO_THROW({
    sample_interactor->DoSomething({});
  });
}

TEST_F(SampleInteractorTest, DoSomethingCallsPresenterOneTime) {
  // Arrange
  entities::SampleInteractorRequest request = {};
  request.request_data = 0xAFFE;

  EXPECT_CALL(*sample_interactor_output_, PresentSomething(_))
      .Times(1);

  // Act
  sample_interactor_->DoSomething(request);

  // Assert
}

TEST_F(SampleInteractorTest, DoSomethingCallsPresenterWithAFFEArg) {
  // Arrange
  entities::SampleInteractorRequest request = {};
  request.request_data = 0xAFFE;

  EXPECT_CALL(*sample_interactor_output_, PresentSomething(Field(&entities::SampleInteractorResponse::response_data, 0xAFFE)));

  // Act
  sample_interactor_->DoSomething(request);

  // Assert
}

TEST_F(SampleInteractorTest, DoSomethingCallsPresenterWithAFFEArgFailing) {
  // Arrange
  entities::SampleInteractorRequest request = {};
  request.request_data = 0xAFFF;

  EXPECT_CALL(*sample_interactor_output_, PresentSomething(Field(&entities::SampleInteractorResponse::response_data, 0xAFFE)));

  // Act
  sample_interactor_->DoSomething(request);

  // Assert
}
