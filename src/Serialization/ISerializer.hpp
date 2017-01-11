// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_I_SERIALIZER_HPP
#define SERIALIZATION_I_SERIALIZER_HPP

#include "Core/IEntity.hpp"
#include "ISerializationContext.hpp"

#include "memory"

namespace Serialization {

class ISerializer {
  public:
    virtual ~ISerializer();

    virtual std::string getTypeId() const = 0;

    virtual Core::StatusResult::Unique serialize(
      const Core::IEntity& entity,
      ISerializationContext& context) const = 0;

    virtual Core::StatusResult::Unique deserialize(
      Core::IEntity::Unique& entity,
      ISerializationContext& context) const = 0;
};

}

#endif /* end of include guard: SERIALIZATION_I_SERIALIZER_HPP */