#ifndef POOP_P1_NETWORK_H
#define POOP_P1_NETWORK_H

#include <set>
#include <map>
#include <iostream>
#include "ptrcomparator.h"
#include "busline.h"

class BusLine;
class BusStop;

class Network {
public:
    static const int LAST_ZONE = 4;

    ~Network();

    void addLine(BusLine*);
    void addStop(int stopID, BusStop* stop);

    BusLine* getLine(const std::string& lineName);
    BusStop* getStop(int stopID);

    void filterByZone(int numOfZones);
    void filterByLineNumberRange(int lower, int upper);
    void filterByLineNumberSmaller(int upper);
    void filterByLineNumberGreater(int lower);
    void filterByNumberOfStopsSmaller(int upper);
    void filterByNumberOfStopsGreater(int lower);

    friend std::ostream& operator<<(std::ostream& os, const Network& n);

private:
    std::set<BusLine *, PtrComparator> busLines_;
    std::map<int, BusStop*> allBusStops_;

    void filterIf(std::function<bool(std::set<BusLine *>::iterator)> condition);
};


#endif //POOP_P1_NETWORK_H
