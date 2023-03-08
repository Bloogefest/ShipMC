#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class GameEvent : public Packet {
   private:
    uint8_t event;
    float value;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    GameEvent(uint8_t event, float value) : event(event), value(value) {
    }

    ~GameEvent() override = default;

    explicit GameEvent(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      event = buffer->ReadByte();
      value = buffer->ReadFloat();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByte(event);
      buffer->WriteFloat(value);
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint8_t GetEvent() const {
      return event;
    }

    [[nodiscard]] float GetValue() const {
      return value;
    }
  };
}
