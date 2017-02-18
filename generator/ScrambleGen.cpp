#include <iostream>
#include <ctime>
#include "ScrambleGen.h"

//
// Created by alex on 2/4/17.
//

const QStringList ScrambleGen::twists = {
    "L",  "R",  "U",  "D",  "F",  "B",
    "L'", "R'", "U'", "D'", "F'", "B'",
    "L2", "R2", "U2", "D2", "F2", "B2"
};

ScrambleGen::ScrambleGen() {
    seed = (uint) time(NULL);
    qsrand(seed);
}


bool ScrambleGen::checkNextTwist(int currentPosition, int nextPosition) {
    return currentPosition % 6 == nextPosition % 6;
}

QStringList ScrambleGen::getNewScramble() {
    QStringList result;
    int cur = qrand() % twists.length();
    int next = 0;
    result << twists[cur];
    for (int i = 1; i < 25; i++) {
        while (checkNextTwist(cur, (next = qrand() % twists.length())));
        result << twists[next];
        cur = next;
    }
    return result;
}
