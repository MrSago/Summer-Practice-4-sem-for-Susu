#include "tabledata.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardItemModel>

TableData::TableData(const QVector<QString>& column_headers)
    : model_(new QStandardItemModel(0, column_headers.size() + 1)),
      headers_(column_headers) {
  headers_.push_front("ID");
  initHeaders();
  initSearcher();
}

TableData::~TableData() {
  if (model_ != nullptr) {
    delete model_;
  }
  clearSearcher();
}

bool TableData::addRow(const QVector<QString>& columns) {
  if (columns.size() > model_->columnCount()) {
    return false;
  }

  int row_count = model_->rowCount();
  int last_id = lastID();
  model_->insertRow(row_count);
  model_->setData(model_->index(row_count, 0), last_id);

  for (int i = 0; i < columns.size(); ++i) {
    QModelIndex index = model_->index(row_count, i + 1);
    model_->setData(index, columns[i]);
    criterionSearch_[headers_[i + 1]]->insert(columns[i], last_id);
  }

  return true;
}

bool TableData::removeRow(int id) {
  int row = findRow(id);
  for (int i = 1; i < headers_.size(); ++i) {
    QModelIndex index = model_->index(row, i);
    QString data = model_->data(index).toString();
    criterionSearch_[headers_[i]]->erase(data, id);
  }
  return model_->removeRow(row);
}

QVector<QString> TableData::getRowData(int id) {
  int row = findRow(id);
  QVector<QString> data(model_->columnCount());
  for (int i = 0; i < data.size(); ++i) {
    QModelIndex index = model_->index(row, i);
    data[i] = model_->data(index).toString();
  }
  return data;
}

void TableData::editRow(const QVector<QString>& columns, int id) {
  if (columns.size() > model_->columnCount()) {
    return;
  }

  int row = findRow(id);
  for (int i = 0; i < columns.size(); ++i) {
    QModelIndex index = model_->index(row, i + 1);
    QString data = model_->data(index).toString();
    criterionSearch_[headers_[i + 1]]->erase(data, id);
    criterionSearch_[headers_[i + 1]]->insert(columns[i], id);
    model_->setData(index, columns[i]);
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
      QString data = model_->data(index).toString();
      obj[headers_[j]] = data;
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

  if (model_ != nullptr) {
    delete model_;
  }
  model_ = new QStandardItemModel(array.size(), headers_.size());
  initHeaders();
  clearSearcher();
  initSearcher();

  for (int i = 0; i < array.size(); ++i) {
    int id = array[i].toObject()[headers_[0]].toString().toInt();
    for (int j = 0; j < headers_.size(); ++j) {
      QModelIndex index = model_->index(i, j);
      QString data = array[i].toObject()[headers_[j]].toString();
      model_->setData(index, data);
      if (j > 0) {
        criterionSearch_[headers_[j]]->insert(data, id);
      }
    }
  }

  return model_;
}

QAbstractItemModel* TableData::clearModel() {
  if (model_ != nullptr) {
    delete model_;
  }
  model_ = new QStandardItemModel(0, headers_.size());
  initHeaders();
  clearSearcher();
  initSearcher();
  return model_;
}

QAbstractItemModel* TableData::search(const QString& header,
                                      const QString& search_string) {
  QVector<int> ids = criterionSearch_[header]->find(search_string);

  QAbstractItemModel* searchModel_ =
      new QStandardItemModel(ids.size(), headers_.size());
  for (int i = 0; i < headers_.size(); ++i) {
    searchModel_->setHeaderData(i, Qt::Horizontal, headers_[i]);
  }

  for (int i = 0; i < ids.count(); ++i) {
    for (int j = 0; j < model_->rowCount(); ++j) {
      QModelIndex index = model_->index(j, 0);
      int id = model_->data(index).toInt();
      if (id == ids[i]) {
        for (int k = 0; k < model_->columnCount(); ++k) {
          index = model_->index(j, k);
          QString data = model_->data(index).toString();
          QModelIndex index_search = searchModel_->index(i, k);
          searchModel_->setData(index_search, data);
        }
        break;
      }
    }
  }

  return searchModel_;
}

void TableData::initHeaders() {
  for (int i = 0; i < headers_.size(); ++i) {
    model_->setHeaderData(i, Qt::Horizontal, headers_[i]);
  }
}

void TableData::initSearcher() {
  for (int i = 1; i < headers_.size(); ++i) {
    criterionSearch_[headers_[i]] = new PrefixSearcher;
  }
}

void TableData::clearSearcher() {
  for (PrefixSearcher* searcher : criterionSearch_) {
    if (searcher != nullptr) {
      delete searcher;
    }
  }
  criterionSearch_.clear();
}

int TableData::lastID() {
  return model_->data(model_->index(model_->rowCount() - 1, 0))
             .toString()
             .toInt() +
         1;
}

int TableData::findRow(int id) {
  for (int i = 0; i < model_->rowCount(); ++i) {
    QModelIndex index = model_->index(i, 0);
    int ix = model_->data(index).toString().toInt();
    if (ix == id) {
      return i;
    }
  }
  return -1;
}
