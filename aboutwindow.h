#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

namespace Ui {
class AboutWindow;
}

/**
 * @brief Класс окна с информацией о приложении и разработчике
 */
class AboutWindow : public QDialog {
  Q_OBJECT

 public:
  explicit AboutWindow(QWidget* parent = nullptr);
  ~AboutWindow();

 private:
  Ui::AboutWindow* ui_;
};

#endif  // ABOUTWINDOW_H
