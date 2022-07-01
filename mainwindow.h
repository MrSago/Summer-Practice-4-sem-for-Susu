#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractItemModel>
#include <QListView>
#include <QMainWindow>
#include <QStringListModel>

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

 private:
  Ui::MainWindow* ui;
  TableData tableData;
};
#endif  // MAINWINDOW_H
