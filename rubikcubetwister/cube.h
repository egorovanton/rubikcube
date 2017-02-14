#ifndef CUBE_H
#define CUBE_H

#include <QVector>
#include <tuple>
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
        {NOTHING, RIGHT_COLUMN, TOP_ROW, NOTHING, LEFT_COLUMN, BOTTOM_ROW},  // back plane
        {LEFT_COLUMN, NOTHING, TOP_ROW, RIGHT_COLUMN, NOTHING, BOTTOM_ROW},  // left plane
        {BOTTOM_ROW, RIGHT_COLUMN, NOTHING, TOP_ROW, LEFT_COLUMN, NOTHING}   // down plane
    };

//    PlaneType currentFront;

    //CAUTION
    //theese functions reverse newLine/result respectively when needed
    void setLine(LineType line, PlaneType plane, QVector<int> newLine);
    QVector<int> getLine(LineType line, PlaneType plane);

    void rotateCounterClockwise(Direction &dir);
    void rotateMiddle(Direction &dir);
    friend bool isRow(LineType line);
public:
    Cube();

    void rotate(Direction dir);
    void rotate(QString dir);
    void rotate(PlaneType plane, Rotation rotation);

//    void setFront(PlaneType plane);
    void turnLeft();


    QVector<QVector<QVector<int> > > getMatrix() const;
    QString print();

    //returns line without without reversing it
    QVector<int> getRawLine(LineType line, PlaneType plane);

    std::tuple<PlaneType, PlaneType> getCubie(PlaneType plane1, PlaneType plane2);
    std::tuple<PlaneType, PlaneType, PlaneType> getCubie(PlaneType plane1, PlaneType plane2, PlaneType plane3);


};

#endif // CUBE_H
