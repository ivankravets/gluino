#include "Utils/Testing.hpp"

#include "Messaging/Event.hpp"

using namespace Messaging;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

}

TEST_CASE("Event can be constructed", "[Event]") {

  auto content = Content::makeShared();
  auto eventNoContent = Event::makeUnique("created", "resource");
  auto eventWithContent = Event::makeUnique("created", "resource", content);

  SECTION("type is correct") {
    REQUIRE(eventNoContent->getTypeId() == "event");
    REQUIRE(eventWithContent->getTypeId() == "event");
  }

  SECTION("event type retained") {
    REQUIRE(eventNoContent->getEventType() == "created");
    REQUIRE(eventWithContent->getEventType() == "created");
  }

  SECTION("resource retained") {
    REQUIRE(eventNoContent->getResource() == "resource");
    REQUIRE(eventWithContent->getResource() == "resource");
  }

  SECTION("content retained") {
    REQUIRE(eventWithContent->getContent() == content.get());
  }
}
