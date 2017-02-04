#include <QVector>
#include <QString>
#include <QStringList>

//
// Created by alex on 2/4/17.
//

#ifndef RUBIKCUBE_SCRAMBLEGEN_H
#define RUBIKCUBE_SCRAMBLEGEN_H


class ScrambleGen {
protected:
    QVector<QString> twists;
    bool checkNextTwist(int currentPosition, int nextPosition);

public:
    ScrambleGen();
    QStringList getNewScramble();
};


#endif //RUBIKCUBE_SCRAMBLEGEN_H
