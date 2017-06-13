#include "catch.hpp"

#include "nodetype.hpp"
#include "pluginapitest.hpp"
#include "pluginmanager.hpp"
#include "sodaconfig.hpp"

#include <QJsonObject>

using namespace soda;
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

const NodeType TestAlgorithm::TYPE = NodeType{"", "", ""};

const QJsonObject TestAlgorithm::getConfiguration() const {
  std::cerr << "Error: This is only a test stub without functionallity! "
               "TestAlgorithm::getConfiguration() was called. \""
            << std::endl;
  throw std::bad_function_call();
}

void TestAlgorithm::setConfiguration(const QJsonObject &t_configuration) {
  Q_UNUSED(t_configuration)
}

const char *TestAlgorithm::getSignal(int t_index) const {
  if (t_index == 0) {
    return SIGNAL(signal_imageReady(cv::Mat));
  }
  return "";
}

const char *TestAlgorithm::getSlot(int t_index) const {
  if (t_index == 0) {
    return SLOT(slot_process(cv::Mat));
  }
  return "";
}

void TestAlgorithm::run() {}

void TestAlgorithm::slot_process(cv::Mat) {}

const NodeType &TestAlgorithm::getType() const { return TYPE; }

const QString TestPlugin::getName() const { return "TestPlugin"; }

const QString TestPlugin::getDescription() const { return ""; }

const QString TestPlugin::getAuthor() const { return Soda_AUTHOR_SCHUMACB; }

const QString TestPlugin::getMaintainer() const { return Soda_AUTHOR_SCHUMACB; }

const QString TestPlugin::getURL() const { return Soda_URL; }

const std::string TestPlugin::getID() const { return TestPlugin_PID; }

const Version TestPlugin::getVersion() const { return m_version; }

void TestPlugin::onLoad(PluginRegistry &t_registry) { Q_UNUSED(t_registry) }

void TestPlugin::onUnload(PluginRegistry &t_registry) { Q_UNUSED(t_registry) }

void TestPlugin::setVersion(Version t_version) { m_version = t_version; }

void TestPluginRegistry::registerPlugin(Plugin &t_plugin) {
  std::cerr << "Error: This is only a test stub without functionallity! "
               "TestPluginRegistry::registerPlugin() was called with plugin \""
            << t_plugin.getName().toStdString() << "(" << t_plugin.getID()
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

void TestPluginRegistry::registerNodeFactory(NodeFactory &t_factory) {
  Q_UNUSED(t_factory)
}

QtNodes::DataModelRegistry *TestPluginRegistry::getDataModelRegistry() {
  return nullptr;
}
