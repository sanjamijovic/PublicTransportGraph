#ifndef PUBLICTRANSPORTGRAPH_BUSLINE_H
#define PUBLICTRANSPORTGRAPH_BUSLINE_H


#include <string>
#include <utility>
#include <vector>
#include <map>
#include <set>

#include "linedirection.h"
#include "ptrcomparator.h"

class BusStop;

class BusLine {

public:
    enum Directions { DIRECTION_A, DIRECTION_B };

    BusLine(const std::string& lineName, const std::string& firstStop, const std::string& lastStop);

    void setName(const std::string& lineName);
    unsigned long getNumberOfStops(Directions direction) const;
    int getNumberOfStopsInZone(int zoneID);
    unsigned long getNumberOfAllStops() const;
    int getLineNumber() const;
    const std::string& getName() const;
    const std::string& getFirstStop() const;
    const std::string& getLastStop() const;

    void addStop(BusStop* stop, Directions direction);
    void removeStop(BusStop* stop, Directions direction);

    std::set<BusLine *, PtrComparator> linesWithMutualStops();
    BusLine* lineWithMostMutualStops();
    bool hasStopsInOneDirection(BusStop* firstStop, BusStop* secondStop) const;
    BusStop* nextStopInDirection(BusStop* stop, Directions direction);
    static unsigned long numOfMutualStops(BusLine*, BusLine*);

    friend bool operator<(const BusLine& line1, const BusLine& line2);
    friend std::ostream& operator<<(std::ostream &os, const BusLine &line);

private:
    std::string lineName_;
    int lineNumber_;
    std::string firstStop_, lastStop_;
    LineDirection directionA_, directionB_;
    std::map<int, int> numberOfStopsInZone_;

    int getLineNumberFromLineName();
    std::set<BusStop*> getAllStops();
};


#endif //PUBLICTRANSPORTGRAPH_BUSLINE_H
