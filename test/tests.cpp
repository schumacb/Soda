#include <QCoreApplication>
#include <QtTest/QTest>

#include "library/pluginManager/pluginmanagertest.hpp"

int main( int argc, char** argv )
{
  QCoreApplication app(argc, argv);
  int result;
  // QtTest

  PluginManagerTest pluginManagerTest;
  pluginManagerTest.current_dir = app.applicationDirPath();
  result = QTest::qExec(&pluginManagerTest, argc, argv);
  if (result != 0) {
      return result;
  }
}
