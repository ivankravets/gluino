#include "Event.hpp"

using namespace Messaging;

Event::Event(const EventType& eventType, const std::string& resource) :
  eventType(eventType), resource(resource) {
}

Event::Event(const EventType& eventType, const std::string& resource, std::unique_ptr<IEntity> content) :
  eventType(eventType), resource(resource), content(std::move(content)) {
}
