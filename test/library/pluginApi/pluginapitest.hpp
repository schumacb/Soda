#pragma once

#include <functional>

#include <QObject>

#include "plugin.hpp"
#include "pluginregistry.hpp"
#include "version.hpp"

#define TestPlugin_PID "de.hochschule-trier.soda.test.testplugin"
#define TestPlugin_Version                                                     \
  Version {                                                                    \
    PluginApi_VERSION_MAJOR, PluginApi_VERSION_MINOR, PluginApi_VERSION_PATCH  \
  }

class TestPlugin : public QObject, public Plugin {
  Q_OBJECT
  Q_INTERFACES(Plugin)
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
  virtual void registerPlugin(Plugin &t_plugin) override {
    std::cerr
        << "Error: This is only a test stub without functionallity! "
           "TestPluginRegistry::registerPlugin() was called with plugin \""
        << t_plugin.getName() << "(" << t_plugin.getPid() << ")\"."
        << std::endl;
    throw std::bad_function_call();
  }

  virtual Plugin *findPlugin(const std::string t_pid,
                             const Version t_version) override {
    std::cerr << "Error: This is only a test stub without functionallity! "
                 "TestPluginRegistry::findPlugin() was called with PID \""
              << t_pid << "\" and version \"" << t_version << "\"!"
              << std::endl;
    throw std::bad_function_call();
  }
};
