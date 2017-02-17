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
        std::cout << simpleGen.getSeed() << "\n";
        const QStringList &list = simpleGen.getNewScramble();
        cout << list.join(" ").toStdString() << endl;
        for (auto str: list) {
            cube.rotate(str);
        }
        //cout << cube.print().toStdString() << endl;
        Solver solver(cube);
        QStringList result = solver.solve();
        cout << result.join(" ").toStdString() << endl;

        for (auto f:{FRONT, RIGHT, BACK, LEFT}) {
            auto r = getRight(f);
            //auto l = getLeft(f);

            auto const &dCorner = solver.getCube().getCubie(f, DOWN, r);
            auto const &down = solver.getCube().getCubie(DOWN, f);
            auto const &mid = solver.getCube().getCubie(f, r);
            auto const &upp = solver.getCube().getCubie(f, UP);
            auto const &uCorner = solver.getCube().getCubie(f, UP, r);

            if (std::get<0>(down) != DOWN || std::get<1>(down) != f
                || std::get<0>(dCorner) != f || std::get<1>(dCorner) != DOWN || std::get<2>(dCorner) != r
                || std::get<0>(mid) != f || std::get<1>(mid) != r
                || std::get<0>(upp) != f || std::get<1>(upp) != UP
                || std::get<0>(uCorner) != f || std::get<1>(uCorner) != UP || std::get<2>(uCorner) != r) {
                std::cout << "BROKEN\n" << simpleGen.getSeed() << "\n";
                std::cout << solver.getCube().print().toStdString();
                return 1;
            }

        }
    }
}
