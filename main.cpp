#include <iostream>
#include "generator/ScrambleGen.h"
#include "twister/cube.h"
#include "solver/solver.h"
#include <string>
#include <tuple>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QSet>
#include <QDebug>

QTextStream& qStdOut() {
    static QTextStream ts(stdout);
    return ts;
}

QTextStream& qStdIn() {
    static QTextStream ts(stdin, QIODevice::ReadOnly);
    return ts;
}

void printRecourse(const QString &str) {
    QFile file(str);
    if (file.open(QIODevice::ReadOnly)) {
        qStdOut() << QTextStream(&file).readAll();
        qStdOut().flush();
    }
}

bool valid(const QStringList& list) {
    for (const QString &str : list) {
        if (!Direction::validDirecions.contains(str.toUpper())) {
            qWarning() << "Unknown: " << str;
            return false;
        }
    }

    return true;
}

void printSolution(const QStringList& scramble) {
    Cube c;
    c.rotate(scramble);
    Solver solver(c);
    qStdOut() << solver.getPreparedResultF2L().join(" ") << "\n";
}

int main() {
    printRecourse(":txt/welcome");

    ScrambleGen scrambler;
    QStringList lastScramble;
    while (true) {
        qStdOut().flush();

        QStringList input = qStdIn().readLine().split(QRegExp("\\s"), QString::SkipEmptyParts);

        if (input.length() == 0) {
            continue;
        }

        if (input[0] == "help" || input[0] == "?") {
            printRecourse(":/txt/help");
            continue;
        }

        if (input[0] == "exit") {
            break;
        }

        if (input[0] == "scramble") {
            lastScramble = scrambler.getNewScramble();
            qStdOut() << lastScramble.join(" ") << "\n";
            continue;
        }

        if (input[0] == "solve")  {
            if (input.length() == 1) {
                qStdOut() << "input scramble to solve (type help solve for more infomation)\n";
                continue;
            }

            input.removeFirst();
            if (input[0] == "it") {
                if (lastScramble.isEmpty()){
                    qStdOut() << "no scramble was generated\n";
                } else {
                    printSolution(lastScramble);
                }
            }  else {
                if (valid(input)) {
                    printSolution(input);
                } else {
                  qStdOut() << "invalid scramble\n";
                  qStdOut() << "valid scrambles are any combination of : \n";
                  qStdOut() << ScrambleGen::twists.join(" ") << "\n";
                }
            }
            continue;
        }
        qStdOut() << "Unknown command: " << input[0] << "\n";

    }
}
