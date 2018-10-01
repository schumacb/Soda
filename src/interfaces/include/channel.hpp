#pragma once

#include <QObject>
#include <memory>

#include "color.hpp"

namespace soda
{

class Channel : public QObject {
        Q_OBJECT

private:
        Q_DISABLE_COPY(Channel)
        bool _valid;
        int _minHue;
        int _maxHue;
        int _minSat;
        int _maxSat;
        int _minVal;
        int _maxVal;
        int _minArea;
        int _maxBlobs;
        QString _name;
        static int _clamp(int v, int l, int h) { return (v<l?l:(v>h?h:v));}

        void _setInvalid();

public:
        static const int VERSION = 1;
        static const int MIN_HUE = 0;
        static const int MIN_SAT = 0;
        static const int MIN_VAL = 0;

        static const int MAX_HUE = 180;
        static const int MAX_SAT = 255;
        static const int MAX_VAL = 255;

        Channel(QObject *parent = 0, bool valid = true);

        void setMinHue(int minHue);
        void setMaxHue(int maxHue);
        void setMinSat(int minSat);
        void setMaxSat(int maxSat);
        void setMinVal(int minVal);
        void setMaxVal(int maxVal);
        void setName(QString name);

        void setMinArea(int minArea);
        void setMaxBlobs(int maxBlobs);

        unsigned int minHue() const;
        unsigned int maxHue() const;
        unsigned int minSat() const;
        unsigned int maxSat() const;
        unsigned int minVal() const;
        unsigned int maxVal() const;

        Color color() const;
        QString name() const;
        bool isValid() const;

        unsigned int minArea() const;
        unsigned int maxBlobs() const;

        bool read(QDataStream &in);
        void write(QDataStream &out) const;

        signals:
                void minHueChanged(int minHue);
                void maxHueChanged(int maxHue);
                void minSatChanged(int minSat);
                void maxSatChanged(int maxSat);
                void minValChanged(int minVal);
                void maxValChanged(int maxVal);
                void nameChanged(QString name);
                void minAreaChanged(int minArea);
                void maxBlobsChanged(int maxBlobs);
};

typedef std::shared_ptr<Channel> chan_ptr;

} // namespace soda

