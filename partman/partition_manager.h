// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef DEEPIN_INSTALLER_REBORN_PARTMAN_PARTITION_MANAGER_H
#define DEEPIN_INSTALLER_REBORN_PARTMAN_PARTITION_MANAGER_H

#include <QList>
#include <QObject>

#include "partman/device.h"

namespace partman {

class Operation;

class PartitionManager : public QObject {
  Q_OBJECT

 public:
  explicit PartitionManager(QObject* parent = nullptr);
  ~PartitionManager();

  // Update operation list.
  // This method is called in UI thread.
  void setOperations(const QList<Operation*>& operations) {
    operations_ = operations;
  }

 signals:
  void refreshDevices();
  void devicesRefreshed(const DeviceList& devices);

  // Run oem/auto-part.sh script.
  void autoPart();
  // Emitted after oem/auto-part.sh script is executed and exited.
  // |ok| is true if that script exited 0.
  void autoPartDone(bool ok);

  void manualPart();
  void manualPartDone(bool ok);

 private:
  void initConnections();

  QList<Operation*> operations_;

 private slots:
  void doRefreshDevices();
  void doAutoPart();
  void doManualPart();
};

}  // namespace partman

#endif  // DEEPIN_INSTALLER_REBORN_PARTMAN_PARTITION_MANAGER_H
