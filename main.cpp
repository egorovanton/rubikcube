#include <iostream>
#include "generator/ScrambleGen.h"
#include "twister/cube.h"

//
// Created by alex on 2/4/17.
//
int main() {
    ScrambleGen simpleGen;
    std::cout << simpleGen.getNewScramble().join(", ").toStdString();
    Cube cube;
    cube.rotate("R");
}
