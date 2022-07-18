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

/**
 * @brief Класс главного окна приложения
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 /* Ивенты кнопок и виджетов */
 private slots:
  void onRefreshButtonClicked();
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
 /****************************/

 private:
  Ui::MainWindow* ui_;
  TableData* tableData_;
  QCompleter* compl_;

  /* Методы инициализации класса */
  void connectActions();
  void setupTable();
  void initCompleter();
  /*******************************/

  /**
   * @brief Кастомизированный MessageBox для вывода оповещений и ошибок
   * 
   * @param reason Сообщение для отображения
   */
  void buttonMessageBox(const QString& reason);

  /**
   * @brief Обновление данных таблицы
   */
  void refreshTable();
};
#endif  // MAINWINDOW_H
