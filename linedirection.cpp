#include "linedirection.h"
#include "busstop.h"


void LineDirection::add(BusStop *stop) {
    stops_.push_back(stop);
}

void LineDirection::remove(BusStop *stop) {
    stops_.erase(std::remove(stops_.begin(), stops_.end(), stop), stops_.end());
}

unsigned long LineDirection::getNumberOfStops() const {
    return stops_.size();
}

std::ostream &operator<<(std::ostream &os, const LineDirection &l) {
    for (BusStop *s : l.stops_)
        os << *s;
    return os;
}
