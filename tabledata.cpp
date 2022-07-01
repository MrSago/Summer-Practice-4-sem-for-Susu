#include "tabledata.h"

TableData::TableData() : _model(new QStandardItemModel(0, 3)) {
  _model->setHeaderData(0, Qt::Horizontal, QString("Автор"));
  _model->setHeaderData(1, Qt::Horizontal, QString("Тема"));
  _model->setHeaderData(2, Qt::Horizontal, QString("Фраза"));

  int rows = 5;
  _model->insertRows(_model->rowCount(), rows);
  for (int i = 0; i < rows; ++i) {
    _model->setData(_model->index(i, 0), "Автор");
    _model->setData(_model->index(i, 1), "жошшшш");
    _model->setData(_model->index(i, 2), "По факту кста внатуре");
  }
}

QAbstractItemModel* TableData::getModel() { return _model; }

void TableData::addRow(QVector<QString>& columns) {
  if (columns.size() > _model->columnCount()) {
    return;
  }

  int row_count = _model->rowCount();
  _model->insertRow(row_count);

  for (int i = 0; i < columns.size(); ++i) {
    QModelIndex index = _model->index(row_count, i);
    _model->setData(index, columns[i]);
  }
}

bool TableData::removeRow(int row) { return _model->removeRow(row); }

QVector<QString> TableData::getRowData(int row) {
  QVector<QString> data(_model->columnCount());
  for (int i = 0; i < data.size(); ++i) {
    QModelIndex index = _model->index(row, i);
    data[i] = _model->data(index).toString();
  }
  return data;
}

void TableData::changeRow(QVector<QString>& columns, int row) {
  if (columns.size() > _model->columnCount()) {
    return;
  }

  for (int i = 0; i < columns.size(); ++i) {
    QModelIndex index = _model->index(row, i);
    _model->setData(index, columns[i]);
  }
}
