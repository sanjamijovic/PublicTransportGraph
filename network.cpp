#include "network.h"
#include "busline.h"
#include "busstop.h"

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
void Network::filterByZone(unsigned long numOfZones) {
    if (numOfZones <= 0 || numOfZones > LAST_ZONE)
        throw std::invalid_argument("Number of zone isn't valid.");

    filterIf([numOfZones](std::set<BusLine *>::iterator iter) {
        for (int i = numOfZones + 1; i <= LAST_ZONE; i++)
            if ((*iter)->getNumberOfStopsInZone(i) != 0)
                return false;

        return (*iter)->getNumberOfAllStops() != 0;
    });
}

void Network::filterByLineNumberRange(unsigned long lower, unsigned long upper) {
    filterIf([lower, upper](std::set<BusLine *>::iterator iter) {
        return (*iter)->getLineNumber() >= lower && (*iter)->getLineNumber() <= upper;
    });
}

void Network::filterByLineNumberSmaller(unsigned long upper) {
    filterByLineNumberRange(0, upper - 1);
}

void Network::filterByLineNumberGreater(unsigned long lower) {
    filterByLineNumberRange(lower + 1, INT_MAX);
}

void Network::filterByNumberOfStopsSmaller(unsigned long upper) {
    filterIf([upper](std::set<BusLine *>::iterator iter) {
        return (*iter)->getNumberOfAllStops() < upper;
    });
}

void Network::filterByNumberOfStopsGreater(unsigned long lower) {
    filterIf([lower](std::set<BusLine *>::iterator iter) {
        return (*iter)->getNumberOfAllStops() > lower;
    });
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

// calculates the nearest stop to location, if line passed must be a stop of that line
BusStop *Network::nearestStopToLocation(Location location, BusLine *line) {
    if(line && line->getNumberOfAllStops() == 0)
        return nullptr;
    std::vector<BusStop*> stopsOfLine;

    for(auto iter : allBusStops_) {
        if(!line || iter.second->isStopForLine(line))
            stopsOfLine.push_back(iter.second);
    }

    auto result = std::min_element(stopsOfLine.begin(), stopsOfLine.end(), [location](BusStop* stop1, BusStop* stop2) {
        return Location::distance(location, stop1->getLocation_()) < Location::distance(location, stop2->getLocation_());
    });
    if(result == stopsOfLine.end())
        return nullptr;
    return *result;

}

std::set<BusStop *, PtrComparator> Network::allNextStops(BusStop *stop) {
    std::set<BusStop *, PtrComparator> result;
    for (auto line : busLines_) {
        auto nextStop = line->nextStopInDirection(stop, BusLine::DIRECTION_A);
        if(nextStop)
            result.insert(nextStop);
        nextStop = line->nextStopInDirection(stop, BusLine::DIRECTION_B);
        if(nextStop)
            result.insert(nextStop);

    }

    return result;
}

std::vector<Network::pairsOfConnectedLines> Network::mutualStopsForAllPairsOfLines(unsigned long minStops) {
    std::vector<pairsOfConnectedLines> result;
    for(auto line1 : busLines_) {
        auto linesWithMutualStops = line1->linesWithMutualStops();
        for(auto line2 : linesWithMutualStops) {
            unsigned long numOfMutualStops = BusLine::numOfMutualStops(line1, line2);
            if (*line1 < *line2 && numOfMutualStops >= minStops)
                result.push_back(std::make_pair(std::make_pair(line1, line2), numOfMutualStops));
        }
    }

    std::sort(result.begin(), result.end(), [] (const pairsOfConnectedLines& pair1, const pairsOfConnectedLines& pair2) {
        return *pair1.first.first < *pair2.first.first;
    });

    return result;
}

std::ostream &operator<<(std::ostream &os, const Network &n) {
    for (BusLine *b : n.busLines_) {
        os << b->getName() << " " << b->getFirstStop() << " -> " << b->getLastStop() << std::endl;
    }
    return os;
}
