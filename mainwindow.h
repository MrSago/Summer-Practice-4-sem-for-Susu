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
  void onClearButtonClicked();
  void onSearchButtonClicked();

  void onSaveFileClicked();
  void onLoadFileClicked();

  void onHelpActionClicked();
  void onAboutActionClicked();

  void onCriterionComboBoxActivated(int index);

 private:
  Ui::MainWindow* ui_;
  TableData* tableData_;
  QCompleter* compl_;

  void connectActions();
  void setupTable();
  void initCompleter();

  void buttonMessageBox(const QString& reason);
};
#endif  // MAINWINDOW_H
