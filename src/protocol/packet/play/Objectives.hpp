#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>

namespace Ship {

  class Objectives : public Packet {
   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();
    ~Objectives() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }
  };
}
