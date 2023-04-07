
// unittest_SimpleMath.cpp : Defines the entry point for the console application.

#include "gtest/gtest.h"
#include "gmock/gmock.h"  
#include <memory>

#include "{{LIB.DIR}}/use_cases/sample_interactor.h"
#include "{{LIB.DIR}}/use_cases/i_sample_repository.h"
#include "{{LIB.DIR}}/use_cases/i_sample_interactor_output.h"

using namespace {{LIB.DIR}};

using ::testing::AtLeast;
using ::testing::_;
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
    sample_repository_ = std::make_shared<MockSampleRepository>();
    sample_interactor_output_ = std::make_shared<MockSampleInteractorOutput>();

    sample_interactor_ = std::make_shared<use_cases::SampleInteractor>(sample_repository_);
    sample_interactor_->SetOutput(sample_interactor_output_);
  }

  std::shared_ptr<MockSampleRepository> sample_repository_;
  std::shared_ptr<MockSampleInteractorOutput> sample_interactor_output_;
  std::shared_ptr<use_cases::SampleInteractor> sample_interactor_; 
};

TEST(SampleInteractorTestWithoutPresenter, DoSomethingDefaultCallNoException)
{
    auto sample_repository = std::make_shared<MockSampleRepository>();
    auto sample_interactor = std::make_shared<use_cases::SampleInteractor>(sample_repository);
    EXPECT_NO_THROW({
        sample_interactor->DoSomething({});
    });
}

TEST_F(SampleInteractorTest, DoSomethingCallsPresenterOneTime)
{
    // Arrange
    entities::SampleInteractorRequest request = {};
    request.request_data = 0xAFFE;

    EXPECT_CALL(*sample_interactor_output_, PresentSomething(_))
      .Times(1);

    // Act
    sample_interactor_->DoSomething(request);

    // Assert
}

TEST_F(SampleInteractorTest, DoSomethingCallsPresenterWithAFFEArg)
{
    // Arrange
    entities::SampleInteractorRequest request = {};
    request.request_data = 0xAFFE;


    EXPECT_CALL(*sample_interactor_output_, PresentSomething(Field( &entities::SampleInteractorResponse::response_data, 0xAFFE)));

    // Act
    sample_interactor_->DoSomething(request);

    // Assert
}
TEST_F(SampleInteractorTest, DoSomethingCallsPresenterWithAFFEArgFailing)
{
    // Arrange
    entities::SampleInteractorRequest request = {};
    request.request_data = 0xAFFF;


    EXPECT_CALL(*sample_interactor_output_, PresentSomething(Field( &entities::SampleInteractorResponse::response_data, 0xAFFE)));

    // Act
    sample_interactor_->DoSomething(request);

    // Assert
}
