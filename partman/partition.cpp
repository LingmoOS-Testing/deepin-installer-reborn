// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "partman/partition.h"

namespace installer {

Partition::Partition()
    : device_path(),
      path(),
      uuid(),
      label(),
      part_label(),
      partition_number(-1),
      type(PartitionType::Unallocated),
      status(PartitionStatus::Real),
      fs(FsType::Empty),
      os(OsType::Empty),
      sector_size(-1),
      length(-1),
      freespace(-1),
      sector_start(-1),
      sector_end(-1),
      sectors_unallocated_preceding(0),
      sectors_unallocated_succeeding(0),
      mount_point() {
}

Partition::~Partition() {

}

bool Partition::operator==(const Partition& other) const {
  return (this->device_path == other.device_path &&
          this->partition_number == other.partition_number &&
          this->sector_start == other.sector_start &&
          type == other.type);
}

qint64 Partition::getByteLength() const {
  const qint64 sectors = getSectorLength();
  if (sectors >= 0) {
    return sectors * sector_size;
  } else {
    return -1;
  }
}

qint64 Partition::getSector() const {
  return sector_start + (sector_end - sector_start) / 2;
}

qint64 Partition::getSectorLength() const {
  if (sector_start >= 0 && sector_end >= 0) {
    return sector_end - sector_start + 1;
  } else {
    return -1;
  }
}

}  // namespace installer