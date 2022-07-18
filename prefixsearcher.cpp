#include "prefixsearcher.h"

void PrefixSearcher::insert(const QString& str, int input_id) {
  int vertice = 0;
  for (QChar sym : str) {
    if (!canGoNode(vertice, sym)) {
      createNode(vertice, sym);
    }
    vertice = getNextVertice(vertice, sym);
  }
  trie_[vertice].ids.push_back(input_id);
  trie_[vertice].isLeaf = trie_[vertice].ids.size();
}

void PrefixSearcher::erase(const QString& str, int erase_id) {
  int vertice = 0;
  for (QChar sym : str) {
    if (!canGoNode(vertice, sym)) {
      return;
    }
    vertice = getNextVertice(vertice, sym);
  }

  Node& node = trie_[vertice];
  auto it = std::find(node.ids.begin(), node.ids.end(), erase_id);
  if (it != node.ids.end()) {
    node.ids.erase(it);
  }
  node.isLeaf = node.ids.size();
}

QVector<int> PrefixSearcher::find(const QString& prefix) {
  int vertice = 0;
  for (QChar sym : prefix) {
    if (!canGoNode(vertice, sym)) {
      return QVector<int>();
    }
    vertice = getNextVertice(vertice, sym);
  }
  QVector<int> result;
  depthFirstSearch(result, vertice);
  std::sort(result.begin(), result.end());
  return result;
}

bool PrefixSearcher::canGoNode(int vertice, QChar sym) {
  return trie_[vertice].nextNodes.contains(sym);
}

void PrefixSearcher::createNode(int vertice, QChar sym) {
  trie_[vertice].nextNodes[sym] = countNodes_++;
}

int PrefixSearcher::getNextVertice(int vertice, QChar sym) {
  return trie_[vertice].nextNodes[sym];
}

bool PrefixSearcher::isLeaf(int vertice) { return trie_[vertice].isLeaf; }

void PrefixSearcher::depthFirstSearch(QVector<int>& result, int vertice) {
  if (isLeaf(vertice)) {
    for (int id : trie_[vertice].ids) {
      result.push_back(id);
    }
  }
  QList vertices = trie_[vertice].nextNodes.values();
  for (int& next_vertice : vertices) {
    depthFirstSearch(result, next_vertice);
  }
}
