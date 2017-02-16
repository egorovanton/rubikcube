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

        for (auto l:{FRONT, RIGHT, BACK, LEFT}) {
            auto r = getRight(l);
            auto const &corner = solver.getCube().getCubie(l, DOWN, r);
            auto const &tuple = solver.getCube().getCubie(DOWN, l);
            if (std::get<0>(tuple) != DOWN || std::get<1>(tuple) != l
                || std::get<0>(corner) != l || std::get<1>(corner) != DOWN || std::get<2>(corner) != r) {
                std::cout << "BROKEN\n" << simpleGen.getSeed() << "\n";
                std::cout << solver.getCube().print().toStdString();
                return 1;
            }

        }
    }
}
