#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class ServerChangeDifficulty : public Packet {
   private:
    Difficulty difficulty;
    bool locked;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    ServerChangeDifficulty(Difficulty difficulty, bool locked) : difficulty(difficulty), locked(locked) {
    }

    ~ServerChangeDifficulty() override = default;

    ServerChangeDifficulty(const ProtocolVersion* version, ByteBuffer* buffer) {
      difficulty = (Difficulty) buffer->ReadByte();
      if (version >= &ProtocolVersion::MINECRAFT_1_14) {
        locked = buffer->ReadBoolean();
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByte(difficulty);
      if (version >= &ProtocolVersion::MINECRAFT_1_14) {
        buffer->WriteBoolean(locked);
      }
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] Difficulty GetDifficulty() const {
      return difficulty;
    }

    [[nodiscard]] bool IsLocked() const {
      return locked;
    }
  };
}
