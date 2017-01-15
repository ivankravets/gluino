// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_REQUEST_HPP
#define MESSAGING_REQUEST_HPP

#include "ActionType.hpp"
#include "Core/IEntity.hpp"

namespace Messaging {

/**
  The request message.
*/
class Request : public Core::IEntity {
  TYPE_INFO(Request, IEntity, "request")
  public:
    Request(
      std::string     sender,
      ActionType      actionType,
      std::string     resource,
      IEntity::Shared content
    );

    /**
      The request sender.
    */
    std::string getSender() const { return sender; };

    /**
      The resource action type (Create, Get, Update, Delete).
    */
    ActionType getActionType() const { return actionType; }

    /**
      The resource.
    */
    std::string getResource() const { return resource; }

    /**
      The request content.
    */
    const IEntity* getContent() const { return content.get(); };

  private:
    std::string     sender;
    ActionType      actionType;
    std::string     resource;
    IEntity::Shared content;
};

}

#endif /* end of include guard: MESSAGING_MESSAGE_HPP */
