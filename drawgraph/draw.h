#pragma once

#include <QWidget>
#include <QSvgGenerator>

class Draw : public QWidget
{

public:
    Draw(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void drawGraph(QPainter *qp);
    void renderSvgFile();

private:
    QString path;
    QSvgGenerator generator;
};