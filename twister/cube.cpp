#include "cube.h"
#include "QDebug"
#include <iostream>


QVector<QVector<QVector<int> > > Cube::getMatrix() const {
    return matrix;
}

bool isRow(Cube::LineType line) {
    return line > Cube::NOTHING && line < Cube::LEFT_COLUMN;
}

QVector<int> Cube::getLine(Cube::LineType line, PlaneType plane) const {
    QVector<int> result = getRawLine(line, plane);
    if (plane > 2) {
        std::reverse(result.begin(), result.end());
    }
    return result;
}

void Cube::turnLeft() {
    rotate(UP, CLOCKWISE);
    rotate(EQUATOR, COUNTER_CLOCKWISE);
    rotate(DOWN, COUNTER_CLOCKWISE);
}

void Cube::turnRight() {
    rotate(UP, COUNTER_CLOCKWISE);
    rotate(EQUATOR, CLOCKWISE);
    rotate(DOWN, CLOCKWISE);
}

void Cube::turnHalf() {
    rotate(UP, HALF_TURN);
    rotate(EQUATOR, HALF_TURN);
    rotate(DOWN, HALF_TURN);
}

QString Cube::print() const {

    QList<QString> result;

    for (auto row: matrix[UP]) {
        result.append("   " + vectorToString(row));
    }

    for (auto row: QVector<LineType>{TOP_ROW, CENTER_ROW, BOTTOM_ROW}) {
        QString line = "";
        for (auto plane: QVector<PlaneType>{LEFT, FRONT, RIGHT, BACK}) {
            line += vectorToString(getLine(row, plane));
        }
        result.append(line);
    }

    for (int i = 2; i > -1; --i) {
        result.append("   " + vectorToString(matrix[DOWN][i]));
    }

    result.append("");
    return result.join("\n");
}

QVector<int> Cube::getRawLine(LineType line, PlaneType plane) const {
    if (line == NOTHING) {
        qWarning("Cube::getRawLine(Cube::LineType, PlaneType)");
        qWarning("\tLineType is NOTHING");

        return QVector<int>();
    }

    QVector<int> result(3);

    int lineNumber = (static_cast<int>(line) - 1) % 3;
    int row = isRow(line);
    int column = 1 - row;

    for (int i = 0; i < 3; ++i) {
        result[i] = matrix[plane][lineNumber * row + i * column][lineNumber * column + i * row];
    }

    return result;

}

std::tuple<PlaneType, PlaneType> Cube::getCubie(PlaneType plane1, PlaneType plane2) const {
    return std::make_tuple((PlaneType) getRawLine(RELATION_TABLE[plane1][plane2], plane1)[1],
                           (PlaneType) getRawLine(RELATION_TABLE[plane2][plane1], plane2)[1]);
}

std::tuple<PlaneType, PlaneType, PlaneType> Cube::getCubie(PlaneType plane1, PlaneType plane2, PlaneType plane3) const {

    int x1 = getRawLine(RELATION_TABLE[plane1][plane2], plane1)[(static_cast<int>(RELATION_TABLE[plane1][plane3]) - 1) %
                                                                3];
    int x2 = getRawLine(RELATION_TABLE[plane2][plane3], plane2)[(static_cast<int>(RELATION_TABLE[plane2][plane1]) - 1) %
                                                                3];
    int x3 = getRawLine(RELATION_TABLE[plane3][plane1], plane3)[(static_cast<int>(RELATION_TABLE[plane3][plane2]) - 1) %
                                                                3];

    return std::make_tuple((PlaneType) x1, (PlaneType) x2, (PlaneType) x3);
}

void Cube::setLine(Cube::LineType line, PlaneType plane, QVector<int> newLine) {
    if (line == NOTHING) {
        qWarning("Cube::getLine(Cube::LineType, PlaneType)");
        qWarning("\tLineType is NOTHING");
    }

    if (plane > 2) {
        std::reverse(newLine.begin(), newLine.end());
    }

    int lineNumber = (static_cast<int>(line) - 1) % 3;
    int row = isRow(line);
    int column = 1 - row;

    for (int i = 0; i < 3; ++i) {
        matrix[plane][lineNumber * row + i * column][lineNumber * column + i * row] = newLine[i];
    }
}

Cube::Cube() : matrix(6, QVector<QVector<int>>(3, QVector<int>(3))) {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                matrix[i][j][k] = i;
            }
        }
    }

}


void Cube::rotate(Direction dir) {
    PlaneType plane = dir.getPlane();
    Rotation rot = dir.getRotation();

    if (plane < STANDING) {
        for (int i = 0; i < (plane > 2 ? 4 - rot : rot); ++i) {
            rotateMatrix(matrix[plane]);
        }
        for (int i = 0; i < rot; ++i) {
            rotateCounterClockwise(dir);
        }
    } else {
        for (int i = 0; i < 4 - rot; ++i) {
            rotateMiddle(dir);
        }
    }


}

void Cube::rotate(QString dir) {
    rotate(Direction(dir));
}

void Cube::rotate(PlaneType plane, Rotation rotation) {
    rotate(Direction(plane, rotation));
}

//void Cube::setFront(PlaneType plane)
//{

//    currentFront = plane;
//}

void Cube::rotateCounterClockwise(Direction &dir) {
    PlaneType plane = dir.getPlane();
    QVector<PlaneType> neighbours = dir.getNeighbours();


    PlaneType currentPlane = neighbours[0];
    PlaneType nextPlane;
    LineType currentLine = RELATION_TABLE[currentPlane][plane];
    LineType nextLine;

    //    if (plane > DOWN) {

    //    }

    //     qDebug() << "Cube::rotate: " << "start moving lines";
    //     qDebug() << "Cube::rotate: " << "neighbours = " << neighbours;

    for (int i = 0; i < 3; ++i) {
        //        qDebug() << "Cube::rotate: " << " i = " << i;
        nextPlane = neighbours[(i + 1) % 4];
        nextLine = RELATION_TABLE[nextPlane][plane];

        //         qDebug() << "Cube::rotate: " << "nextPlane = " << nextPlane;
        //         qDebug() << "Cube::rotate: " << "nextLine = " << nextLine;

        auto currentContents = getLine(currentLine, currentPlane);
        auto nextContents = getLine(nextLine, nextPlane);

        //         qDebug() << "Cube::rotate: " << "currentContents = " << vectorToString(currentContents);
        //         qDebug() << "Cube::rotate: " << "nextContents = " << vectorToString(nextContents);

        setLine(currentLine, currentPlane, nextContents);
        setLine(nextLine, nextPlane, currentContents);

        //         std::cout << print().toStdString() << std::endl;

        currentPlane = nextPlane;
        currentLine = nextLine;
    }

}

void Cube::rotateMiddle(Direction &dir) {
    PlaneType plane = dir.getPlane();
    QVector<PlaneType> neighbours = dir.getNeighbours();
    QVector<LineType> lines;

    switch (plane) {
        case MIDDLE:
            lines = {CENTER_COLUMN, CENTER_COLUMN, CENTER_COLUMN, CENTER_COLUMN};
            break;
        case STANDING:
            lines = {CENTER_COLUMN, CENTER_ROW, CENTER_COLUMN, CENTER_ROW};
            break;
        case EQUATOR:
            lines = {CENTER_ROW, CENTER_ROW, CENTER_ROW, CENTER_ROW};
            break;
        default:
            throw;
    }

    PlaneType currentPlane = neighbours[0];
    PlaneType nextPlane;
    LineType currentLine = lines[0];
    LineType nextLine;

    for (int i = 0; i < 3; ++i) {
        nextPlane = neighbours[(i + 1) % 4];
        nextLine = lines[(i + 1) % 4];

        auto currentContents = getLine(currentLine, currentPlane);
        auto nextContents = getLine(nextLine, nextPlane);

        setLine(currentLine, currentPlane, nextContents);
        setLine(nextLine, nextPlane, currentContents);

        currentPlane = nextPlane;
        currentLine = nextLine;
    }
}
