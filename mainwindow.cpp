#include "mainwindow.h"

#include <QClipboard>
#include <QMessageBox>
#include <QStatusBar>

#include "additemdialog.h"
#include "edititemdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  connectButtons();
  setupTable();
  statusBar()->showMessage("Готов");
}

MainWindow::~MainWindow() {
  delete ui_;
  delete tableData_;
}

void MainWindow::onAddButtonClicked() {
  AddItemDialog dialog(this);
  dialog.exec();

  if (dialog.result() == QDialog::Accepted) {
    QVector<QString> data = {dialog.getAuthor(), dialog.getTheme(),
                             dialog.getPhrase()};
    tableData_->addRow(data);
  }
  statusBar()->showMessage("Запись успешно добавлена в таблицу");
}

void MainWindow::onRemoveButtonClicked() {
  QModelIndexList selected_rows =
      ui_->mainTableView->selectionModel()->selectedRows();
  if (selected_rows.size() != 1) {
    buttonMessageBox("Выберите строку для удаления");
    return;
  }

  int row = selected_rows.first().row();
  tableData_->removeRow(row);
  statusBar()->showMessage("Запись успешно удалена");
}

void MainWindow::onEditButtonClicked() {
  QModelIndexList selected_rows =
      ui_->mainTableView->selectionModel()->selectedRows();
  if (selected_rows.size() != 1) {
    buttonMessageBox("Выберите строку для редактирования");
    return;
  }

  int row = selected_rows.first().row();
  QVector<QString> data = tableData_->getRowData(row);
  EditItemDialog dialog(data, this);
  dialog.exec();

  if (dialog.result() == QDialog::Accepted) {
    QVector<QString> data = {dialog.getAuthor(), dialog.getTheme(),
                             dialog.getPhrase()};
    tableData_->editRow(data, row);
  }
  statusBar()->showMessage("Запись в таблице успешно изменена");
}

void MainWindow::onCopyButtonClicked() {
  QModelIndexList selected_rows =
      ui_->mainTableView->selectionModel()->selectedRows();
  if (selected_rows.size() != 1) {
    buttonMessageBox("Выберите строку для копирования");
    return;
  }

  int row = selected_rows.first().row();
  QVector<QString> data = tableData_->getRowData(row);
  QString result = "";
  for (auto& it : data) {
    result += it + '\t';
  }

  QApplication::clipboard()->setText(result);
  statusBar()->showMessage("Строка скопирована");
}

void MainWindow::onSearchButtonClicked() {
  int search_index = ui_->criterionComboBox->currentIndex();
  QString search_string = ui_->searchLineEdit->text();
  if (search_string.isNull() || search_string.isEmpty()) {
    return;
  }
  qDebug("%d : %s\n", search_index, search_string.toStdString().c_str());
}

void MainWindow::connectButtons() {
  connect(ui_->addButton, &QAbstractButton::clicked, this,
          &MainWindow::onAddButtonClicked);
  connect(ui_->removeButton, &QAbstractButton::clicked, this,
          &MainWindow::onRemoveButtonClicked);
  connect(ui_->editButton, &QAbstractButton::clicked, this,
          &MainWindow::onEditButtonClicked);
  connect(ui_->copyButton, &QAbstractButton::clicked, this,
          &MainWindow::onCopyButtonClicked);
  connect(ui_->searchButton, &QAbstractButton::clicked, this,
          &MainWindow::onSearchButtonClicked);
}

void MainWindow::setupTable() {
  tableData_ = new TableData(QVector<QString>{"Автор", "Тема", "Фраза"});
  tableData_->setSearchCriterionColumns(QVector<int>{0, 1});

  ui_->mainTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui_->mainTableView->verticalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui_->mainTableView->setModel(tableData_->getModel());
}

void MainWindow::buttonMessageBox(const QString& text) {
  QMessageBox msg_box;
  msg_box.setWindowTitle("Таблица");
  msg_box.setWindowIcon(windowIcon());
  msg_box.setIcon(QMessageBox::Information);
  msg_box.setText(text);
  msg_box.exec();
}
