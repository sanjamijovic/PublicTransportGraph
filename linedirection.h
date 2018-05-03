#ifndef POOP_P1_LINEDIRECTION_H
#define POOP_P1_LINEDIRECTION_H

#include <vector>
#include <iostream>
#include <set>
#include <map>

class BusLine;
class BusStop;

class LineDirection {
public:
    void add(BusStop* stop);
    void remove(BusStop* stop);

    unsigned long getNumberOfStops() const;
    std::vector<BusStop*> getStops();

    bool hasStops(BusStop* firstStop, BusStop* secondStop) const;
    BusStop* nextStop(BusStop* stop);

    friend std::ostream&operator<<(std::ostream&, const LineDirection&);

private:
    std::vector<BusStop*> stops_;
};


#endif //POOP_P1_LINEDIRECTION_H
