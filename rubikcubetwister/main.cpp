#include <QCoreApplication>
#include "direction.h"
#include <iostream>
#include "cube.h"
#include "utils.h"
#include <QDebug>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    cout << (- 2) % 6;


    Cube cube;

    cout << "initial cube:" << endl << endl;
    cout << cube.print().toStdString() << endl;

    QVector<QString> directions = {"F", "B2", "L\'"};


    for (auto str: directions) {
        cout << "direction : " << str.toStdString() << endl;
        Direction dir(str);
        cube.rotate(dir);
        cout << cube.print().toStdString() << endl << endl;
    }

    cout << cube.print().toStdString() << endl;

    return a.exec();
}
