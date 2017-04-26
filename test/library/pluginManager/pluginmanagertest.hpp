#ifndef PLUGINMANAGERTEST_HPP
#define PLUGINMANAGERTEST_HPP

#include <QObject>
#include <QTest>

#include "plugin.hpp"
#include "pluginmanager.hpp"

#include "library/pluginApi/pluginapitest.hpp"

class PluginManagerTest : public QObject {
  Q_OBJECT
public:
  QString current_dir{};

private slots:
  void initTestCase() {}

  void pluginMangerConstructor() {
    PluginManager *pm = new PluginManager();
    delete pm;
  }

  void pluginRegistration() {

    PluginManager pm;
    Plugin *findResult;
    TestPlugin tp;

    pm.registerPlugin(tp);
    findResult = pm.findPlugin(
        "de.hochschule-trier.soda.test.nonexistentplugin", Version{0, 0, 0});
    QVERIFY(findResult == nullptr);
    findResult = pm.findPlugin(TestPlugin_PID, tp.getVersion());
    QVERIFY(findResult != nullptr);
    QVERIFY(&tp == findResult);
  }

  void pluginLoading() {
    PluginManager pm;
    QStringList dirs;
    dirs.append(current_dir + "/../lib");
    pm.loadPlugins(dirs);
    size_t pluginCount = pm.countRegisteredPlugins();
    QVERIFY(pluginCount > 0);
  }

  void pluginSearch() {

    PluginManager pm;
    Plugin *findResult;
    TestPlugin tp_old, tp, tp_new;

    Version oldVersion{0, 0, 0};
    Version currentVersion{1, 0, 0};
    Version newVersion{2, 0, 0};

    tp_old.setVersion(oldVersion);
    tp.setVersion(currentVersion);
    tp_new.setVersion(newVersion);

    pm.registerPlugin(tp_old);
    pm.registerPlugin(tp);
    pm.registerPlugin(tp_new);

    findResult = pm.findPlugin(TestPlugin_PID, currentVersion);
    QVERIFY(findResult != nullptr);
    QVERIFY(&tp == findResult);

    oldVersion = Version{0, 0, 0};
    currentVersion = Version{0, 1, 0};
    newVersion = Version{0, 2, 0};

    tp_old.setVersion(oldVersion);
    tp.setVersion(currentVersion);
    tp_new.setVersion(newVersion);

    pm.registerPlugin(tp_old);
    pm.registerPlugin(tp);
    pm.registerPlugin(tp_new);

    findResult = pm.findPlugin(TestPlugin_PID, currentVersion);
    QVERIFY(findResult != nullptr);
    QVERIFY(&tp == findResult);

    oldVersion = Version{0, 0, 0};
    currentVersion = Version{0, 0, 1};
    newVersion = Version{0, 0, 2};

    tp_old.setVersion(oldVersion);
    tp.setVersion(currentVersion);
    tp_new.setVersion(newVersion);

    pm.registerPlugin(tp_old);
    pm.registerPlugin(tp);
    pm.registerPlugin(tp_new);

    findResult = pm.findPlugin(TestPlugin_PID, currentVersion);
    QVERIFY(findResult != nullptr);
    QVERIFY(&tp == findResult);
  }
};

#endif // PLUGINMANAGERTEST_HPP
