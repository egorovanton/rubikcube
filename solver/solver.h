//
// Created by Vetrier on 14/02/2017.
//

#ifndef RUBIKCUBE_SOLVER_H
#define RUBIKCUBE_SOLVER_H


#include "../twister/cube.h"

class Solver {
public:
    Solver(Cube cube);
    QStringList solve();

private:
    Cube cube;
};


#endif //RUBIKCUBE_SOLVER_H
