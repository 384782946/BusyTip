#ifndef BUSYTIPWIDGET_H
#define BUSYTIPWIDGET_H

#include <QWidget>
#include <QTimer>

class QPropertyAnimation;

class BusyTipWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int offset READ offset WRITE setOffset NOTIFY offsetChanged)
public:

    enum AnimStyle{
        Round,
        Dot
    };

    explicit BusyTipWidget(QWidget *parent = nullptr);

    QString tip() const
    {
        return m_tip;
    }

    void show(int msec = -1);
    void hide();

    int offset() const;
    void setOffset(int offset);

    void setTip(QString tip);

    AnimStyle style() const;
    void setStyle(const AnimStyle &style);

signals:
    void offsetChanged(int offset);

protected:
    void paintEvent(QPaintEvent* event) override;

    void drawDot(QPainter& painter);

    void drawRound(QPainter& painter);

private:
    QPropertyAnimation* m_animation = nullptr;
    QTimer* m_timer = nullptr;
    QString m_tip;
    int m_offset = 0;
    AnimStyle m_style = Round;
};

#endif // BUSYTIPWIDGET_H
