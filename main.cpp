#include <QAbstractItemModel>
#include <QApplication>
#include <QListView>
#include <QStringListModel>

#include "mainwindow.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  MainWindow mainWindow;
  mainWindow.show();

  return app.exec();
}
