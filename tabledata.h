#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractItemModel>
#include <QCompleter>

#include "prefixsearcher.h"

/**
 * @brief Класс реализующий работу с таблицей
 */
class TableData {
 public:
  /**
   * @brief Конструктор создания объекта класса TableData
   * 
   * @param column_headers Заголовки столбцов
   */
  TableData(const QVector<QString>& column_headers);

  ~TableData();

  /**
   * @brief Получить текущую модель таблицы
   * 
   * @return QAbstractItemModel* Текущая модель
   */
  QAbstractItemModel* getModel() const { return model_; }

  /**
   * @brief Добавить запись в таблицу
   * 
   * @param columns Столбцы
   * @return true Запись добавлена
   * @return false Ошибка добавления записи
   */
  bool addRow(const QVector<QString>& columns);

  /**
   * @brief Удалить запись из таблицы
   * 
   * @param id Идентификатор строки
   * @return true Запись удалена
   * @return false Ошибка удаления записи
   */
  bool removeRow(int id);

  /**
   * @brief Получить строку из таблицы
   * 
   * @param id Идентификатор строки
   * @return QVector<QString> Список столбцов строки
   */
  QVector<QString> getRowData(int id);

  /**
   * @brief Редактировать строку в таблицу
   * 
   * @param columns Измененная строка для вставки
   * @param id Идентификатор строки
   */
  void editRow(const QVector<QString>& columns, int id);

  /**
   * @brief Сохранить данные таблицы в файл json
   * 
   * @param path Путь до файла
   * @return true Файл сохранен
   * @return false Ошибка сохранения файла
   */
  bool saveToJson(const QString& path);

  /**
   * @brief Загрузка данных таблицы из файла json
   * 
   * @param path Пусть до файла
   * @return QAbstractItemModel* Новая модель таблицы
   */
  QAbstractItemModel* loadFromJson(const QString& path);

  /**
   * @brief Очистить модель таблицу
   * 
   * @return QAbstractItemModel* Новая модель таблицы
   */
  QAbstractItemModel* clearModel();

  /**
   * @brief Поиск подстрок в таблицу по заданному критерию
   * 
   * @param criterion Критерий (столбец) для поиска
   * @param str Строка для поиска
   * @return QAbstractItemModel* Новая модель поиска таблицы
   */
  QAbstractItemModel* search(const QString& criterion, const QString& str);

 private:
  QAbstractItemModel* model_;
  QAbstractItemModel* savedModel_;
  QVector<QString> headers_;
  QHash<QString, PrefixSearcher*> criterionSearch_;

  /* Методы инициализации класса */
  void initHeaders();
  void initSearcher();
  /*******************************/

  /**
   * @brief Очистка данных префиксных деревьев
   */
  void clearSearcher();

  /**
   * @brief Вернуть последний идентификатор строки
   * 
   * @return int Идентификатор строки
   */
  int lastID();

  /**
   * @brief Поиск строки с определенным идентификатором
   * 
   * @param id Идентификатор для поиска
   * @return int Номер строки
   */
  int findRow(int id);
};

#endif  // TABLEMODEL_H
