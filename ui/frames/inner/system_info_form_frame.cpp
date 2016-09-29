// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "ui/frames/inner/system_info_form_frame.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "service/settings_manager.h"
#include "service/settings_name.h"
#include "sysinfo/validate_hostname.h"
#include "sysinfo/validate_username.h"
#include "ui/frames/consts.h"
#include "ui/widgets/avatar_button.h"
#include "ui/widgets/comment_label.h"
#include "ui/widgets/icon_button.h"
#include "ui/widgets/line_edit.h"
#include "ui/widgets/nav_button.h"
#include "ui/widgets/title_label.h"

namespace installer {

SystemInfoFormFrame::SystemInfoFormFrame(QWidget* parent)
    : QFrame(parent),
      is_username_validated_(false),
      is_hostname_validated_(false),
      is_password_validated_(false),
      is_password2_validated_(false) {
  this->setObjectName(QStringLiteral("system_info_form_frame"));

  this->initUI();
  this->initConnections();
}

void SystemInfoFormFrame::updateAvatar(const QString& avatar) {
  avatar_button_->updateIcon(avatar);
}

void SystemInfoFormFrame::updateTimezone(const QString& timezone) {
  timezone_button_->setText(timezone);
}

void SystemInfoFormFrame::initConnections() {
  connect(avatar_button_, &QPushButton::clicked,
          this, &SystemInfoFormFrame::avatarClicked);
  connect(next_button_, &QPushButton::clicked,
          this, &SystemInfoFormFrame::onNextButtonClicked);
  connect(timezone_button_, &QPushButton::clicked,
          this, &SystemInfoFormFrame::timezoneClicked);

  connect(username_edit_, &QLineEdit::textChanged,
          this, &SystemInfoFormFrame::onUsernameChanged);
  connect(hostname_edit_, &QLineEdit::textChanged,
          this, &SystemInfoFormFrame::onHostnameChanged);
  connect(password_edit_, &QLineEdit::textChanged,
          this, &SystemInfoFormFrame::onPasswordChanged);
  connect(password2_edit_, &QLineEdit::textChanged,
          this, &SystemInfoFormFrame::onPassword2Changed);
}

void SystemInfoFormFrame::initUI() {
  timezone_button_ = new IconButton(QStringLiteral(":/images/timezone.png"),
                                    QStringLiteral(":/images/timezone.png"),
                                    QStringLiteral(":/images/timezone.png"),
                                    128, 32, nullptr);
  QHBoxLayout* timezone_layout = new QHBoxLayout();
  timezone_layout->setAlignment(Qt::AlignLeft);
  timezone_layout->addWidget(timezone_button_);

  TitleLabel* title_label = new TitleLabel(tr("Create User Account"));
  QHBoxLayout* title_layout = new QHBoxLayout();
  title_layout->addWidget(title_label);

  CommentLabel* comment_label =
   new CommentLabel(tr("Input username and password"));
  QHBoxLayout* comment_layout = new QHBoxLayout();
  comment_layout->addWidget(comment_label);

  avatar_button_ = new AvatarButton();
  QHBoxLayout* avatar_layout = new QHBoxLayout();
  avatar_layout->addWidget(avatar_button_);

  username_edit_ = new LineEdit(QStringLiteral(":/images/username.png"));
  username_edit_->setPlaceholderText(tr("Username"));
  hostname_edit_ = new LineEdit(QStringLiteral(":/images/hostname.png"));
  hostname_edit_->setPlaceholderText(tr("Computer name"));
  password_edit_ = new LineEdit(QStringLiteral(":/images/password.png"));
  password_edit_->setPlaceholderText(tr("Password"));
  password2_edit_ = new LineEdit(QStringLiteral(":/images/password.png"));
  password2_edit_->setPlaceholderText(tr("Reenter password"));

  QVBoxLayout* form_layout = new QVBoxLayout();
  form_layout->setContentsMargins(0, 0, 0, 0);
  form_layout->setMargin(0);
  form_layout->setSpacing(20);
  form_layout->addWidget(username_edit_);
  form_layout->addWidget(hostname_edit_);
  form_layout->addWidget(password_edit_);
  form_layout->addWidget(password2_edit_);

  QFrame* form_wrapper = new QFrame();
  form_wrapper->setFixedWidth(400);
  form_wrapper->setLayout(form_layout);
  QHBoxLayout* form_wrapper_layout = new QHBoxLayout();
  form_wrapper_layout->setContentsMargins(0, 0, 0, 0);
  form_wrapper_layout->setSpacing(0);
  form_wrapper_layout->addStretch();
  form_wrapper_layout->addWidget(form_wrapper);
  form_wrapper_layout->addStretch();

  next_button_ = new NavButton(tr("Next"));
  QHBoxLayout* next_layout = new QHBoxLayout();
  next_layout->addWidget(next_button_);

  QVBoxLayout* layout = new QVBoxLayout();
  layout->setSpacing(kMainLayoutSpacing);
  layout->addLayout(timezone_layout);
  layout->addStretch(1);
  layout->addLayout(title_layout);
  layout->addLayout(comment_layout);
  layout->addStretch(1);
  layout->addLayout(avatar_layout);
  layout->addStretch(1);
  layout->addLayout(form_wrapper_layout);
  layout->addStretch(3);
  layout->addLayout(next_layout);

  this->setLayout(layout);
}

void SystemInfoFormFrame::validateUsername(bool empty_ok) {
  const ValidateUsernameState state = ValidateUsername(username_edit_->text());
  switch (state) {
    case ValidateUsernameState::AlreadyUsedError: {
      username_edit_->setToolTip(tr("Username is already in use"));
      break;
    }

    case ValidateUsernameState::EmptyError: {
      if (!empty_ok) {
        username_edit_->setToolTip(tr("Username is empty!"));
      }
      break;
    }

    case ValidateUsernameState::FirstCharError: {
      username_edit_->setToolTip("First character is invalid");
      break;
    }

    case ValidateUsernameState::InvalidCharError: {
      username_edit_->setToolTip(tr("Invalid character!"));
      break;
    }

    case ValidateUsernameState::Ok: {
      username_edit_->setToolTip("");
      break;
    }

    case ValidateUsernameState::TooLongError: {
      username_edit_->setToolTip(tr("User name has too many characters"));
      break;
    }
  }

  is_username_validated_ = (state == ValidateUsernameState::Ok);
}

void SystemInfoFormFrame::validateHostname(bool empty_ok) {
  if (empty_ok) {
    is_hostname_validated_ = ValidateHostnameTemp(hostname_edit_->text());
  } else {
    is_hostname_validated_ = ValidateHostname(hostname_edit_->text());
  }
  if (!is_hostname_validated_) {
    hostname_edit_->setToolTip(tr("Invalid hostname!"));
  }
}

void SystemInfoFormFrame::validatePassword(bool empty_ok) {
  Q_UNUSED(empty_ok);
  is_password_validated_ = true;
}

void SystemInfoFormFrame::validatePassword2(bool empty_ok) {
  Q_UNUSED(empty_ok);
  is_password2_validated_ = true;
}

void SystemInfoFormFrame::onNextButtonClicked() {
  if (is_username_validated_ && is_hostname_validated_ &&
      is_password_validated_ && is_password2_validated_) {
    WriteUsername(username_edit_->text());
    WriteHostname(hostname_edit_->text());
    WritePassword(password_edit_->text());

    emit this->finished();
  } else {
    if (!is_username_validated_) {
      validateUsername(false);
    }

    if (!is_hostname_validated_) {
      validateHostname(false);
    }

    if (!is_password_validated_) {
      validatePassword(false);
    }
  }
}

void SystemInfoFormFrame::onUsernameChanged() {
  validateUsername(true);
}

void SystemInfoFormFrame::onHostnameChanged() {
  validateHostname(true);
}

void SystemInfoFormFrame::onPasswordChanged() {
  validatePassword(true);
}

void SystemInfoFormFrame::onPassword2Changed() {
  validatePassword2(true);
}

}  // namespace installer
