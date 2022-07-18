#ifndef EDITITEMDIALOG_H
#define EDITITEMDIALOG_H

#include <QDialog>

namespace Ui {
class EditItemDialog;
}

/**
 * @brief Класс окна редактирования записи таблицы
 */
class EditItemDialog : public QDialog {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор для создания нового объекта класса EditItemDialog
   * 
   * @param items входные данные из таблицы для редактирования
   * @param parent указатель на родительский виджет (по умолчанию nullptr)
   */
  explicit EditItemDialog(QVector<QString>& items, QWidget* parent = nullptr);

  ~EditItemDialog();

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
  Ui::EditItemDialog* ui_;

  /**
   * @brief Соединить диалоговые кнопки с их ивентами
   */
  void connectButtons();

  /**
   * @brief Установить входные данные в полях диалогового окна
   * 
   * @param items Входные данные таблицы
   */
  void setEditTexts(QVector<QString>& items);
};

#endif  // EDITITEMDIALOG_H
