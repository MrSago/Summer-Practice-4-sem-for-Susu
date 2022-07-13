#include "edititemdialog.h"

#include "ui_edititemdialog.h"

EditItemDialog::EditItemDialog(QVector<QString>& items, QWidget* parent)
    : QDialog(parent), ui_(new Ui::EditItemDialog) {
  ui_->setupUi(this);
  connectButtons();
  setEditTexts(items);
}

EditItemDialog::~EditItemDialog() { delete ui_; }

QString EditItemDialog::getAuthor() { return ui_->authorLineEdit->text(); }

QString EditItemDialog::getTheme() { return ui_->themeLineEdit->text(); }

QString EditItemDialog::getPhrase() {
  return ui_->phraseTextEdit->toPlainText();
}

void EditItemDialog::connectButtons() {
  connect(ui_->acceptButton, &QAbstractButton::clicked, this,
          &EditItemDialog::accept);
  connect(ui_->cancelButton, &QAbstractButton::clicked, this,
          &EditItemDialog::reject);
}

void EditItemDialog::setEditTexts(QVector<QString>& items) {
  ui_->authorLineEdit->setText(items[1]);
  ui_->themeLineEdit->setText(items[2]);
  ui_->phraseTextEdit->setText(items[3]);
}
