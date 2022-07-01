#include "tabledata.h"

TableData::TableData() : _model(new QStandardItemModel(0, 3)) {
  _model->setHeaderData(0, Qt::Horizontal, QString("Автор"));
  _model->setHeaderData(1, Qt::Horizontal, QString("Тема"));
  _model->setHeaderData(2, Qt::Horizontal, QString("Фраза"));

  int rows = 5;
  _model->insertRows(_model->rowCount(), rows);
  for (int i = 0; i < rows; ++i) {
    _model->setData(_model->index(i, 0), "Додик");
    _model->setData(_model->index(i, 1), "Тема залупная");
    _model->setData(_model->index(i, 2),
                    "По факту кста внатуре\nв прокуратуре");
  }
}

QAbstractItemModel* TableData::getModel() { return _model; }
