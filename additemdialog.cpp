#include "additemdialog.h"

#include "ui_additemdialog.h"

AddItemDialog::AddItemDialog(QWidget *parent)
    : QDialog(parent), ui_(new Ui::AddItemDialog) {
  ui_->setupUi(this);
  connectButtons();
}

AddItemDialog::~AddItemDialog() { delete ui_; }

QString AddItemDialog::getAuthor() { return ui_->authorLineEdit->text(); }

QString AddItemDialog::getTheme() { return ui_->themeLineEdit->text(); }

QString AddItemDialog::getPhrase() {
  return ui_->phraseTextEdit->toPlainText();
}

void AddItemDialog::connectButtons() {
  connect(ui_->acceptButton, &QAbstractButton::clicked, this,
          &AddItemDialog::accept);
  connect(ui_->cancelButton, &QAbstractButton::clicked, this,
          &AddItemDialog::reject);
}
