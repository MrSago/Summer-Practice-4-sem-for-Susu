
#include "tabledata.h"

#include <QStandardItemModel>

TableData::TableData(const QVector<QString>& column_headers)
    : model_(new QStandardItemModel(0, column_headers.size())),
      sourceModel_(model_) {
  for (int i = 0; i < column_headers.size(); ++i) {
    model_->setHeaderData(i, Qt::Horizontal, column_headers[i]);
  }
}

TableData::~TableData() {
  if (model_ != sourceModel_) {
    delete model_;
  }
  delete sourceModel_;
}

void TableData::addRow(QVector<QString>& columns) {
  if (columns.size() > model_->columnCount()) {
    return;
  }

  int row_count = model_->rowCount();
  model_->insertRow(row_count);
  for (int i = 0; i < columns.size(); ++i) {
    QModelIndex index = model_->index(row_count, i);
    model_->setData(index, columns[i]);
  }
}

bool TableData::removeRow(int row) { return model_->removeRow(row); }

QVector<QString> TableData::getRowData(int row) {
  QVector<QString> data(model_->columnCount());
  for (int i = 0; i < data.size(); ++i) {
    QModelIndex index = model_->index(row, i);
    data[i] = model_->data(index).toString();
  }
  return data;
}

void TableData::editRow(QVector<QString>& columns, int row) {
  if (columns.size() > model_->columnCount()) {
    return;
  }

  for (int i = 0; i < columns.size(); ++i) {
    QModelIndex index = model_->index(row, i);
    model_->setData(index, columns[i]);
  }
}

void TableData::resetModel() { model_ = sourceModel_; }
