#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QVector>
#include <functional>
#include "direction.h"

template <typename T>
QString vectorToString(const QVector<T> &vector)
{
    QString result;
    for (T t: vector) {
        result += t;
    }
    return result;
};

template <>
QString vectorToString(QVector<int> const& vector);


// деление по модулю здорового человека
template <typename T>
inline T modulus(T i, T n) {
    return (i % n + n) % n;
}

//template <typename T>
//QString vectorToString(QVector<T> const& vector, std::function<QString(T)> show) {
//    QString result;
//    for (T t : vector) {
//        result += show(t);
//    }
//    return result;
//}


void rotateHelper(int n, int& x, int& y);

template <typename T>
void rotateMatrix(QVector<QVector<T>>& matrix) {

    //    using std::cout;
    //    using std::endl;

    //    cout << "rotateMatrix: " << endl;
    int n = matrix.length();
    //    cout << "n = " << n << endl;

    for (int i = 0; i < (n+1)/2; ++i){
        for (int j = 0; j < n/2; ++j) {
            int x0 = j, y0 = i;
            int x1 = j, y1 = i;

            for (int k = 0; k < 3; ++k)  {
                rotateHelper(n, x1, y1);

                //                cout << "Swapping:"
                //                     << " x = " << x0
                //                     << " y = " << y0
                //                     << " x1 = " << x1
                //                     << " y1 = " << y1
                //                     << endl;


                std::swap(matrix[y0][x0], matrix[y1][x1]);
                x0 = x1;
                y0 = y1;
            }

        }
    }
    //    cout << "end rotation" << endl;

}

QString planeToString(PlaneType p);
//fixme wut?
PlaneType getLeft(PlaneType p);
PlaneType getRight(PlaneType p);
PlaneType getBack(PlaneType p);

#endif // UTILS_H
