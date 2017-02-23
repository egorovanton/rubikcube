#include <iostream>
#include "../generator/ScrambleGen.h"
#include "../twister/cube.h"
#include "solver.h"
#include <string>
#include <tuple>

//
// Created by alex on 2/4/17.
//

using namespace std;


int main() {

    ScrambleGen simpleGen;
    std::cout << simpleGen.getSeed() << "\n";

    int i = 0;
    int dif = 0;
    int x = 3'000;

    while (++i < x) {
        Cube cube;
        const QStringList &list = simpleGen.getNewScramble();
        cout << i << endl;
        for (auto str: list) {
            cube.rotate(str);
        }
        //cout << cube.print().toStdString() << endl;
        Solver solverN(cube);
        Solver solverF2L(cube);

        auto F2Lres = solverF2L.getPreparedResultF2L();
        auto Nres = solverN.getPreparedResult();
        dif += Nres.length() - F2Lres.length();

        //cout << Nres.join(" ").toStdString() << endl;
        //cout << F2Lres.join(" ").toStdString() << endl;

        for (auto f:{FRONT, RIGHT, BACK, LEFT}) {
            auto r = getRight(f);

            auto const &dCorner = solverF2L.getCube().getCubie(f, DOWN, r);
            auto const &down = solverF2L.getCube().getCubie(DOWN, f);
            auto const &mid = solverF2L.getCube().getCubie(f, r);
            auto const &upp = solverF2L.getCube().getCubie(f, UP);
            auto const &uCorner = solverF2L.getCube().getCubie(f, UP, r);

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

                std::cout << solverF2L.getCube().print().toStdString();
                return 1;
            }

        }
    }
    cout << dif/x;
}