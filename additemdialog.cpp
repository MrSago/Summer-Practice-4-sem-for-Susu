#include "additemdialog.h"

#include "ui_additemdialog.h"

AddItemDialog::AddItemDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddItemDialog) {
  ui->setupUi(this);

  connect(ui->acceptButton, &QAbstractButton::clicked, this,
          &AddItemDialog::accept);
  connect(ui->cancelButton, &QAbstractButton::clicked, this,
          &AddItemDialog::reject);
}

AddItemDialog::~AddItemDialog() { delete ui; }

QString AddItemDialog::getAuthor() { return ui->authorLineEdit->text(); }

QString AddItemDialog::getTheme() { return ui->themeLineEdit->text(); }

QString AddItemDialog::getPhrase() { return ui->phraseTextEdit->toPlainText(); }
