#include "cube.h"
#include "direction.h"
#include "QDebug"
//#include <iostream>

QVector<QVector<QVector<int> > > Cube::getMatrix() const
{
    return matrix;
}

bool isRow(Cube::LineType line) {
    return line > Cube::NOTHING && line < Cube::LEFT_COLUMN;
}

QVector<int> Cube::getLine(Cube::LineType line, PlaneType plane)
{
    if (line == NOTHING) {
        qWarning("Cube::getLine(Cube::LineType, PlaneType)");
        qWarning("\tLineType is NOTHING");

        return QVector<int>();
    }

    QVector<int> result(3);

    int row     = isRow(line);
    int column  = 1 - row;
    int bottom  = line == BOTTOM_ROW;
    int right   = line == RIGHT_COLUMN;

    for (int i = 0; i < 3; ++i) {
        result[i] = matrix[plane][i * column + 2 * bottom][i * row + 2 * right];
    }

    return result;
}

QString Cube::print()
{
    QList<QString> result;
    for (auto row: matrix[UP]) {
        result.append("   " + vectorToString(row));
    }

    for (int row = 0; row < 3; ++row) {
        QString temp = "";
        for (int plane: QVector<int>{LEFT, FRONT, RIGHT, BACK}) {
            temp += vectorToString(matrix[plane][row]);
        }
        result.append(temp);
    }

    for (auto row: matrix[DOWN]) {
        result.append("   " + vectorToString(row));
    }


    return result.join("\n");
}

void Cube::setLine(Cube::LineType line, PlaneType plane, QVector<int> newLine)
{
    if (line == NOTHING) {
        qWarning("Cube::setLine(Cube::LineType, PlaneType, QVector<int>)");
        qWarning("\tLineType is NOTHING");

        return;
    }

    int row     = isRow(line);
    int column  = 1 - row;
    int bottom  = line == BOTTOM_ROW;
    int right   = line == RIGHT_COLUMN;

    for (int i = 0; i < 3; ++i) {
        matrix[plane][i * column + 2 * bottom][i * row + 2 * right] = newLine[i];
    }
}

Cube::Cube(): matrix(6, QVector<QVector<int>>(3, QVector<int>(3)))
{
    for(int i = 0; i < 6; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                matrix[i][j][k] = i;
            }
        }
    }

}


void Cube::rotate(Direction dir)
{
    PlaneType plane = dir.getPlane();
    Rotation rot = dir.getRotation();

    for (int i = 0; i < rot; ++i) {
        rotateMatrix(matrix[plane]);
        rotateCounterClockwise(dir);
    }


}

void Cube::rotateCounterClockwise(Direction &dir) {
     PlaneType plane = dir.getPlane();
     QVector<PlaneType> neighbours = dir.getNeighbours();

     PlaneType currentPlane = neighbours[0];
     PlaneType nextPlane = currentPlane;
     LineType currentLine = RELATION_TABLE[currentPlane][plane];
     LineType nextLine = currentLine;

//     qDebug() << "Cube::rotate: " << "start moving lines";
//     qDebug() << "Cube::rotate: " << "neighbours = " << neighbours;

     for (int i = 0; i < 3; ++i) {
//         qDebug() << "Cube::rotate: " << " i = " << i;

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
