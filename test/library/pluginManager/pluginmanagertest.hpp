#include <QObject>

#include "plugininterface.hpp"

#ifndef PLUGINMANAGERTEST_HPP
#define PLUGINMANAGERTEST_HPP

#define TestPlugin_PID "de.hochschule-trier.soda.test.testplugin"
#define TestPlugin_Version Version{1,0,0}

class TestPlugin : public QObject, public PluginInterface {
    Q_OBJECT
    Version m_version{TestPlugin_Version};
public:
    virtual const std::string getName() const { return "TestPlugin";}
    virtual const std::string getDescription() const {return "";}
    virtual const std::string getPid() const {return TestPlugin_PID;}
    virtual const Version getVersion() const {return m_version;}

    virtual void onLoad() {}
    virtual void onUnload() {}

    void setVersion(Version t_version) {m_version = t_version;}


};

#endif // PLUGINMANAGERTEST_HPP
