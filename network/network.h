#ifndef PUBLICTRANSPORTGRAPH_NETWORK_H
#define PUBLICTRANSPORTGRAPH_NETWORK_H

#include "location.h"
#include "ptrcomparator.h"
#include <iostream>
#include <map>
#include <set>

class BusLine;
class BusStop;

class Network {
public:
    friend class LGraphGenerator;
    friend class CGraphGenerator;

    static const int LAST_ZONE = 4;
    using pairsOfConnectedLines = std::pair<std::pair<BusLine *, BusLine *>, unsigned long>;

    ~Network();

    void addLine(BusLine *);
    void removeLine(BusLine *);
    void changeLineName(BusLine *, const std::string &);
    void addStop(int stopID, BusStop *stop);

    BusLine *getLine(const std::string &lineName);
    BusStop *getStop(int stopID);
    std::vector <std::string> getAllLineNames() const;

    void filterByZone(unsigned long numOfZones);
    void filterByLineNumberRange(unsigned long lower, unsigned long upper);
    void filterByLineNumberSmaller(unsigned long upper);
    void filterByLineNumberGreater(unsigned long lower);
    void filterByNumberOfStopsSmaller(unsigned long upper);
    void filterByNumberOfStopsGreater(unsigned long lower);

    BusStop *nearestStopToLocation(Location location, BusLine *line = nullptr);
    std::set<BusStop *, PtrComparator> allNextStops(BusStop *stop);
    std::vector <pairsOfConnectedLines> mutualStopsForAllPairsOfLines(unsigned long minStops = 1);
    unsigned long shortestPath(BusStop *, BusStop *);
    unsigned long numOfStopovers(BusStop *, BusStop *);

    friend std::ostream &operator<<(std::ostream &os, const Network &n);

    void clear();

private:
    std::set<BusLine *, PtrComparator> busLines_;
    std::map<int, BusStop *> allBusStops_;

    void filterIf(std::function<bool(std::set<BusLine *>::iterator)> condition);
};

#endif //PUBLICTRANSPORTGRAPH_NETWORK_H
