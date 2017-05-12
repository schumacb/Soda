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
  // AlgorithmNode interface
public:
  const QJsonObject &getConfiguration() const override;
  void setConfiguration(const QJsonObject &configuration) override;
  QString getID() override;
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
  virtual const QString getName() const override;
  virtual const QString getDescription() const override;
  virtual const std::string getPid() const override;
  virtual const Version getVersion() const override;
  virtual void onLoad(pluginapi::PluginRegistry &t_registry) override;
  virtual void onUnload(pluginapi::PluginRegistry &t_registry) override;
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
