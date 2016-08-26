// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef DEEPIN_INSTALLER_REBORN_UI_FRAMES_INNER_EDIT_PARTITION_FRAME_H
#define DEEPIN_INSTALLER_REBORN_UI_FRAMES_INNER_EDIT_PARTITION_FRAME_H

#include <QFrame>
#include <ui/widgets/nav_button.h>
#include <ui/widgets/table_combo_box.h>

namespace ui {

class NavButton;
class TableComboBox;

class EditPartitionFrame : public QFrame {
  Q_OBJECT

 public:
  explicit EditPartitionFrame(QWidget* parent = nullptr);

  void setPartition();

 signals:
  void canceled();
  void confirmed();

 private:
  void initConnections();
  void initUI();

  TableComboBox* fs_box_ = nullptr;
  TableComboBox* mount_point_box_ = nullptr;
  NavButton* cancel_button_ = nullptr;
  NavButton* ok_button_ = nullptr;
};

}  // namespace ui

#endif  // DEEPIN_INSTALLER_REBORN_UI_FRAMES_INNER_EDIT_PARTITION_FRAME_H