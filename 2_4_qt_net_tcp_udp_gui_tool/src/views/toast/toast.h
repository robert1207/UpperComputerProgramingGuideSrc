#ifndef TOAST_H
#define TOAST_H

#include <QtWidgets/QWidget>
#include "ui_toast.h"

class Toast : public QWidget
{
    Q_OBJECT

public:
    Toast(QWidget *parent = Q_NULLPTR);
    ~Toast();

    void setText(const QString& text);

    void showAnimation(int timeout = 2000);

public:
    static void showTip(const QString& text, QWidget* parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::ToastClass ui;
};

#endif // TOAST_H
