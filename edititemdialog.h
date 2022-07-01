#ifndef EDITITEMDIALOG_H
#define EDITITEMDIALOG_H

#include <QDialog>

namespace Ui {
class EditItemDialog;
}

class EditItemDialog : public QDialog {
  Q_OBJECT

 public:
  explicit EditItemDialog(QVector<QString>& items, QWidget* parent = nullptr);
  ~EditItemDialog();
  QString getAuthor();
  QString getTheme();
  QString getPhrase();

 private:
  Ui::EditItemDialog* ui;
};

#endif  // EDITITEMDIALOG_H
