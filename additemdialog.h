#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>

namespace Ui {
class AddItemDialog;
}

class AddItemDialog : public QDialog {
  Q_OBJECT

 public:
  explicit AddItemDialog(QWidget* parent = nullptr);
  ~AddItemDialog();
  QString getAuthor();
  QString getTheme();
  QString getPhrase();

 private:
  Ui::AddItemDialog* ui_;

  void connectButtons();
};

#endif  // ADDITEMDIALOG_H
