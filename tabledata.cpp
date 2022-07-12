
#include "tabledata.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardItemModel>

TableData::TableData(const QVector<QString>& column_headers,
                     const QVector<int>& search_criterions)
    : model_(new QStandardItemModel(0, column_headers.size() + 1)) {
  for (const int i : search_criterions) {
    if (i >= 1 && i < model_->columnCount()) {
      criterionSearch_[i] = new PrefixSearcher;
    }
  }

  headers_ = column_headers;
  headers_.push_front("ID");
  initHeaders();
}

TableData::~TableData() {
  if (model_ != nullptr) {
    delete model_;
  }
  // delete sourceModel_;
  for (PrefixSearcher* i : criterionSearch_) {
    delete i;
  }
}

void TableData::addRow(QVector<QString>& columns) {
  if (columns.size() > model_->columnCount()) {
    return;
  }

  int row_count = model_->rowCount();
  int last_id = lastID();
  model_->insertRow(row_count);
  model_->setData(model_->index(row_count, 0), last_id);
  for (int i = 1; i < columns.size() + 1; ++i) {
    QModelIndex index = model_->index(row_count, i);
    model_->setData(index, columns[i - 1]);
  }
}

bool TableData::removeRow(int row) { return model_->removeRow(row); }

QVector<QString> TableData::getRowData(int row) {
  QVector<QString> data(model_->columnCount());
  for (int i = 1; i < data.size() + 1; ++i) {
    QModelIndex index = model_->index(row, i);
    data[i - 1] = model_->data(index).toString();
  }
  return data;
}

void TableData::editRow(QVector<QString>& columns, int row) {
  if (columns.size() > model_->columnCount()) {
    return;
  }

  for (int i = 1; i < columns.size() + 1; ++i) {
    QModelIndex index = model_->index(row, i);
    model_->setData(index, columns[i - 1]);
  }
}

bool TableData::saveToJson(const QString& path) {
  QFile file(path);
  if (!file.open(QIODevice::WriteOnly)) {
    return false;
  }

  QJsonArray array;
  for (int i = 0; i < model_->rowCount(); ++i) {
    QJsonObject obj;
    for (int j = 0; j < model_->columnCount(); ++j) {
      QModelIndex index = model_->index(i, j);
      QString header = model_->headerData(j, Qt::Horizontal).toString();
      QString data = model_->data(index).toString();
      obj[header] = data;
    }
    array.push_back(obj);
  }

  QJsonObject save_data;
  save_data.insert("TABLE_DATA", array);
  file.write(QJsonDocument(save_data).toJson());
  return true;
}

QAbstractItemModel* TableData::loadFromJson(const QString& path) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly)) {
    return nullptr;
  }

  QJsonDocument load_doc(QJsonDocument::fromJson(file.readAll()));
  if (!load_doc.object().contains("TABLE_DATA")) {
    return nullptr;
  }
  QJsonArray array = load_doc.object()["TABLE_DATA"].toArray();

  QVector<QString> headers;
  for (int i = 0; i < model_->columnCount(); ++i) {
    headers.push_back(model_->headerData(i, Qt::Horizontal).toString());
  }

  delete model_;
  model_ = new QStandardItemModel(array.size(), headers.size());
  for (int i = 0; i < headers.size(); ++i) {
    model_->setHeaderData(i, Qt::Horizontal, headers[i]);
  }

  for (int i = 0; i < array.size(); ++i) {
    for (int j = 0; j < headers.size(); ++j) {
      QModelIndex index = model_->index(i, j);
      QString data = array[i].toObject()[headers[j]].toString();
      model_->setData(index, data);
    }
  }

  return model_;
}

QAbstractItemModel* TableData::resetModel() {
  if (model_ != nullptr) {
    delete model_;
  }
  model_ = new QStandardItemModel(0, headers_.size());
  initHeaders();
  return model_;
}

void TableData::initHeaders() {
  for (int i = 0; i < headers_.size(); ++i) {
    model_->setHeaderData(i, Qt::Horizontal, headers_[i]);
  }
}

int TableData::lastID() {
  return model_->data(model_->index(model_->rowCount() - 1, 0))
             .toString()
             .toInt() +
         1;
}
