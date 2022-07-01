#include "edititemdialog.h"

#include "ui_edititemdialog.h"

EditItemDialog::EditItemDialog(QVector<QString>& items, QWidget* parent)
    : QDialog(parent), ui(new Ui::EditItemDialog) {
  ui->setupUi(this);

  connect(ui->acceptButton, &QAbstractButton::clicked, this,
          &EditItemDialog::accept);
  connect(ui->cancelButton, &QAbstractButton::clicked, this,
          &EditItemDialog::reject);

  ui->authorLineEdit->setText(items[0]);
  ui->themeLineEdit->setText(items[1]);
  ui->phraseTextEdit->setText(items[2]);
}

EditItemDialog::~EditItemDialog() { delete ui; }

QString EditItemDialog::getAuthor() { return ui->authorLineEdit->text(); }

QString EditItemDialog::getTheme() { return ui->themeLineEdit->text(); }

QString EditItemDialog::getPhrase() {
  return ui->phraseTextEdit->toPlainText();
}
