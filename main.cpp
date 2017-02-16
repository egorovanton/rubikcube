#include <iostream>
#include "generator/ScrambleGen.h"
#include "twister/cube.h"
#include "solver/solver.h"

//
// Created by alex on 2/4/17.
//
int main() {
    using std::cout;
    using std::endl;

    ScrambleGen simpleGen;
    while (true) {
        Cube cube;
        //std::cout << simpleGen.getSeed() << "\n";
        const QStringList &list = simpleGen.getNewScramble();
        cout << list.join(" ").toStdString() << endl;
        for (auto str: list) {
            cube.rotate(str);
        }
        //cout << cube.print().toStdString() << endl;
        Solver solver(cube);
        QStringList result = solver.solve();
        cout << result.join(" ").toStdString() << endl;

        for (auto q:{FRONT, RIGHT, BACK, LEFT}) {
            const std::tuple<PlaneType, PlaneType> &tuple = solver.getCube().getCubie(DOWN, q);
            if (std::get<0>(tuple) != DOWN || std::get<1>(tuple) != q) {
                std::cout << "BROKEN\n" << simpleGen.getSeed() << "\n";
                std::cout << solver.getCube().print().toStdString();
                return 1;
            }
        }

    }
}
