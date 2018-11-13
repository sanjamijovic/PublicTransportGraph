#include "location.h"
#include <cmath>

Location::Location(double latitude, double longitude) :
        latitude_(latitude),
        longitude_(longitude) {}

double Location::getLatitude() const {
    return latitude_;
}

double Location::getLongitude() const {
    return longitude_;
}

double Location::distance(const Location &l1, const Location &l2) {
    return sqrt(pow(l1.longitude_ - l2.longitude_, 2) + pow(l1.latitude_ - l2.latitude_, 2));
}

std::ostream &operator<<(std::ostream &os, const Location &l) {
    return os << l.latitude_ << ", " << l.longitude_;
}

