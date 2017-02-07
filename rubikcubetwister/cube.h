#ifndef CUBE_H
#define CUBE_H

#include <QVector>
#include "direction.h"
#include "utils.h"

class Cube
{
private:
    QVector<QVector<QVector<int>>> matrix;
    enum LineType {
        NOTHING,

        TOP_ROW,
        CENTER_ROW,
        BOTTOM_ROW,

        LEFT_COLUMN,
        CENTER_COLUMN,
        RIGHT_COLUMN
    };

    const QVector<QVector<LineType>> RELATION_TABLE = {
        {NOTHING, RIGHT_COLUMN, TOP_ROW, NOTHING, LEFT_COLUMN, BOTTOM_ROW},  // front plane
        {LEFT_COLUMN, NOTHING, TOP_ROW, RIGHT_COLUMN, NOTHING, BOTTOM_ROW},  // right plane
        {BOTTOM_ROW, RIGHT_COLUMN, NOTHING, TOP_ROW, LEFT_COLUMN, NOTHING},  // up plane
        {NOTHING, LEFT_COLUMN, TOP_ROW, NOTHING, RIGHT_COLUMN, BOTTOM_ROW},  // back plane
        {RIGHT_COLUMN, NOTHING, TOP_ROW, LEFT_COLUMN, NOTHING, BOTTOM_ROW},  // left plane
        {TOP_ROW, RIGHT_COLUMN, NOTHING, BOTTOM_ROW, LEFT_COLUMN, NOTHING}   // down plane
    };

    void setLine(LineType line, PlaneType plane, QVector<int> newLine);
    void rotateCounterClockwise(Direction &dir);
    friend bool isRow(LineType line);
public:
    Cube();

    void rotate(Direction dir);

    QVector<QVector<QVector<int> > > getMatrix() const;
    QVector<int> getLine(LineType line, PlaneType plane);
    QString print();
};

#endif // CUBE_H
