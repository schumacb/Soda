#pragma once

#include <QWidget>

namespace soda
{

class QPaintEvent;

class ImageView : public QWidget
{
    Q_OBJECT
public:
    explicit ImageView(QWidget *parent = nullptr);
    void painteEvent(QPaintEvent* paint_event);
signals:

public slots:
};

} // namespace soda
