#include "mainwindow.h"

#include <QStandardItemModel>

#include "./ui_mainwindow.h"
#include "additemdialog.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->mainTableView->setModel(tableData.getModel());
  ui->mainTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);

  //  connect(ui->addButton, &QAbstractButton::clicked, this,
  //          &MainWindow::onAddButtonClicked);
  //  ui->mainTableView->setColumnWidth(0, 100);
  //  ui->mainTableView->setColumnWidth(1, 200);
  //  ui->mainTableView->setColumnWidth(2, 500);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onAddButtonClicked() {
  AddItemDialog dialog(this);
  dialog.exec();

  if (dialog.result() == QDialog::Accepted) {
    qDebug("Author: %s", dialog.getAuthor().toStdString().c_str());
    qDebug("Theme: %s", dialog.getTheme().toStdString().c_str());
    qDebug("Phrase:\n%s", dialog.getPhrase().toStdString().c_str());
  }
}
