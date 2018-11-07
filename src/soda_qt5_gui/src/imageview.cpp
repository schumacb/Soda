#include "imageview.h"

#include <QPaintEvent>
#include <QPainter>

namespace soda
{

ImageView::ImageView(QWidget *parent) : QWidget(parent)
{

}

void ImageView::painteEvent(QPaintEvent* paint_event)
{
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::black));
    painter.drawRect(0,0, width(), height());

}

} // namespace soda
