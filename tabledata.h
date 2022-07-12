#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractItemModel>
#include <QCompleter>

#include "prefixsearcher.h"

class TableData {
 public:
  TableData(const QVector<QString>& column_headers,
            const QVector<int>& search_criterions);
  ~TableData();

  QAbstractItemModel* getModel() const { return model_; }
  void addRow(QVector<QString>& columns);
  bool removeRow(int row);
  QVector<QString> getRowData(int row);
  void editRow(QVector<QString>& columns, int row);

  bool saveToJson(const QString& path);
  QAbstractItemModel* loadFromJson(const QString& path);

  QAbstractItemModel* resetModel();
  QAbstractItemModel* search(const QString& str);

 private:
  QVector<QString> headers_;
  QAbstractItemModel* model_;
  // QAbstractItemModel* const sourceModel_;
  QMap<int, PrefixSearcher*> criterionSearch_;

  void initHeaders();
  int lastID();
};

#endif  // TABLEMODEL_H
