#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class EndCombatEvent : public Packet {
   private:
    uint32_t duration;
    uint32_t entityId;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    EndCombatEvent(uint32_t duration, uint32_t entityId) : duration(duration), entityId(entityId) {
    }

    ~EndCombatEvent() override = default;

    explicit EndCombatEvent(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      duration = buffer->ReadVarInt();
      entityId = buffer->ReadInt();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(duration);
      buffer->WriteInt(entityId);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetDuration() const {
      return duration;
    }

    [[nodiscard]] uint32_t GetEntityId() const {
      return entityId;
    }
  };
}
