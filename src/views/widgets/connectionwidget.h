#ifndef CONNECTIONWIDGET_H
#define CONNECTIONWIDGET_H

#include <QWidget>
#include <QPainter>

class ConnectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConnectionWidget(QWidget *parent = nullptr);
    void setStartWidget(QWidget *widget);
    void setEndWidget(QWidget *widget);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QWidget *m_startWidget;
    QWidget *m_endWidget;

};

#endif // CONNECTIONWIDGET_H
