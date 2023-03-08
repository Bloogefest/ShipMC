#include "../../../ProtocolUtils.hpp"
#include "Metadata.hpp"

namespace Ship {

  NBTMetadataEntry::NBTMetadataEntry(NBT* value) : value(value) {
  }

  NBTMetadataEntry::NBTMetadataEntry(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = ProtocolUtils::ReadNBT(buffer);
  }

  NBTMetadataEntry::~NBTMetadataEntry() {
    delete value;
  }

  void NBTMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    if (value) {
      ProtocolUtils::WriteNBT(buffer, value);
    } else {
      buffer->WriteByte(0);
    }
  }

  MetadataEntryType NBTMetadataEntry::GetType() const {
    return MetadataEntryType::NBT;
  }

  uint32_t NBTMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  NBT* NBTMetadataEntry::GetValue() const {
    return value;
  }

  void NBTMetadataEntry::SetValue(NBT* newValue) {
    delete value;
    value = newValue;
  }
}