#ifndef PUBLICTRANSPORTGRAPH_BUSSTOP_H
#define PUBLICTRANSPORTGRAPH_BUSSTOP_H

#include "busline.h"
#include "location.h"
#include "network.h"
#include "node.h"
#include <iostream>
#include <set>
#include <string>

class BusStop : public Node {
public:
    BusStop(int stopID, const std::string &stopName, Location location, int zoneID);

    int getStopID_() const;
    const std::string &getStopName_() const;
    int getZoneID_() const;
    const Location &getLocation_() const;

    std::set<BusLine *> getLines();
    bool isStopForLine(BusLine *);

    friend void BusLine::addStop(BusStop *stop, Directions direction);
    friend void BusLine::removeStop(BusStop *stop, Directions direction);
    friend void BusLine::removeAllStops();
    friend void Network::removeLine(BusLine *);

    friend bool operator<(const BusStop &stop1, const BusStop &stop2);
    friend std::ostream &operator<<(std::ostream &, const BusStop &);

    std::string label() const override;

private:
    int stopID_;
    std::string stopName_;
    Location location_;
    int zoneID_;
    std::set<BusLine *> lines_;

    void addLine(BusLine *line);
    void removeLine(BusLine *line);
};

#endif //PUBLICTRANSPORTGRAPH_BUSSTOP_H
