#include <QCoreApplication>
#include "direction.h"
#include <iostream>
#include "cube.h"
#include <QDebug>
#include <random>

using namespace std;

int main(int argc, char *argv[])
{
//    cout << (- 2) % 6;


    Cube cube;

    cout << "initial cube:" << endl << endl;
    cout << cube.print().toStdString() << endl;

    QVector<QString> directions = {"F'", "D", "F'", "D'", "L", "F2", "D2", "L2", "F2", "L", "B2", "R", "L", "U'", "L2", "F", "D'", "F2", "D", "B2", "U'", "L'", "U2", "B", "D"};

    cout << "directions : " << toString(directions, [](QString x){return x;}).toStdString() << endl;
    for (auto str: directions) {
        cout << "direction : " << str.toStdString() << endl;
//        Direction dir(str);
        cube.rotate(str);
        cout << cube.print().toStdString() << endl << endl;
    }

    cout << cube.print().toStdString() << endl;

    default_random_engine gen;
    uniform_int_distribution<int> randomPlane(0, 5);
    uniform_int_distribution<int> randomInt(0, 3);
    for (int i = 0; i < 10; ++i) {
        PlaneType plane = (PlaneType) randomPlane(gen);
        QVector<PlaneType> neighbours = Direction(plane, CLOCKWISE).getNeighbours();
        int neighbourIndex = randomInt(gen);
        PlaneType plane1 = neighbours[neighbourIndex];
        PlaneType plane2 = neighbours[(neighbourIndex + 1) % 4];

        cout << "plane A = " << planeToString(plane).toStdString() << endl;
        cout << "plane B = " << planeToString(plane1).toStdString() << endl;
        cout << "plane C = " << planeToString(plane2).toStdString() << endl;

        int x1, x2, x3;
        tuple<PlaneType, PlaneType> p;
        tuple<PlaneType, PlaneType, PlaneType> t;

        p = cube.getCubie(plane, plane1);
        cout << "between A and B is "
             << planeToString(get<0>(p)).toStdString() << " "
             << planeToString(get<1>(p)).toStdString() << endl;
        p = cube.getCubie(plane1, plane2);
        cout << "between B and C is "
             << planeToString(get<0>(p)).toStdString() << " "
             << planeToString(get<1>(p)).toStdString() << endl;
        p = cube.getCubie(plane2, plane);
        cout << "between C and A is "
             << planeToString(get<0>(p)).toStdString() << " "
             << planeToString(get<1>(p)).toStdString() << endl;
        t = cube.getCubie(plane, plane1, plane2);
        cout << "between A, B and C is "
             << planeToString(get<0>(t)).toStdString() << " "
             << planeToString(get<1>(t)).toStdString() <<  " " << get<2>(t) << endl;
        cout << endl << endl;
    }

    cout << ".turnLeft();" << endl;
    cube.turnLeft();
    cout << cube.print().toStdString() << endl << endl;
    for (int i = 0; i < 10; ++i) {
        PlaneType plane = (PlaneType) randomPlane(gen);
        QVector<PlaneType> neighbours = Direction(plane, CLOCKWISE).getNeighbours();
        int neighbourIndex = randomInt(gen);
        PlaneType plane1 = neighbours[neighbourIndex];
        PlaneType plane2 = neighbours[(neighbourIndex + 1) % 4];

        cout << "plane A = " << planeToString(plane).toStdString() << endl;
        cout << "plane B = " << planeToString(plane1).toStdString() << endl;
        cout << "plane C = " << planeToString(plane2).toStdString() << endl;

        int x1, x2, x3;
        tuple<PlaneType, PlaneType> p;
        tuple<PlaneType, PlaneType, PlaneType> t;

        p = cube.getCubie(plane, plane1);
        cout << "between A and B is "
             << planeToString(get<0>(p)).toStdString() << " "
             << planeToString(get<1>(p)).toStdString() << endl;
        p = cube.getCubie(plane1, plane2);
        cout << "between B and C is "
             << planeToString(get<0>(p)).toStdString() << " "
             << planeToString(get<1>(p)).toStdString() << endl;
        p = cube.getCubie(plane2, plane);
        cout << "between C and A is "
             << planeToString(get<0>(p)).toStdString() << " "
             << planeToString(get<1>(p)).toStdString() << endl;
        t = cube.getCubie(plane, plane1, plane2);
        cout << "between A, B and C is "
             << planeToString(get<0>(t)).toStdString() << " "
             << planeToString(get<1>(t)).toStdString() << " "
             << planeToString(get<2>(t)).toStdString() << endl;
        cout << endl << endl;
    }
}
