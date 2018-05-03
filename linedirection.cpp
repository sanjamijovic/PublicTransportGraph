#include "linedirection.h"
#include "busstop.h"
#include <vector>


void LineDirection::add(BusStop *stop) {
    stops_.push_back(stop);
}

void LineDirection::remove(BusStop *stop) {
    stops_.erase(std::remove(stops_.begin(), stops_.end(), stop), stops_.end());
}

unsigned long LineDirection::getNumberOfStops() const {
    return stops_.size();
}

std::vector<BusStop *> LineDirection::getStops() {
    return stops_;
}

bool LineDirection::hasStops(BusStop *firstStop, BusStop *secondStop) const {
    auto firstResult = std::find(stops_.begin(), stops_.end(), firstStop);
    auto secondResult = std::find(stops_.begin(), stops_.end(), secondStop);
    return !(firstResult == stops_.end() || secondResult == stops_.end());
}

BusStop *LineDirection::nextStop(BusStop *stop) {
    for(auto it = stops_.begin(); it != stops_.end(); it++)
        if((*it) == stop)
            return *(++it);
    return nullptr;
}

std::ostream &operator<<(std::ostream &os, const LineDirection &l) {
    for (BusStop *s : l.stops_)
        os << *s;
    return os;
}
