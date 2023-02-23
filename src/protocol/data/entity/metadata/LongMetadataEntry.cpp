#include "Metadata.hpp"

namespace Ship {

  LongMetadataEntry::LongMetadataEntry(uint64_t value) : value(value) {
  }

  void LongMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) {
    buffer->WriteLong(value);
  }

  void LongMetadataEntry::Read(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = buffer->ReadLong();
  }

  MetadataEntryType LongMetadataEntry::GetType() const {
    return MetadataEntryType::LONG;
  }

  uint32_t LongMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  uint64_t LongMetadataEntry::GetValue() const {
    return value;
  }

  void LongMetadataEntry::SetValue(uint64_t newValue) {
    value = newValue;
  }
}