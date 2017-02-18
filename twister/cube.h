#ifndef CUBE_H
#define CUBE_H

#include <QVector>
#include <tuple>
#include "direction.h"
#include "utils.h"
#include "mask.h"

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
    QVector<int> getLine(LineType line, PlaneType plane) const;

    void rotateCounterClockwise(Direction &dir);

    void rotateMiddle(Direction &dir);

    friend bool isRow(LineType line);

    template <typename K, typename V>
    bool fitsCubies(const QMap<K, V> &cubies) const {
        for (const K &key : cubies.keys()) {
            if (cubies[key] != getCubie(key)) {
                return false;
            }
        }
        return true;
    }

    template <typename K, typename V>
    bool fitsCubiesRelatively(const QMap<K, V> &cubies) const {
        for (const K &key : cubies.keys()) {
            if (cubies[key] != getCubie(key)) {
                return false;
            }
        }
        return true;
    }



public:
    Cube();

    bool rotate(Direction dir);
    bool rotate(QString dir);
    bool rotate(PlaneType plane, Rotation rotation);

    bool rotate(QStringList dirs);

    //    void setFront(PlaneType plane);
    void turnLeft();
    void turnRight();
    void turnHalf();


    QVector<QVector<QVector<int> > > getMatrix() const;
    QString print() const;

    //returns line without without reversing it
    QVector<int> getRawLine(LineType line, PlaneType plane) const;
    PlaneType getCurrentFront() const;

    Duo getCubie(PlaneType plane1, PlaneType plane2) const;
    Duo getCubie(const Duo &planes) const;
    Triple getCubie(PlaneType plane1, PlaneType plane2, PlaneType plane3) const;
    Triple getCubie(const Triple &planes) const;

    bool fitsMask(const Mask &mask) const;
    bool fitsMaskRelatively(const Mask &mask) const;
};

#endif // CUBE_H
