#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>

namespace Ui {
class AddItemDialog;
}

/**
 * @brief Класс окна добавления записи в таблицу
 */
class AddItemDialog : public QDialog {
  Q_OBJECT

 public:
  explicit AddItemDialog(QWidget* parent = nullptr);
  ~AddItemDialog();

  /**
   * @brief Получить строку с автором из authorLineEdit
   * 
   * @return QString authorLineEdit
   */
  QString getAuthor();

  /**
   * @brief Получить строку с темой из themeLineEdit
   * 
   * @return QString themeLineEdit
   */
  QString getTheme();

  /**
   * @brief Получить строку с фразой из phraseTextEdit
   * 
   * @return QString phraseTextEdit
   */
  QString getPhrase();

 private:
  Ui::AddItemDialog* ui_;

  /**
   * @brief Соединить диалоговые кнопки с их ивентами
   */
  void connectButtons();
};

#endif  // ADDITEMDIALOG_H
