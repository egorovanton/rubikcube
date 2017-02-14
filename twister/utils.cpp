#include "utils.h"

template <>
QString vectorToString(QVector<int> const& vector) {
    QString result;
    for (int t: vector) {
        result += QString::number(t);
    }
    return result;
}


void rotateHelper(int n, int &x, int &y)  {
    int temp = y;
    y = x;
    x = n - temp - 1;
}

