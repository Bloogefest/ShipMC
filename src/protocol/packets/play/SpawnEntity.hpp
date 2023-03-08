#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>

namespace Ship {

  class SpawnEntity : public Packet {
   private:
    uint32_t entityId;
    UUID entityUuid;
    uint32_t type;
    double x;
    double y;
    double z;
    float pitch;
    float yaw;
    float headYaw;
    uint32_t data;
    float velocityX;
    float velocityY;
    float velocityZ;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    SpawnEntity(uint32_t entityId, const UUID& entityUuid, uint32_t type, double x, double y, double z, float pitch, float yaw, float headYaw,
      uint32_t data, float velocityX, float velocityY, float velocityZ)
      : entityId(entityId), entityUuid(entityUuid), type(type), x(x), y(y), z(z), pitch(pitch), yaw(yaw), headYaw(headYaw), data(data),
        velocityX(velocityX), velocityY(velocityY), velocityZ(velocityZ) {
    }

    ~SpawnEntity() override = default;

    SpawnEntity(const ProtocolVersion* version, ByteBuffer* buffer) {
      entityId = buffer->ReadVarInt();
      entityUuid = buffer->ReadUUID();
      if (version >= &ProtocolVersion::MINECRAFT_1_14) {
        type = buffer->ReadVarInt();
      } else {
        type = buffer->ReadByte();
      }
      x = buffer->ReadDouble();
      y = buffer->ReadDouble();
      z = buffer->ReadDouble();
      pitch = buffer->ReadAngle();
      yaw = buffer->ReadAngle();
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {
        headYaw = buffer->ReadAngle();
        data = buffer->ReadVarInt();
      } else {
        data = buffer->ReadInt();
      }
      velocityX = (float) buffer->ReadShort() / 8000.0F;
      velocityY = (float) buffer->ReadShort() / 8000.0F;
      velocityZ = (float) buffer->ReadShort() / 8000.0F;
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(entityId);
      buffer->WriteUUID(entityUuid);
      if (version >= &ProtocolVersion::MINECRAFT_1_14) {
        buffer->WriteVarInt(type);
      } else {
        buffer->WriteByte(type);
      }
      buffer->WriteDouble(x);
      buffer->WriteDouble(y);
      buffer->WriteDouble(z);
      buffer->WriteAngle(pitch);
      buffer->WriteAngle(yaw);
      if (version >= &ProtocolVersion::MINECRAFT_1_19) {
        buffer->WriteAngle(headYaw);
        buffer->WriteVarInt(data);
      } else {
        buffer->WriteInt(data);
      }
      buffer->WriteShort((uint16_t) (velocityX * 8000.0F));
      buffer->WriteShort((uint16_t) (velocityY * 8000.0F));
      buffer->WriteShort((uint16_t) (velocityZ * 8000.0F));
    }

    uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetEntityId() const {
      return entityId;
    }

    [[nodiscard]] const UUID& GetEntityUuid() const {
      return entityUuid;
    }

    [[nodiscard]] uint32_t getType() const {
      return type;
    }

    [[nodiscard]] double GetX() const {
      return x;
    }

    [[nodiscard]] double GetY() const {
      return y;
    }

    [[nodiscard]] double GetZ() const {
      return z;
    }

    [[nodiscard]] float GetPitch() const {
      return pitch;
    }

    [[nodiscard]] float GetYaw() const {
      return yaw;
    }

    [[nodiscard]] float GetHeadYaw() const {
      return headYaw;
    }

    [[nodiscard]] uint32_t GetData() const {
      return data;
    }

    [[nodiscard]] float GetVelocityX() const {
      return velocityX;
    }

    [[nodiscard]] float GetVelocityY() const {
      return velocityY;
    }

    [[nodiscard]] float GetVelocityZ() const {
      return velocityZ;
    }
  };
}
