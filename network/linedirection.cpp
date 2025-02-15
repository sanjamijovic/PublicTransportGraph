#include "linedirection.h"
#include "busstop.h"
#include <vector>


void LineDirection::add(BusStop *stop) {
    stops_.push_back(stop);
}

void LineDirection::remove(BusStop *stop) {
    stops_.erase(std::remove(stops_.begin(), stops_.end(), stop), stops_.end());
}

void LineDirection::removeAllStops() {
    stops_.clear();
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

bool LineDirection::hasStop(BusStop *stop) const {
    return std::find(stops_.begin(), stops_.end(), stop) != stops_.end();
}

BusStop *LineDirection::nextStop(BusStop *stop) {
    auto iter = std::find(stops_.begin(), stops_.end(), stop);
    return iter != stops_.end() ? (std::next(iter) != stops_.end() ? *std::next(iter) : nullptr) : nullptr;
}

std::ostream &operator<<(std::ostream &os, const LineDirection &l) {
    for (BusStop *s : l.stops_)
        os << *s << std::endl;
    return os;
}
