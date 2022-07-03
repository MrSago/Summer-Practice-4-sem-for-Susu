
#include "prefixsearcher.h"

void PrefixSearcher::insert(QString& str, void* input_data) {
  int vertice = 0;
  for (QChar sym : str) {
    sym = sym.toLower();
    if (!canGoNode(vertice, sym)) {
      createNode(vertice, sym);
    }
    vertice = getNextVertice(vertice, sym);
  }
  trie_[vertice].data = input_data;
}

void PrefixSearcher::erase(QString& str) {
  int vertice = 0;
  for (QChar sym : str) {
    if (!canGoNode(vertice, sym)) {
      return;
    }
    vertice = getNextVertice(vertice, sym);
  }
  trie_[vertice].isLeaf = false;
  trie_[vertice].data = nullptr;
}

QVector<void*> PrefixSearcher::find(QString& prefix) {
  int vertice = 0;
  for (QChar sym : prefix) {
    sym = sym.toLower();
    if (!canGoNode(vertice, sym)) {
      return QVector<void*>();
    }
  }
  QVector<void*> result;
  depthFirstSearch(result, vertice);
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

void PrefixSearcher::depthFirstSearch(QVector<void*>& result, int vertice) {
  if (isLeaf(vertice)) {
    result.push_back(trie_[vertice].data);
  }
  QList vertices = trie_[vertice].nextNodes.values();
  for (int& next_vertice : vertices) {
    depthFirstSearch(result, next_vertice);
  }
}
