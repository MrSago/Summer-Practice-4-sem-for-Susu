#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractItemModel>
#include <QCompleter>

#include "prefixsearcher.h"

class TableData {
 public:
  TableData(const QVector<QString>& column_headers);
  ~TableData();

  QAbstractItemModel* getModel() const { return model_; }
  bool addRow(const QVector<QString>& columns);
  bool removeRow(int id);
  QVector<QString> getRowData(int id);
  void editRow(const QVector<QString>& columns, int id);

  bool saveToJson(const QString& path);
  QAbstractItemModel* loadFromJson(const QString& path);

  QAbstractItemModel* clearModel();
  QAbstractItemModel* search(const QString& criterion, const QString& str);

 private:
  QAbstractItemModel* model_;
  QAbstractItemModel* savedModel_;
  QVector<QString> headers_;

  QHash<QString, PrefixSearcher*> criterionSearch_;

  void initHeaders();
  void initSearcher();
  void clearSearcher();
  int lastID();
  int findRow(int id);
};

#endif  // TABLEMODEL_H
