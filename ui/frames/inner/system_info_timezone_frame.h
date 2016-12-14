// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef INSTALLER_UI_FRAMES_INNER_SYSTEM_INFO_TIMEZONE_FRAME_H
#define INSTALLER_UI_FRAMES_INNER_SYSTEM_INFO_TIMEZONE_FRAME_H

#include <QFrame>

namespace installer {

class CommentLabel;
class NavButton;
class TimezoneManager;
class TimezoneMap;
class TitleLabel;

// Displays a world map to let user select timezone.
class SystemInfoTimezoneFrame : public QFrame {
  Q_OBJECT

 public:
  explicit SystemInfoTimezoneFrame(QWidget* parent = nullptr);

 signals:
  // Emitted when back button is clicked.
  void finished();

  // Emitted when a new timezone is chosen.
  void timezoneUpdated(const QString& timezone);

 public slots:
  // Read default timezone and emit timezoneUpdated() signal.
  void readConf();

  // Validate timezone and write to conf file.
  void writeConf();

 protected:
  void changeEvent(QEvent* event) override;

 private:
  void initConnections();
  void initUI();

  QString timezone_;

  TimezoneManager* timezone_manager_ = nullptr;

  TitleLabel* title_label_ = nullptr;
  CommentLabel* comment_label_ = nullptr;
  TimezoneMap* timezone_map_ = nullptr;
  NavButton* back_button_ = nullptr;

  // Priority of timezone: User > Conf > Scan
  enum class TimezoneSource {
    NotSet,  // Timezone not set.
    User,  // Timezone is setup by user.
    Conf,  // Timezone is read from conf file
    Scan  // Timezone is updated based on geoip or regdomain
  };
  TimezoneSource timezone_source_;

 private slots:
  void onBackButtonClicked();

  // Update timezone after receiving signals from timezone manager.
  void onTimezoneManagerUpdated(const QString& timezone);

  // Update timezone after a new one has been chosen by user.
  void onTimezoneMapUpdated(const QString& timezone);
};

}  // namespace installer

#endif  // INSTALLER_UI_FRAMES_INNER_SYSTEM_INFO_TIMEZONE_FRAME_H
