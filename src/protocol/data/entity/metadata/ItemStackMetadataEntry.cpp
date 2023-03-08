#include "Metadata.hpp"

namespace Ship {

  ItemStackMetadataEntry::ItemStackMetadataEntry(const ItemStack& value) : value(value) {
  }

  void ItemStackMetadataEntry::Write(const ProtocolVersion* version, ByteBuffer* buffer) const {
    value.Write(version, buffer);
  }

  ItemStackMetadataEntry::ItemStackMetadataEntry(const ProtocolVersion* version, ByteBuffer* buffer) {
    value = ItemStack(version, buffer);
  }

  MetadataEntryType ItemStackMetadataEntry::GetType() const {
    return MetadataEntryType::ITEM_STACK;
  }

  uint32_t ItemStackMetadataEntry::GetOrdinal() const {
    return ORDINAL;
  }

  ItemStack ItemStackMetadataEntry::GetValue() const {
    return value;
  }

  void ItemStackMetadataEntry::SetValue(const ItemStack& newValue) {
    value = newValue;
  }
}