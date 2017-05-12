#include <QDir>

#include "catch.hpp"

#include "pluginmanager.hpp"

#include "library/pluginApi/pluginapitest.hpp"

#include "pluginmanagertest.hpp"

using namespace soda::pluginmanager;
using namespace soda::pluginapi;

TEST_CASE("Destructor"
          "[pluginManager]") {
  PluginManager *pm = new PluginManager();
  delete pm;
}

TEST_CASE("Plugin Loading"
          "[pluginManager]") {
  PluginManager pm;
  QStringList dirs;
  dirs.append(QDir::currentPath() + "/lib");
  dirs.append(QDir::currentPath() + "/../lib");
  pm.loadPlugins(dirs);
  size_t pluginCount = pm.countRegisteredPlugins();
  REQUIRE(pluginCount > 0);
}

TEST_CASE("Plugin registration", "[pluginRegistry]") {

  PluginManager pm;
  Plugin *findResult;
  TestPlugin tp;

  pm.registerPlugin(tp);
  findResult = pm.findPlugin("de.hochschule-trier.soda.test.nonexistentplugin",
                             Version{0, 0, 0});
  REQUIRE(findResult == nullptr);
  findResult = pm.findPlugin(TestPlugin_PID, tp.getVersion());
  REQUIRE(findResult != nullptr);
  REQUIRE(&tp == findResult);
}

TEST_CASE("Plugin search", "[pluginRegistry]") {

  PluginManager pm;
  Plugin *findResult, *noResult;
  TestPlugin tp_old, tp;

  Version oldVersion{0, 0, 0};
  Version currentVersion{1, 0, 0};

  tp_old.setVersion(oldVersion);
  tp.setVersion(currentVersion);

  pm.registerPlugin(tp_old);
  pm.registerPlugin(tp);

  findResult = pm.findPlugin(TestPlugin_PID, currentVersion);
  REQUIRE(findResult != nullptr);
  REQUIRE(&tp == findResult);

  noResult = pm.findPlugin(TestPlugin_PID, oldVersion);
  REQUIRE(noResult == nullptr);

  oldVersion = Version{0, 0, 0};
  currentVersion = Version{0, 1, 0};

  tp_old.setVersion(oldVersion);
  tp.setVersion(currentVersion);

  pm.registerPlugin(tp_old);
  pm.registerPlugin(tp);

  findResult = pm.findPlugin(TestPlugin_PID, currentVersion);
  REQUIRE(findResult != nullptr);
  REQUIRE(&tp == findResult);

  noResult = pm.findPlugin(TestPlugin_PID, oldVersion);
  REQUIRE(noResult == nullptr);

  oldVersion = Version{0, 0, 0};
  currentVersion = Version{0, 0, 1};

  tp_old.setVersion(oldVersion);
  tp.setVersion(currentVersion);

  pm.registerPlugin(tp_old);
  pm.registerPlugin(tp);

  findResult = pm.findPlugin(TestPlugin_PID, currentVersion);
  REQUIRE(findResult != nullptr);
  REQUIRE(&tp == findResult);

  noResult = pm.findPlugin(TestPlugin_PID, oldVersion);
  REQUIRE(noResult == nullptr);
}
