// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef INSTALLER_UI_WIDGETS_FLAT_BUTTON_H
#define INSTALLER_UI_WIDGETS_FLAT_BUTTON_H

#include <QPushButton>

namespace installer {

// FlatButton only displays an icon, without any frame lines.
// It also changes cursor shape.
class FlatButton : public QPushButton {
  Q_OBJECT

 public:
  explicit FlatButton(QWidget* parent = nullptr);
  FlatButton(const QString& text, QWidget* parent = nullptr);

 protected:
  // Override these two event handlers to implements hover effect.
  void enterEvent(QEvent* event) override;
  void leaveEvent(QEvent* event) override;
};

}  // namespace installer

#endif  // INSTALLER_UI_WIDGETS_FLAT_BUTTON_H
