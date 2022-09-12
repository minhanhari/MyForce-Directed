#include <QApplication>
#include <QPalette>
#include "draw.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    Draw window;

    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::white);

    window.setAutoFillBackground(true);
    window.setPalette(pal);

    window.resize(500, 500);
    window.setWindowTitle("Force-Directed Layout");
    window.show();

    return app.exec();
}
