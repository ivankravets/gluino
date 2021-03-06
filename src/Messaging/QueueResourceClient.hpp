// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_QUEUE_RESOURCE_CLIENT_HPP
#define MESSAGING_QUEUE_RESOURCE_CLIENT_HPP

#include "QueueClient.hpp"
#include "ResourceResponseHandler.hpp"
#include "ResourceEventHandler.hpp"
#include "Core/Memory.hpp"
#include "Core/Status.hpp"

#include <vector>

namespace Messaging {

struct IMessageQueue;

class QueueResourceClient : public QueueClient {
  public:
    QueueResourceClient(const std::string& clientId, const std::string& resource, IMessageQueue& messageQueue);
    virtual ~QueueResourceClient() override;

    QueueResourceClient(const QueueResourceClient&) = delete;
    QueueResourceClient& operator=(const QueueResourceClient&) = delete;

    std::string getClientId() const override { return clientId; }

    std::tuple<Core::Status, std::string> sendRequest(RequestType requestType);
    std::tuple<Core::Status, std::string> sendRequest(RequestType requestType, std::unique_ptr<Core::IEntity> content);

    void onResponse(const Response& response) const override;
    void onEvent(const Event& event) const override;

    template<typename T>
    void addOnResponse(RequestType requestType, T onResponse) {
      responseHandlers.push_back(std::make_unique<ResourceResponseHandlerImpl<T>>(requestType, onResponse));
    }

    template<typename T>
    void addOnEvent(EventType eventType, T onEvent) {
      eventHandlers.push_back(std::make_unique<ResourceEventHandlerImpl<T>>(eventType, onEvent));
    }

  private:
    const std::string clientId;
    const std::string resource;
    IMessageQueue& messageQueue;
    std::vector<std::unique_ptr<ResourceResponseHandler>> responseHandlers;
    std::vector<std::unique_ptr<ResourceEventHandler>> eventHandlers;
};

}

#endif /* end of include guard: MESSAGING_QUEUE_RESOURCE_CLIENT_HPP */
