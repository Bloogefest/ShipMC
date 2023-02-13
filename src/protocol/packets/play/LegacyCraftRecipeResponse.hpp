#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>
#include <utility>

namespace Ship {

  class LegacyCraftRecipeResponse : public Packet {
   private:
    uint8_t windowId;
    uint32_t recipe;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    LegacyCraftRecipeResponse(uint8_t windowId, uint32_t recipe) : windowId(windowId), recipe(recipe) {
    }

    ~LegacyCraftRecipeResponse() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      windowId = buffer->ReadByte();
      recipe = buffer->ReadVarInt();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteByte(windowId);
      buffer->WriteVarInt(recipe);
    }

    uint32_t Size(const ProtocolVersion* version) override {
      return ByteBuffer::BYTE_SIZE + ByteBuffer::VarIntBytes(recipe);
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint8_t GetWindowId() const {
      return windowId;
    }

    [[nodiscard]] uint32_t GetRecipe() const {
      return recipe;
    }
  };
}