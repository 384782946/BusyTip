#include "busytipwidget.h"

#include <QPainter>
#include <QtMath>
#include <QPropertyAnimation>

BusyTipWidget::BusyTipWidget(QWidget *parent) : QWidget(parent)
{
    setWindowFlag(Qt::WindowStaysOnTopHint);

    setAttribute(Qt::WA_TranslucentBackground,true);

    //setWindowModality(Qt::WindowModal);

    this->setFixedSize(200,140);

    m_animation = new QPropertyAnimation(this, "offset");
    m_animation->setDuration(1400);
    m_animation->setLoopCount(-1);//无限循环

    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);

    connect(m_timer,&QTimer::timeout,this,[=](){
        if(this->isVisible()){
            this->hide();
        }
    });

    hide();
}

void BusyTipWidget::show(int msec)
{
    auto parent = parentWidget();
    if(parent) {
        auto rect = parent->rect();
        this->move(rect.width()/2-this->width()/2,rect.height()/2-this->height()/2);
    }

    if(m_style == Round) {
        m_animation->setStartValue(0);
        m_animation->setEndValue(350);

        QEasingCurve curve(QEasingCurve::InOutCubic);
        m_animation->setEasingCurve(curve);
    }else if(m_style == Dot) {
        m_animation->setStartValue(0);
        m_animation->setEndValue(3);
        m_animation->setEasingCurve(QEasingCurve());
    }

    if(msec > 0) {
        m_timer->setInterval(msec);
        m_timer->start();
    }else{
        m_timer->stop();
    }

    m_animation->start();
    QWidget::show();
}

void BusyTipWidget::hide()
{
    if(m_timer->isActive()) {
        m_timer->stop();
    }

    if(QAbstractAnimation::Running == m_animation->state()) {
        m_animation->stop();
    }
    QWidget::hide();
}

void BusyTipWidget::setTip(QString tip)
{
    if (m_tip == tip)
        return;

    m_tip = tip;
    this->update();
}

void BusyTipWidget::drawDot(QPainter& painter)
{
    QPointF p1,p2,p3,p4;
    int xCenter = rect().width()/2;
    int yCenter = rect().height()/2 - 20;
    p1.setX(xCenter - 26);
    p1.setY(yCenter);

    p2.setX(xCenter - 8);
    p2.setY(yCenter);

    p3.setX(xCenter + 8);
    p3.setY(yCenter);

    p4.setX(xCenter + 26);
    p4.setY(yCenter);

    int  size1,size2,size3,size4;
    int base = 2;
    int step = 1;
    size1 = qAbs(0-m_offset)%3*step +base;
    size2 = qAbs(1-m_offset)%3*step +base;
    size3 = qAbs(2-m_offset)%3*step +base;
    size4 = qAbs(3-m_offset)%3*step +base;

    painter.setBrush(Qt::white);
    painter.drawEllipse(p1,size1,size1);
    painter.drawEllipse(p2,size2,size2);
    painter.drawEllipse(p3,size3,size3);
    painter.drawEllipse(p4,size4,size4);
}

void BusyTipWidget::drawRound(QPainter& painter)
{
    QPointF center = rect().center();
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::white);
    painter.setBrush(Qt::transparent);
    painter.setPen(pen);
    int radius = 15;
    QRect arcRect(center.x()-radius,center.y()-radius-20,radius*2,radius*2);
    painter.drawArc(arcRect,m_offset * 16,16 *((m_offset + 360)%360));
}

BusyTipWidget::AnimStyle BusyTipWidget::style() const
{
    return m_style;
}

void BusyTipWidget::setStyle(const AnimStyle &style)
{
    m_style = style;
}

void BusyTipWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    QColor color(0,0,0,200);
    painter.setPen(color);
    painter.setBrush(color);
    auto rect = this->rect();
    painter.drawRoundRect(this->rect(),10,10);

    painter.setPen(Qt::white);

    QRect textRect = rect;
    textRect.adjust(0,height()* 0.35,0,0);

    painter.drawText(textRect,Qt::AlignCenter,tip());

    if(m_style == Round){
        drawRound(painter);
    }else if(m_style == Dot) {
        drawDot(painter);
    }

    QWidget::paintEvent(event);
}

int BusyTipWidget::offset() const
{
    return m_offset;
}

void BusyTipWidget::setOffset(int offset)
{
    if(m_offset == offset){
        return;
    }
    m_offset = offset;
    emit offsetChanged(offset);
    this->update(0,0,this->width(),this->height()/2);
}
