#include "connectionwidget.h"

ConnectionWidget::ConnectionWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void ConnectionWidget::setStartWidget(QWidget *widget)
{
    m_startWidget = widget;
}

void ConnectionWidget::setEndWidget(QWidget *widget)
{
    m_endWidget = widget;
}

void ConnectionWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if (!m_startWidget || !m_endWidget)
        return;

    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(m_startWidget->mapTo(this, m_startWidget->rect().center()),
                     m_endWidget->mapTo(this, m_endWidget->rect().center()));
}
