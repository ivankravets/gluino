// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_I_SERIALIZER_HPP
#define SERIALIZATION_I_SERIALIZER_HPP

#include "Core/IEntity.hpp"
#include "ISerializationContext.hpp"
#include "IDeserializationContext.hpp"

#include "memory"

namespace Serialization {

struct ISerializer {
  TYPE_PTRS_ABSTRACT(ISerializer)
  virtual ~ISerializer() = default;

  virtual const std::string& getTypeId() const = 0;

  virtual Core::Status serialize(
    const Core::IEntity& entity,
    ISerializationContext& context) const = 0;

  virtual Core::Status deserialize(
    std::unique_ptr<Core::IEntity>& entity,
    IDeserializationContext& context) const = 0;
};

}

#endif /* end of include guard: SERIALIZATION_I_SERIALIZER_HPP */
