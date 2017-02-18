#include <iostream>
#include "generator/ScrambleGen.h"
#include "twister/cube.h"
#include "solver/solver.h"
#include <string>
#include <tuple>

//
// Created by alex on 2/4/17.
//

using namespace std;


int main() {

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
        QStringList prepResult = solver.getPreparedResult();
        cout << result.join(" ").toStdString() << endl;
        cout << prepResult.join(" ").toStdString() << endl;
        cout << solver.getCube().print().toStdString() << endl;
        for (auto f:{FRONT, RIGHT, BACK, LEFT}) {
            auto r = getRight(f);

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

                cout << "r = " << planeToString(r).toStdString() << endl;
                cout << "f = " << planeToString(f).toStdString() << endl;

                std::cout << "dCorner = " << printTuple(dCorner) << endl;
                std::cout << "down = " << printTuple(down) << endl;
                std::cout << "mid = " << printTuple(mid) << endl;
                std::cout << "upp = " << printTuple(upp) << endl;

                std::cout << solver.getCube().print().toStdString();
                return 1;
            }

        }
        break;
    }
}
