#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QDialog>

namespace Ui {
class HelpWindow;
}

/**
 * @brief Класс окна с подсказками о приложении
 */
class HelpWindow : public QDialog {
  Q_OBJECT

 public:
  explicit HelpWindow(QWidget* parent = nullptr);
  ~HelpWindow();

 private:
  Ui::HelpWindow* ui_;
};

#endif  // HELPWINDOW_H
