#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCompleter>
#include <QMainWindow>

#include "tabledata.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void onAddButtonClicked();
  void onRemoveButtonClicked();
  void onEditButtonClicked();
  void onCopyButtonClicked();
  void onSearchButtonClicked();

 private:
  Ui::MainWindow* ui_;
  TableData* tableData_;

  void connectButtons();
  void setupTable();

  void buttonMessageBox(const QString& reason);
};
#endif  // MAINWINDOW_H
