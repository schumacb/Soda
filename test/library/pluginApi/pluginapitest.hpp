#pragma once

#include <functional>

#include <QObject>

#include <opencv2/opencv.hpp>

#include "imagefilter.hpp"
#include "plugin.hpp"
#include "pluginregistry.hpp"
#include "version.hpp"

#define TestPlugin_PID "de.hochschule-trier.soda.test.testplugin"
#define TestPlugin_Version                                                     \
  Version {                                                                    \
    PluginApi_VERSION_MAJOR, PluginApi_VERSION_MINOR, PluginApi_VERSION_PATCH  \
  }

namespace soda {
namespace pluginapi {

class TestAlgorithm : public QObject, public ImageFilter {
  Q_OBJECT
public:
  Plugin *m_plugin;
  // AlgorithmNode interface
  const QJsonObject &getConfiguration() const override;
  void setConfiguration(const QJsonObject &configuration) override;
  const QString getID() const override;
  pluginapi::Plugin *getPlugin() const override;
  const char *getSignal(int index) const override;
  const char *getSlot(int index) const override;
public slots:
  void run() override;
  // ImageSource interface
signals:
  void signal_imageReady(cv::Mat) override;
  // ImageProcessor interface
public slots:
  void slot_process(cv::Mat) override;
};

class TestPlugin : public QObject, public Plugin {
  Q_OBJECT
  Q_INTERFACES(soda::pluginapi::Plugin)
  Version m_version = TestPlugin_Version;

public:
  const QString getName() const override;
  const QString getDescription() const override;
  const QString getAuthor() const override;
  const QString getMaintainer() const override;
  const QString getURL() const override;
  const std::string getID() const override;
  const Version getVersion() const override;
  void onLoad(pluginapi::PluginRegistry &t_registry) override;
  void onUnload(pluginapi::PluginRegistry &t_registry) override;
  void setVersion(Version t_version);
};

class TestPluginRegistry : public PluginRegistry {
  // PluginRegistry interface
public:
  virtual void registerPlugin(Plugin &t_plugin) override;
  virtual Plugin *findPlugin(const std::string &t_pid,
                             const Version &t_version) override;
  void registerAlgorithm(AlgorithmFactory &factory) override;
};

} // pluginapi
} // soda
