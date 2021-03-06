#include "Utils/Testing.hpp"

#include "Core/Status.hpp"

using namespace Core;

TEST_CASE("static creators", "[Status]") {
  SECTION("OK status has OK status code") {
    REQUIRE(Status::OK.getCode() == StatusCode::OK);
  }
  SECTION("NotImplemented status has NotImplemented status code") {
    REQUIRE(Status::NotImplemented.getCode() == StatusCode::NotImplemented);
  }
}

TEST_CASE("Status can be constructed", "[Status]") {

  auto status = Status(StatusCode::OK, "test");

  SECTION("status code retained") {
    REQUIRE(status.getCode() == StatusCode::OK);
  }
  SECTION("message retained") {
    REQUIRE(status.getMessage() == "test");
  }
  SECTION("inner status is null by default") {
    REQUIRE(status.getInnerStatus() == nullptr);
  }
  SECTION("inner status is retained") {
    auto outer = Status(StatusCode::NotFound, "test", status);
    REQUIRE(outer.getInnerStatus()->getCode() == StatusCode::OK);
  }
}

TEST_CASE("Status copy semantic", "[Status]") {
  SECTION("inner status is copied using its copy constructor") {
    auto innerStaus = Status(StatusCode::Created, "inner");
    auto status = Status(StatusCode::OK, "status", innerStaus);

    auto statusCopy(status);

    REQUIRE(status.getInnerStatus() != nullptr);
    REQUIRE(statusCopy.getInnerStatus()->getCode() == StatusCode::Created);
    REQUIRE(statusCopy.getInnerStatus()->getMessage() == "inner");
  }

  SECTION("inner status is copied using its assignment operator") {
    auto innerStaus = Status(StatusCode::Created, "inner");
    auto status = Status(StatusCode::OK, "status", innerStaus);

    auto statusCopy = Status::OK;
    REQUIRE(statusCopy.getCode() == StatusCode::OK);
    statusCopy = status;

    REQUIRE(status.getInnerStatus() != nullptr);
    REQUIRE(statusCopy.getInnerStatus()->getCode() == StatusCode::Created);
    REQUIRE(statusCopy.getInnerStatus()->getMessage() == "inner");
  }
}

TEST_CASE("Status move semantic", "[Status]") {
  SECTION("inner status is copied using its copy constructor") {
    auto innerStaus = Status(StatusCode::Created, "inner");
    auto status = Status(StatusCode::OK, "status", innerStaus);

    auto statusCopy(std::move(status));

    REQUIRE(status.getInnerStatus() == nullptr);
    REQUIRE(statusCopy.getInnerStatus()->getCode() == StatusCode::Created);
    REQUIRE(statusCopy.getInnerStatus()->getMessage() == "inner");
  }

  SECTION("inner status is copied using its assignment operator") {
    auto innerStaus = Status(StatusCode::Created, "inner");
    auto status = Status(StatusCode::OK, "status", innerStaus);

    auto statusCopy = std::move(status);

    REQUIRE(status.getInnerStatus() == nullptr);
    REQUIRE(statusCopy.getInnerStatus()->getCode() == StatusCode::Created);
    REQUIRE(statusCopy.getInnerStatus()->getMessage() == "inner");
  }
}

TEST_CASE("Status isOK method", "[Status]") {
  SECTION("is OK when status code is OK") {
    auto status = Status(StatusCode::OK, "test");
    REQUIRE(status.isOk());
  }
  SECTION("is not OK when status code is not OK") {
    auto status = Status(StatusCode::Accepted, "test");
    REQUIRE(!status.isOk());
  }
}
