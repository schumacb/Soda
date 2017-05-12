#include "catch.hpp"

#include "pluginmanager.hpp"

#include "pluginapitest.hpp"

#include <QJsonObject>

using namespace soda::pluginapi;

static Version v000{0, 0, 0};
static Version v000_2{0, 0, 0};
static Version v001{0, 0, 1};
static Version v010{0, 1, 0};
static Version v100{1, 0, 0};

TEST_CASE("Interface version", "[pluginApi]") {
  TestPlugin p;
  REQUIRE(Plugin::getInterfaceVersion() == (TestPlugin_Version));
}

TEST_CASE("Destructors", "[pluginApi]") {
  PluginRegistry *pr = new TestPluginRegistry();
  delete pr;

  Plugin *pi = new TestPlugin();
  delete pi;

  TestAlgorithm *algo = new TestAlgorithm();
  delete algo;
}

TEST_CASE("Compare equal versions", "[pluginApi]") {
  REQUIRE(v000 == v000_2);
  REQUIRE(!(v000 != v000_2));
}

TEST_CASE("Compare unequal versions", "[pluginApi]") {
  REQUIRE(v000 != v001);
  REQUIRE(!(v000 == v001));
}

TEST_CASE("Compare major versions", "[pluginApi]") {
  REQUIRE(v000 < v100);
  REQUIRE(v000 <= v100);
  REQUIRE(v100 > v000);
  REQUIRE(v100 >= v000);
}

TEST_CASE("Compare minor versions", "[pluginApi]") {
  REQUIRE(v000 < v010);
  REQUIRE(v000 <= v010);
  REQUIRE(v010 > v000);
  REQUIRE(v010 >= v000);
}

TEST_CASE("Compare patch versions", "[pluginApi]") {
  REQUIRE(v000 < v001);
  REQUIRE(v000 <= v001);
  REQUIRE(v001 > v000);
  REQUIRE(v001 >= v000);
}

TEST_CASE("Streaming operator", "[pluginApi]") {
  std::stringstream ss;
  Version v{1, 2, 3};
  ss << v;
  REQUIRE(ss.str() == "1.2.3");
}

const QJsonObject &TestAlgorithm::getConfiguration() const {
  std::cerr << "Error: This is only a test stub without functionallity! "
               "TestAlgorithm::getConfiguration() was called. \""
            << std::endl;
  throw std::bad_function_call();
}

void TestAlgorithm::setConfiguration(const QJsonObject &t_configuration) {
  Q_UNUSED(t_configuration)
}

QString TestAlgorithm::getID() { return ""; }

void TestAlgorithm::run() {}

void TestAlgorithm::slot_process(cv::Mat) {}

const QString TestPlugin::getName() const { return "TestPlugin"; }

const QString TestPlugin::getDescription() const { return ""; }

const std::string TestPlugin::getPid() const { return TestPlugin_PID; }

const Version TestPlugin::getVersion() const { return m_version; }

void TestPlugin::onLoad(PluginRegistry &t_registry) { Q_UNUSED(t_registry) }

void TestPlugin::onUnload(PluginRegistry &t_registry) { Q_UNUSED(t_registry) }

void TestPlugin::setVersion(Version t_version) { m_version = t_version; }

void TestPluginRegistry::registerPlugin(Plugin &t_plugin) {
  std::cerr << "Error: This is only a test stub without functionallity! "
               "TestPluginRegistry::registerPlugin() was called with plugin \""
            << t_plugin.getName().toStdString() << "(" << t_plugin.getPid()
            << ")\"." << std::endl;
  throw std::bad_function_call();
}

Plugin *TestPluginRegistry::findPlugin(const std::string &t_pid,
                                       const Version &t_version) {
  std::cerr << "Error: This is only a test stub without functionallity! "
               "TestPluginRegistry::findPlugin() was called with PID \""
            << t_pid << "\" and version \"" << t_version << "\"!" << std::endl;
  throw std::bad_function_call();
}

void TestPluginRegistry::registerAlgorithm(AlgorithmFactory &t_factory) {
  Q_UNUSED(t_factory)
}
