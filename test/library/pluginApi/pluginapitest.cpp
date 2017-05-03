#include "catch.hpp"

#include "pluginmanager.hpp"

#include "pluginapitest.hpp"

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
