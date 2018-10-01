#pragma once

#include <memory>

#include "channel.hpp"
#include <QVector>

namespace soda
{

class DataModel : public QObject
{
	Q_OBJECT

public:
	DataModel(QObject *parent);
	~DataModel();

	const QVector<chan_ptr> *getChannels() const;
	const chan_ptr getChannel(int idx) const;
	int getNumChannels() const;

	bool readChannels(QDataStream &in);
	void writeChannels(QDataStream &out) const;

	public slots:
		void addChannel();
		void addChannel(chan_ptr chan);
		void removeChannel(int idx);
		void setMinHue(int idx, int hue);
		void setMaxHue(int idx, int hue);
		void setMinSat(int idx, int sat);
		void setMaxSat(int idx, int sat);
		void setMinVal(int idx, int val);
		void setMaxVal(int idx, int val);
		void setMinArea(int idx, int area);
		void setMaxBlobs(int idx, int blobs);
		void setName(int idx, QString name);

	signals:
		void channelAdded(int idx);
		void channelRemoved(int idx);
		void channelRenamed(int idx);
		void minHueChanged(int  idx);
		void maxHueChanged(int  idx);
		void minSatChanged(int  idx);
		void maxSatChanged(int  idx);
		void minValChanged(int  idx);
		void maxValChanged(int  idx);
		void minAreaChanged(int  idx);
		void maxBlobsChanged(int  idx);

private:
	QVector<chan_ptr> _channels;
};

} // namespace soda
