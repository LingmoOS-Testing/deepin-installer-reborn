// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "partman/device.h"

namespace installer {

Device::Device()
    : partitions(),
      model(),
      path(),
      length(-1),
      heads(-1),
      sectors(-1),
      cylinders(-1),
      cylsize(-1),
      disk_type(),
      sector_size(-1),
      max_prims(-1),
      read_only(true),
      table(PartitionTableType::Unknown) {
}

}  // namespace installer