#ifndef PREFIXSEARCHER_H
#define PREFIXSEARCHER_H

#include <QMap>
#include <QString>
#include <QVector>

/**
 * @brief Вершина префиксного дерева
 */
struct Node {
  QMap<QChar, int> nextNodes;
  bool isLeaf = false;
  QVector<int> ids;
};

/**
 * @brief Класс поиска подстрок реализущий префиксное дерево (бор)
 */
class PrefixSearcher {
 public:
  PrefixSearcher() : countNodes_(1), countStrings_(0) {}

  /**
   * @brief Получить количество строк в префиксном дереве
   * 
   * @return int Число строк в дереве
   */
  int getCountStrings() { return countStrings_; }

  /**
   * @brief Вставка строки в префиксное дерево
   * 
   * @param str Строка для вставки
   * @param input_id Идентификатор строки
   */
  void insert(const QString& str, int input_id);

  /**
   * @brief Удаление строки из префиксного дерева
   * 
   * @param str Строка для удаления
   * @param erase_id Идентификатор строки
   */
  void erase(const QString& str, int erase_id);

  /**
   * @brief Поиск всех подстрок в префиксном дереве
   * 
   * @param prefix Подстрока для поиска
   * @return QVector<int> Список найденных идентификаторов подстрок
   */
  QVector<int> find(const QString& prefix);

 private:
  QMap<int, Node> trie_;
  int countNodes_;
  int countStrings_;

  /**
   * @brief Проверка можно ли пройтись по вершине
   * 
   * @param vertice Номер вершины
   * @param sym Символ строки
   * @return true Да, можно
   * @return false Нет, нельзя
   */
  bool canGoNode(int vertice, QChar sym);

  /**
   * @brief Создать вершину с номером vertice
   * 
   * @param vertice Номер вершины
   * @param sym Символ строки
   */
  void createNode(int vertice, QChar sym);

  /**
   * @brief Получить следующую вершину
   * 
   * @param vertice Номер текущей вершины
   * @param sym Символ строки
   * @return int Новый номер вершины
   */
  int getNextVertice(int vertice, QChar sym);

  /**
   * @brief Проверка на лист
   * 
   * @param vretice Номер вершины
   * @return true Является листом
   * @return false Не является листом
   */
  bool isLeaf(int vretice);

  /**
   * @brief Рекурсивный метод поиска в глубину (DFS) всех подстрок
   * 
   * @param result Ссылка на массив для сохранения результатов
   * @param vertice Номер текущей вершины
   */
  void depthFirstSearch(QVector<int>& result, int vertice);
};

#endif  // PREFIXSEARCHER_H
