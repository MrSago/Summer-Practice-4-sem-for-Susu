#include "mainwindow.h"

#include <QClipboard>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>

#include "aboutwindow.h"
#include "additemdialog.h"
#include "edititemdialog.h"
#include "helpwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  connectActions();
  setupTable();
  initCompleter();
  statusBar()->showMessage("Готов");
}

MainWindow::~MainWindow() {
  delete ui_;
  delete tableData_;
  delete compl_;
}

void MainWindow::onRefreshButtonClicked() {
  QAbstractItemModel* ui_model = ui_->mainTableView->model();
  if (ui_model != tableData_->getModel() && ui_model != nullptr) {
    delete ui_model;
  }
  ui_->mainTableView->setModel(tableData_->getModel());
  ui_->criterionComboBox->setCurrentIndex(0);
  ui_->searchLineEdit->clear();
  statusBar()->showMessage("Таблица обновлена");
}

void MainWindow::onAddButtonClicked() {
  AddItemDialog dialog(this);
  dialog.exec();

  if (dialog.result() == QDialog::Accepted) {
    QVector<QString> data = {dialog.getAuthor(), dialog.getTheme(),
                             dialog.getPhrase()};
    tableData_->addRow(data);
    onSearchButtonClicked();
    statusBar()->showMessage("Запись успешно добавлена в таблицу");
  }
}

void MainWindow::onRemoveButtonClicked() {
  QModelIndexList selected_rows =
      ui_->mainTableView->selectionModel()->selectedRows();
  if (selected_rows.size() != 1) {
    buttonMessageBox("Выберите строку для удаления");
    return;
  }

  int id = selected_rows.first().data().toInt();
  tableData_->removeRow(id);
  onSearchButtonClicked();
  statusBar()->showMessage("Запись успешно удалена");
}

void MainWindow::onEditButtonClicked() {
  QModelIndexList selected_rows =
      ui_->mainTableView->selectionModel()->selectedRows();
  if (selected_rows.size() != 1) {
    buttonMessageBox("Выберите строку для редактирования");
    return;
  }

  int id = selected_rows.first().data().toInt();
  QVector<QString> data = tableData_->getRowData(id);
  EditItemDialog dialog(data, this);
  dialog.exec();

  if (dialog.result() == QDialog::Accepted) {
    QVector<QString> data = {dialog.getAuthor(), dialog.getTheme(),
                             dialog.getPhrase()};
    tableData_->editRow(data, id);
    onSearchButtonClicked();
    statusBar()->showMessage("Запись в таблице успешно изменена");
  }
}

void MainWindow::onCopyButtonClicked() {
  QModelIndexList selected_rows =
      ui_->mainTableView->selectionModel()->selectedRows();
  if (selected_rows.size() != 1) {
    buttonMessageBox("Выберите строку для копирования");
    return;
  }

  int id = selected_rows.first().data().toInt();
  QVector<QString> data = tableData_->getRowData(id);
  QString result = data[1];
  for (int i = 2; i < data.size(); ++i) {
    result += '\t' + data[i];
  }

  QApplication::clipboard()->setText(result);
  statusBar()->showMessage("Строка скопирована");
}

void MainWindow::onClearButtonClicked() {
  QAbstractItemModel* model = tableData_->clearModel();
  if (model) {
    QAbstractItemModel* ui_model = ui_->mainTableView->model();
    if (ui_model != nullptr) {
      delete ui_model;
    }
    ui_->mainTableView->setModel(model);
    statusBar()->showMessage("Таблица успешно очищена");
  } else {
    statusBar()->showMessage("Ошибка очистки таблицы");
  }
}

void MainWindow::onSearchButtonClicked() {
  QAbstractItemModel* ui_model = ui_->mainTableView->model();
  if (ui_model != tableData_->getModel() && ui_model != nullptr) {
    delete ui_model;
  }

  QString criterion = ui_->criterionComboBox->currentText();
  QString search_string = ui_->searchLineEdit->text();
  if (search_string.isNull() || search_string.isEmpty()) {
    ui_->mainTableView->setModel(tableData_->getModel());
    return;
  }

  QAbstractItemModel* model = tableData_->search(criterion, search_string);
  ui_->mainTableView->setModel(model);
}

void MainWindow::onSaveFileClicked() {
  QString path = QFileDialog::getSaveFileName(this, "Сохранить файл", "",
                                              "Фразы (*.json)");
  if (path.isNull() || path.isEmpty()) {
    return;
  }

  if (tableData_->saveToJson(path)) {
    statusBar()->showMessage("Файл успешно сохранен");
  } else {
    statusBar()->showMessage("Ошибка сохранения файла");
  }
}

void MainWindow::onLoadFileClicked() {
  QString path = QFileDialog::getOpenFileName(this, "Загрузить файл", "",
                                              "Фразы (*.json)");
  if (path.isNull() || path.isEmpty()) {
    return;
  }

  QAbstractItemModel* model = tableData_->loadFromJson(path);
  if (model) {
    ui_->mainTableView->setModel(model);
    compl_->setModel(model);
    statusBar()->showMessage("Файл успешно загружен");
  } else {
    statusBar()->showMessage("Ошибка загрузки файла");
  }
}

void MainWindow::onHelpActionClicked() {
  HelpWindow wnd(this);
  wnd.exec();
}

void MainWindow::onAboutActionClicked() {
  AboutWindow wnd(this);
  wnd.exec();
}

void MainWindow::onCriterionComboBoxActivated(int index) {
  compl_->setCompletionColumn(index + 1);
}

void MainWindow::connectActions() {
  connect(ui_->refreshButton, &QAbstractButton::clicked, this,
          &MainWindow::onRefreshButtonClicked);
  connect(ui_->addButton, &QAbstractButton::clicked, this,
          &MainWindow::onAddButtonClicked);
  connect(ui_->removeButton, &QAbstractButton::clicked, this,
          &MainWindow::onRemoveButtonClicked);
  connect(ui_->editButton, &QAbstractButton::clicked, this,
          &MainWindow::onEditButtonClicked);
  connect(ui_->copyButton, &QAbstractButton::clicked, this,
          &MainWindow::onCopyButtonClicked);
  connect(ui_->clearButton, &QAbstractButton::clicked, this,
          &MainWindow::onClearButtonClicked);
  connect(ui_->searchButton, &QAbstractButton::clicked, this,
          &MainWindow::onSearchButtonClicked);

  connect(ui_->actionSave, &QAction::triggered, this,
          &MainWindow::onSaveFileClicked);
  connect(ui_->actionLoad, &QAction::triggered, this,
          &MainWindow::onLoadFileClicked);

  connect(ui_->actionHelp, &QAction::triggered, this,
          &MainWindow::onHelpActionClicked);
  connect(ui_->actionAbout, &QAction::triggered, this,
          &MainWindow::onAboutActionClicked);

  connect(ui_->criterionComboBox, &QComboBox::activated, this,
          &MainWindow::onCriterionComboBoxActivated);
}

void MainWindow::setupTable() {
  tableData_ = new TableData(QVector<QString>{"Автор", "Тема", "Фраза"});
  ui_->mainTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui_->mainTableView->verticalHeader()->hide();
  ui_->mainTableView->setModel(tableData_->getModel());
}

void MainWindow::initCompleter() {
  compl_ = new QCompleter(tableData_->getModel(), this);
  compl_->setCompletionColumn(1);
  ui_->searchLineEdit->setCompleter(compl_);
}

void MainWindow::buttonMessageBox(const QString& text) {
  QMessageBox msg_box;
  msg_box.setWindowTitle("Таблица");
  msg_box.setWindowIcon(windowIcon());
  msg_box.setIcon(QMessageBox::Information);
  msg_box.setText(text);
  msg_box.exec();
}
