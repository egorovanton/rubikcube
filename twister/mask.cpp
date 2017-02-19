#include "mask.h"

QMap<Duo, Duo> Mask::getDuos() const
{
    return duos;
}

QMap<Triple, Triple> Mask::getTriples() const
{
    return triples;
}

Mask::Mask()
{

}

void Mask::setCubie(const PlaneType coord, const PlaneType color) {
    centroids[coord] = color;
}

void Mask::setCubie(const Duo &coord, const Duo &color) {
    duos[coord] = color;
}

void Mask::setCubie(const Triple &coord, const Triple &color) {
    triples[coord] = color;
}

PlaneType Mask::getCubie(const PlaneType coord) const {
    return centroids.value(coord, STUB);
}

Duo Mask::getCubie(const Duo &coord) const {
    return duos.value(coord, Duo{STUB, STUB});
}

Triple Mask::getCubie(const Triple &coord) const {
    return triples.value(coord, Triple{STUB, STUB, STUB});
}

void Mask::eraseCubie(const PlaneType coord) {
    centroids.remove(coord);
}

void Mask::eraseCubie(const Duo &coord) {
    duos.remove(coord);
}

void Mask::eraseCubie(const Triple &coord) {
    triples.remove(coord);
}

