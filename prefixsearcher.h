#ifndef PREFIXSEARCHER_H
#define PREFIXSEARCHER_H

#include <QMap>
#include <QString>
#include <QVector>

struct Node {
  QMap<QChar, int> nextNodes;
  bool isLeaf = false;
  QVector<int> ids;
};

class PrefixSearcher {
 public:
  PrefixSearcher() : countNodes_(1), countStrings_(0) {}
  int getCountStrings() { return countStrings_; }
  void insert(const QString& str, int input_id);
  void erase(const QString& str, int erase_id);
  QVector<int> find(const QString& prefix);

 private:
  QMap<int, Node> trie_;
  int countNodes_;
  int countStrings_;

  bool canGoNode(int vertice, QChar sym);
  void createNode(int vertice, QChar sym);
  int getNextVertice(int vertice, QChar sym);
  bool isLeaf(int vretice);
  void depthFirstSearch(QVector<int>& result, int vertice);
};

#endif  // PREFIXSEARCHER_H
