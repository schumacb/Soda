#ifndef PLUGINAPITEST_HPP
#define PLUGINAPITEST_HPP

#include <functional>
#include <sstream>

#include <QDebug>
#include <QObject>
#include <QtTest/qtest.h>

#include "plugininterface.hpp"
#include "pluginregistry.hpp"
#include "version.hpp"

#define TestPlugin_PID "de.hochschule-trier.soda.test.testplugin"
#define TestPlugin_Version                                                     \
  Version {                                                                    \
    PluginApi_VERSION_MAJOR, PluginApi_VERSION_MINOR, PluginApi_VERSION_PATCH  \
  }

class TestPlugin : public QObject, public PluginInterface {
  Q_OBJECT
  Q_INTERFACES(PluginInterface)
  Version m_version = TestPlugin_Version;

public:
  virtual const std::string getName() const override { return "TestPlugin"; }
  virtual const std::string getDescription() const override { return ""; }
  virtual const std::string getPid() const override { return TestPlugin_PID; }
  virtual const Version getVersion() const override { return m_version; }

  virtual void onLoad() override {}
  virtual void onUnload() override {}

  void setVersion(Version t_version) { m_version = t_version; }
};

class TestPluginRegistry : public PluginRegistry {
public:
  virtual void registerPlugin(PluginInterface &t_plugin) override {
    std::cerr
        << "Error: This is only a test stub without functionallity! "
           "TestPluginRegistry::registerPlugin() was called with plugin \""
        << t_plugin.getName() << "(" << t_plugin.getPid() << ")\"."
        << std::endl;
    throw std::bad_function_call();
  }

  virtual PluginInterface *findPlugin(const std::string t_pid,
                                      const Version t_version) override {
    std::cerr << "Error: This is only a test stub without functionallity! "
                 "TestPluginRegistry::findPlugin() was called with PID \""
              << t_pid << "\" and version \"" << t_version << "\"!"
              << std::endl;
    throw std::bad_function_call();
  }
};

class PluginApiTest : public QObject {
  Q_OBJECT

  Version v000{0, 0, 0};
  Version v000_2{0, 0, 0};
  Version v001{0, 0, 1};
  Version v010{0, 1, 0};
  Version v100{1, 0, 0};

private slots:
  void initTestCase() {}

  void pluginApi() {
    TestPlugin p;
    QVERIFY(PluginInterface::getInterfaceVersion() == TestPlugin_Version);
  }

  void destructors() {
    PluginRegistry *pr = new TestPluginRegistry();
    delete pr;

    PluginInterface *pi = new TestPlugin();
    delete pi;
  }

  void equalVersions() {
    QVERIFY(v000 == v000_2);
    QVERIFY(!(v000 != v000_2));
  }

  void unequalVersions() {
    QVERIFY(v000 != v001);
    QVERIFY(!(v000 == v001));
  }

  void majorVersionComparison() {
    QVERIFY(v000 < v100);
    QVERIFY(v000 <= v100);
    QVERIFY(v100 > v000);
    QVERIFY(v100 >= v000);
  }

  void minorVersionComparison() {
    QVERIFY(v000 < v010);
    QVERIFY(v000 <= v010);
    QVERIFY(v010 > v000);
    QVERIFY(v010 >= v000);
  }

  void patchVersionComparison() {
    QVERIFY(v000 < v001);
    QVERIFY(v000 <= v001);
    QVERIFY(v001 > v000);
    QVERIFY(v001 >= v000);
  }

  void streamingOperator() {

    std::stringstream ss;
    Version v{1, 2, 3};

    ss << v;

    QVERIFY(ss.str() == "1.2.3");
  }

  void cleanupTestCase() {}
};

#endif // PLUGINAPITEST_HPP
