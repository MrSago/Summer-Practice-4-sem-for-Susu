#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->mainTableView->model()->setHeaderData(1, Qt::Horizontal, "Hello",
                                            Qt::DisplayRole);
}

MainWindow::~MainWindow() { delete ui; }
