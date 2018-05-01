#include "location.h"

Location::Location(double latitude, double longitude) :
        latitude_(latitude),
        longitude_(longitude)
{}

double Location::getLatitude() const {
    return latitude_;
}

double Location::getLongitude() const {
    return longitude_;
}

std::ostream &operator<<(std::ostream & os, const Location & l) {
    return os << l.latitude_ << ", " << l.longitude_;
}

