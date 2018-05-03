#ifndef PUBLICTRANSPORTGRAPH_NETWORK_H
#define PUBLICTRANSPORTGRAPH_NETWORK_H

#include <set>
#include <map>
#include <iostream>
#include "ptrcomparator.h"
#include "busline.h"
#include "location.h"

class BusLine;
class BusStop;

class Network {
public:
    static const int LAST_ZONE = 4;
    using pairsOfConnectedLines = std::pair<std::pair<BusLine*, BusLine*>, unsigned long>;

    ~Network();

    void addLine(BusLine*);
    void addStop(int stopID, BusStop* stop);

    BusLine* getLine(const std::string& lineName);
    BusStop* getStop(int stopID);

    void filterByZone(unsigned long numOfZones);
    void filterByLineNumberRange(unsigned long lower, unsigned long upper);
    void filterByLineNumberSmaller(unsigned long upper);
    void filterByLineNumberGreater(unsigned long lower);
    void filterByNumberOfStopsSmaller(unsigned long upper);
    void filterByNumberOfStopsGreater(unsigned long lower);

    BusStop* nearestStopToLocation(Location location, BusLine* line = nullptr);
    std::set<BusStop*, PtrComparator> allNextStops(BusStop* stop);
    std::vector<pairsOfConnectedLines> mutualStopsForAllPairsOfLines(unsigned long minStops = 1);
    unsigned long shortestPath(BusStop*, BusStop*);

    friend std::ostream& operator<<(std::ostream& os, const Network& n);

private:
    std::set<BusLine *, PtrComparator> busLines_;
    std::map<int, BusStop*> allBusStops_;

    void filterIf(std::function<bool(std::set<BusLine *>::iterator)> condition);
};


#endif //PUBLICTRANSPORTGRAPH_NETWORK_H
