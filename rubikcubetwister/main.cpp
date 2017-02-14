#include <QCoreApplication>
#include "direction.h"
#include <iostream>
#include "cube.h"
#include "utils.h"
#include <QDebug>
#include <random>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //    cout << (- 2) % 6;


    //    Cube cube;

    //    cout << "initial cube:" << endl << endl;
    //    cout << cube.print().toStdString() << endl;

    //    QVector<QString> directions = {"F'", "D", "F'", "D'", "L", "F2", "D2", "L2", "F2", "L", "B2", "R", "L", "U'", "L2", "F", "D'", "F2", "D", "B2", "U'", "L'", "U2", "B", "D"};


    //    for (auto str: directions) {
    //        cout << "direction : " << str.toStdString() << endl;
    ////        Direction dir(str);
    //        cube.rotate(str);
    //        cout << cube.print().toStdString() << endl << endl;
    //    }

    //    cout << cube.print().toStdString() << endl;

    //    default_random_engine gen;
    //    uniform_int_distribution<int> randomPlane(0, 5);
    //    uniform_int_distribution<int> randomInt(0, 3);
    //    for (int i = 0; i < 10; ++i) {
    //        PlaneType plane = (PlaneType) randomPlane(gen);
    //        QVector<PlaneType> neighbours = Direction(plane, CLOCKWISE).getNeighbours();
    //        int neighbourIndex = randomInt(gen);
    //        PlaneType plane1 = neighbours[neighbourIndex];
    //        PlaneType plane2 = neighbours[(neighbourIndex + 1) % 4];

    //        cout << "plane A = " << plane << endl;
    //        cout << "plane B = " << plane1 << endl;
    //        cout << "plane C = " << plane2 << endl;

    //        int x1, x2, x3;
    //        tuple<PlaneType, PlaneType> p;
    //        tuple<PlaneType, PlaneType, PlaneType> t;

    //        p = cube.getCubie(plane, plane1);
    //        cout << "between A and B is " << get<0>(p) << " " << get<1>(p) << endl;
    //        p = cube.getCubie(plane1, plane2);
    //        cout << "between B and C is " << get<0>(p) << " " << get<1>(p) << endl;
    //        p = cube.getCubie(plane2, plane);
    //        cout << "between C and A is " << get<0>(p) << " " << get<1>(p) << endl;
    //        t = cube.getCubie(plane, plane1, plane2);
    //        cout << "between A, B and C is " << get<0>(t) << " " << get<1>(t) <<  " " << get<2>(t) << endl;
    //        cout << endl << endl;
    //    }


    //    QVector<int> vec = {1, 2, 3};
    //    toString(vec);
    cout << toString(QVector<int>{1, 2, 3}).toStdString() << endl;


    cout << toString(Direction("M").getNeighbours(), [](PlaneType p){return QString::number((int) p);}).toStdString() << endl;
    cout << toString(Direction("S").getNeighbours(), [](PlaneType p){return QString::number((int) p);}).toStdString() << endl;
    cout << toString(Direction("E").getNeighbours(), [](PlaneType p){return QString::number((int) p);}).toStdString() << endl;

    Cube cube;
    cube.turnLeft();
    cube.turnRight();
    cube.turnHalf();
    cout << cube.print().toStdString() << endl;
    cube.rotate("M2");
    cube.rotate("S2");
    cube.rotate("E2");
    cout << cube.print().toStdString() << endl;
    return a.exec();
}
