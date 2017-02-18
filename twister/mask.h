#ifndef MASK_H
#define MASK_H

#include <QMap>
#include "direction.h"

using Duo    = std::tuple<PlaneType, PlaneType>;
using Triple = std::tuple<PlaneType, PlaneType, PlaneType>;

class Mask
{
private:
    QMap<Duo, Duo>duos;
    QMap<Triple, Triple>triples;

public:
    Mask();
    void setCubie(const Duo &coord, const Duo &color);
    void setCubie(const Triple &coord, const Triple &color);

    Duo getCubie(const Duo &coord);
    Triple getCubie(const Triple &coord);

    void eraseCubie(const Duo &coord);
    void eraseCubie(const Triple &coord);

    template <typename T, template <typename> class Container>
    void setCubies(const Container<T> &coords, const Container<T> &colors) {
        auto t1 = coords.begin();
        auto t2 = colors.begin();
        for (; t1 != coords.end() && t2 != colors.end(); ++t1, ++t2) {
            setCubie(*t1, *t2);
        }
    }

    template <typename T, template <typename> class Container>
    void eraseCubies(const Container<T> &container) {
        for (T& t: container) {
            eraseCubie(t);
        }
    }

    QMap<Duo, Duo> getDuos() const;
    QMap<Triple, Triple> getTriples() const;
};


#endif // MASK_H
