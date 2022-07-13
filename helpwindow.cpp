#include "helpwindow.h"

#include "ui_helpwindow.h"

HelpWindow::HelpWindow(QWidget* parent)
    : QDialog(parent), ui_(new Ui::HelpWindow) {
  ui_->setupUi(this);
  connect(ui_->okButton, &QAbstractButton::clicked, this, &HelpWindow::accept);
}

HelpWindow::~HelpWindow() { delete ui_; }
