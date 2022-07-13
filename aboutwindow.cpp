#include "aboutwindow.h"

#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget* parent)
    : QDialog(parent), ui_(new Ui::AboutWindow) {
  ui_->setupUi(this);
  connect(ui_->okButton, &QAbstractButton::clicked, this, &AboutWindow::accept);
}

AboutWindow::~AboutWindow() { delete ui_; }
