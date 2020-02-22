/*
 * @Name       kcp_tool
 * @Author    Robert Zhang
 * @E-mail    zhangzhiguo1207@163.com
 * @Date       2019-08-02
 */

#include "toast.h"

#include <QPropertyAnimation>
#include <QScreen>
#include <QGuiApplication>
#include <QPainter>
#include <QTimer>

Toast::Toast(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground, true);
}

Toast::~Toast()
{
}

void Toast::setText(const QString& text)
{
    ui.label->setText(text);
}

void Toast::showAnimation(int timeout /*= 2000*/)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    show();

    QTimer::singleShot(timeout, [&]
    {
        QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
        animation->setDuration(1000);
        animation->setStartValue(1);
        animation->setEndValue(0);
        animation->start();
        connect(animation, &QPropertyAnimation::finished, [&]
        {
            close();
            deleteLater();
        });
    });
}

void Toast::showTip(const QString& text, QWidget* parent /*= nullptr*/)
{
    Toast* toast = new Toast(parent);
    toast->setWindowFlags(toast->windowFlags() | Qt::WindowStaysOnTopHint);
    toast->setText(text);
    toast->adjustSize();

    QScreen* pScreen = QGuiApplication::primaryScreen();
    toast->move((pScreen->size().width() - toast->width()) / 2, pScreen->size().height() * 7 / 10);
    toast->showAnimation();
}

void Toast::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter paint(this);

   // paint.begin(this);
    auto kBackgroundColor = QColor(255, 255, 255);
    kBackgroundColor.setAlpha(0 * 255);
    paint.setRenderHint(QPainter::Antialiasing, true);
    paint.setPen(Qt::NoPen);
    paint.setBrush(QBrush(kBackgroundColor, Qt::SolidPattern));
    paint.drawRect(0, 0, width(), height());
 //   paint.end();
}
