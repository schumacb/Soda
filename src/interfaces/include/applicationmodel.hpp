#pragma once

#include <QReadWriteLock>
#include <QStringList>

#include "channel.hpp"
#include "frame.hpp"
#include "imagesource.hpp"
#include "datamodel.hpp"
namespace soda
{

class ApplicationModel : public DataModel
{
	Q_OBJECT

private:
	QReadWriteLock _imageLock;
        Image _image;
	QReadWriteLock _frameLock;
        Frame& _backFrame;
        Frame& _frontFrame;

public:
        ApplicationModel(QObject* parent = 0);
	~ApplicationModel();
		
    void getImage(Image& dest);
    void getChannelData(QVector<ChannelData>& data);
	
        Frame* requireFrame();
	void releaseFrame();

signals:
	void frameReady(Frame);
	void imageReady();

public slots:
        void updateImage(ImageSource* imageSource);
};

}
