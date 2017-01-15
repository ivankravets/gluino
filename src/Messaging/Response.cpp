#include "Response.hpp"

using namespace Messaging;

Response::Response(
  std::string sender,
  std::string receiver,
  ActionType actionType,
  std::string resource,
  IEntity::Shared content
) :
  sender(sender),
  receiver(receiver),
  actionType(actionType),
  resource(resource),
  content(content) {
}
