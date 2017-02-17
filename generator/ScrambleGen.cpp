#include <iostream>
#include "ScrambleGen.h"

//
// Created by alex on 2/4/17.
//

ScrambleGen::ScrambleGen() : twists() {
    seed = 1487347187;(uint) time(NULL);
    qsrand(seed);
    twists << "L" << "R" << "U" << "D" << "F" << "B"
           << "L'" << "R'" << "U'" << "D'" << "F'" << "B'"
           << "L2" << "R2" << "U2" << "D2" << "F2" << "B2";
}


bool ScrambleGen::checkNextTwist(int currentPosition, int nextPosition) {
    return currentPosition % 6 == nextPosition % 6;
}

QStringList ScrambleGen::getNewScramble() {
    QStringList result;
    int cur = qrand() % twists.length();
    int next = 0;
    result << twists[cur];
    for (int i = 1; i < 5; i++) {
        while (checkNextTwist(cur, (next = qrand() % twists.length())));
        result << twists[next];
        cur = next;
    }
    return result;
}
