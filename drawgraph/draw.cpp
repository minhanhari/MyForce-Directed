#include <QPainter>
#include "draw.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>

using namespace std;

bool performCommand(QPainter *qp, const vector<string> &args)
{
    if (args.empty())
        return false;

    if (args[0] == "v" || args[0] == "vertex")
    {
        if (args.size() != 4)
        {
            cerr << "Wrong number of arguments vertex" << endl;
            return false;
        }

        int x = stoi(args[2]), y = stoi(args[3]);

        QColor color;
        char category[3];
        strncpy(category, args[1].c_str(), 3);
        printf("%s\n", category);
        if (strstr(category, "EXT"))
            color = QColor::fromRgb(18, 162, 86);
        else if (strstr(category, "EST"))
            color = QColor::fromRgb(222, 126, 170);
        else if (strstr(category, "AGR"))
            color = QColor::fromRgb(233, 126, 30);
        else if (strstr(category, "CSN"))
            color = QColor::fromRgb(35, 142, 199);
        else if (strstr(category, "OPN"))
            color = QColor::fromRgb(238, 237, 105);
        else
            color = Qt::red;
        QBrush brush(color);
        qp->setBrush(brush);
        QPen pen(Qt::black, 0, Qt::SolidLine);
        qp->setPen(pen);
        qp->drawEllipse(x - 14, y - 14, 28, 28);
        QFont font;
        font.setPointSize(6);
        qp->setFont(font);
        qp->drawText(x + 14, y + 14, args[1].c_str());
        return true;
    }

    if (args[0] == "e" || args[0] == "edge")
    {
        if (args.size() != 5)
        {
            cerr << "Wrong number of arguments vertex" << endl;
            return false;
        }
        int x1 = stoi(args[1]), y1 = stoi(args[2]);
        int x2 = stoi(args[3]), y2 = stoi(args[4]);

        QPen pen(Qt::lightGray, 2, Qt::SolidLine);
        qp->setPen(pen);
        qp->drawLine(x1, y1, x2, y2);

        return true;
    }

    cerr << "Invalid command '" << args[0] << "'" << endl;
    return false;
}

Draw::Draw(QWidget *parent)
    : QWidget(parent)
{
}

void Draw::paintEvent(QPaintEvent *e)
{

    Q_UNUSED(e);

    QPainter qp(this);
    drawGraph(&qp);
}

void Draw::drawGraph(QPainter *qp)
{
    ifstream GraphFile("../out_graph.txt");

    if (GraphFile.is_open())
    {
        printf("File opened successfully.\n");
    }
    else
    {
        printf("Error loading file.\n");
    }

    for (string line; getline(GraphFile, line);)
    {
        if (line.empty())
            break;

        istringstream iss(line);
        vector<string> args;

        for (string str; iss.good();)
        {
            iss >> str;
            args.emplace_back(str);
        }

        if (!performCommand(qp, args))
            exit(1);
    }

    GraphFile.close();

    cout << "Task completed successfully" << endl;
}