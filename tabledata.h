#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractItemModel>
#include <QStandardItemModel>

class TableData {
 public:
  TableData();
  QAbstractItemModel* getModel();

 private:
  QAbstractItemModel* _model;
};

#endif  // TABLEMODEL_H
