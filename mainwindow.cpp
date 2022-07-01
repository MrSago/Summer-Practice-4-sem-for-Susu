#include "mainwindow.h"

#include <QClipboard>
#include <QStandardItemModel>

#include "./ui_mainwindow.h"
#include "additemdialog.h"
#include "edititemdialog.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->mainTableView->setModel(tableData.getModel());
  ui->mainTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);

  connect(ui->addButton, &QAbstractButton::clicked, this,
          &MainWindow::onAddButtonClicked);

  connect(ui->removeButton, &QAbstractButton::clicked, this,
          &MainWindow::onRemoveButtonClicked);

  connect(ui->editButton, &QAbstractButton::clicked, this,
          &MainWindow::onEditButtonClicked);

  connect(ui->copyButton, &QAbstractButton::clicked, this,
          &MainWindow::onCopyButtonClicked);

  //  ui->mainTableView->setColumnWidth(0, 100);
  //  ui->mainTableView->setColumnWidth(1, 200);
  //  ui->mainTableView->setColumnWidth(2, 500);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onAddButtonClicked() {
  AddItemDialog dialog(this);
  dialog.exec();

  if (dialog.result() == QDialog::Accepted) {
    QVector<QString> data = {dialog.getAuthor(), dialog.getTheme(),
                             dialog.getPhrase()};
    tableData.addRow(data);
  }
}

void MainWindow::onRemoveButtonClicked() {
  QModelIndexList selected_rows =
      ui->mainTableView->selectionModel()->selectedRows();
  if (selected_rows.size() == 1) {
    tableData.removeRow(selected_rows.first().row());
  }
}

void MainWindow::onEditButtonClicked() {
  QModelIndexList selected_rows =
      ui->mainTableView->selectionModel()->selectedRows();

  if (selected_rows.size() != 1) {
    return;
  }

  int row = selected_rows.first().row();
  QVector<QString> data = tableData.getRowData(row);

  EditItemDialog dialog(data, this);
  dialog.exec();

  if (dialog.result() == QDialog::Accepted) {
    QVector<QString> data = {dialog.getAuthor(), dialog.getTheme(),
                             dialog.getPhrase()};
    tableData.changeRow(data, row);
  }
}

void MainWindow::onCopyButtonClicked() {
  QModelIndexList selected_rows =
      ui->mainTableView->selectionModel()->selectedRows();

  if (selected_rows.size() != 1) {
    return;
  }

  int row = selected_rows.first().row();

  QVector<QString> data = tableData.getRowData(row);
  QString result = "";
  for (auto it : data) {
    result += it + " ";
  }

  QApplication::clipboard()->setText(result);
}
