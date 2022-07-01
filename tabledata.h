#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractItemModel>
#include <QStandardItemModel>

class TableData {
 public:
  TableData();
  QAbstractItemModel* getModel();
  void addRow(QVector<QString>& columns);
  bool removeRow(int row);
  QVector<QString> getRowData(int row);
  void changeRow(QVector<QString>& columns, int row);

 private:
  QAbstractItemModel* _model;
};

#endif  // TABLEMODEL_H
