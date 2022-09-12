#pragma once

#include <QWidget>

class Draw : public QWidget
{

public:
    Draw(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void drawGraph(QPainter *qp);
};