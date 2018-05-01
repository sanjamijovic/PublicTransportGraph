#include "network.h"
#include "busline.h"


Network::~Network() {
    for (auto l : busLines_)
        delete l;

    for (auto s : allBusStops_)
        delete s.second;
}

void Network::addLine(BusLine *line) {
    busLines_.insert(line);
}

void Network::addStop(int stopID, BusStop *stop) {
    allBusStops_.insert(std::pair<int, BusStop *>(stopID, stop));
}

BusLine *Network::getLine(const std::string &lineName) {
    for (auto l : busLines_)
        if (l->getName() == lineName)
            return l;

    return nullptr;
}

BusStop *Network::getStop(int stopID) {
    std::map<int, BusStop *>::iterator iter;
    iter = allBusStops_.find(stopID);
    if (iter == allBusStops_.end())
        return nullptr;
    return iter->second;
}

// leaves lines which have only stops in zones with smaller id than numOfZones
void Network::filterByZone(int numOfZones) {
    if (numOfZones <= 0 || numOfZones > LAST_ZONE)
        throw std::invalid_argument("Number of zone isn't valid.");

    filterIf([numOfZones](std::set<BusLine *>::iterator iter) {
        for (int i = numOfZones + 1; i <= LAST_ZONE; i++)
            if ((*iter)->getNumberOfStopsInZone(i) != 0)
                return false;

        return (*iter)->getNumberOfAllStops() != 0;
    });
}

void Network::filterByLineNumberRange(int lower, int upper) {
    filterIf([lower, upper](std::set<BusLine *>::iterator iter) {
        return (*iter)->getLineNumber() >= lower && (*iter)->getLineNumber() <= upper;
    });
}

void Network::filterByLineNumberSmaller(int upper) {
    filterByLineNumberRange(0, upper - 1);
}

void Network::filterByLineNumberGreater(int lower) {
    filterByLineNumberRange(lower + 1, INT_MAX);
}

void Network::filterByNumberOfStopsSmaller(int upper) {
    filterIf([upper](std::set<BusLine *>::iterator iter) {
        return (*iter)->getNumberOfAllStops() < upper;
    });
}

void Network::filterByNumberOfStopsGreater(int lower) {
    filterIf([lower](std::set<BusLine *>::iterator iter) {
        return (*iter)->getNumberOfAllStops() > lower;
    });
}

std::ostream &operator<<(std::ostream &os, const Network &n) {
    for (BusLine *b : n.busLines_) {
        os << b->getName() << " " << b->getFirstStop() << " -> " << b->getLastStop() << std::endl;
    }
    return os;
}

void Network::filterIf(std::function<bool(std::set<BusLine *>::iterator)> condition) {
    // keep items which fulfill the condition
    for (auto iter = busLines_.begin(); iter != busLines_.end();) {
        if (condition(iter))
            iter++;
        else
            busLines_.erase(iter++);
    }
}
