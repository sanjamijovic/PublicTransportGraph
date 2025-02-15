#ifndef PUBLICTRANSPORTGRAPH_LINEDIRECTION_H
#define PUBLICTRANSPORTGRAPH_LINEDIRECTION_H

#include <iostream>
#include <map>
#include <set>
#include <vector>

class BusLine;
class BusStop;

class LineDirection {
public:
    void add(BusStop *stop);
    void remove(BusStop *stop);
    void removeAllStops();

    unsigned long getNumberOfStops() const;
    std::vector<BusStop *> getStops();

    bool hasStops(BusStop *firstStop, BusStop *secondStop) const;
    bool hasStop(BusStop *stop) const;
    BusStop *nextStop(BusStop *stop);

    friend std::ostream &operator<<(std::ostream &, const LineDirection &);

private:
    std::vector<BusStop *> stops_;
};

#endif //PUBLICTRANSPORTGRAPH_LINEDIRECTION_H
