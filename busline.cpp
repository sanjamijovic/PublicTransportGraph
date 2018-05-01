#include "busline.h"
#include "linedirection.h"
#include "busstop.h"
#include <regex>
#include <set>

BusLine::BusLine(const std::string &lineName, const std::string &firstStop, const std::string &lastStop) :
        lineName_(lineName),
        lineNumber_(getLineNumberFromLineName()),
        firstStop_(firstStop),
        lastStop_(lastStop)
{}

void BusLine::setName(const std::string &lineName) {
    lineName_ = lineName;
    lineNumber_ = getLineNumberFromLineName();
}

unsigned long BusLine::getNumberOfStops(BusLine::Directions direction) const {
    if (direction == Directions::DIRECTION_A)
        return directionA_.getNumberOfStops();
    else
        return directionB_.getNumberOfStops();
}

unsigned long BusLine::getNumberOfAllStops() const {
    return directionA_.getNumberOfStops() + directionB_.getNumberOfStops();
}

int BusLine::getNumberOfStopsInZone(int zoneID) {
    std::map<int, int>::iterator iter;
    iter = numberOfStopsInZone_.find(zoneID);
    if (iter == numberOfStopsInZone_.end())
        return 0;
    return iter->second;
}

int BusLine::getLineNumber() const {
    return lineNumber_;
}

const std::string& BusLine::getName() const {
    return lineName_;
}

const std::string& BusLine::getFirstStop() const {
    return firstStop_;
}

const std::string& BusLine::getLastStop() const {
    return lastStop_;
}

void BusLine::addStop(BusStop *stop, BusLine::Directions direction) {
    if (direction == Directions::DIRECTION_A)
        directionA_.add(stop);
    else
        directionB_.add(stop);

    stop->addLine(this);

    numberOfStopsInZone_.insert(
            std::pair<int, int>(stop->getZoneID_(), getNumberOfStopsInZone(stop->getZoneID_()) + 1));
}

void BusLine::removeStop(BusStop *stop, BusLine::Directions direction) {
    if (direction == Directions::DIRECTION_A)
        directionA_.remove(stop);
    else
        directionB_.remove(stop);

    stop->removeLine(this);

    numberOfStopsInZone_.insert(
            std::pair<int, int>(stop->getZoneID_(), getNumberOfStopsInZone(stop->getZoneID_()) - 1));
}

std::set<BusLine *, PtrComparator> BusLine::linesWithMutualStops() {
    auto allStops = getAllStops();
    std::set<BusLine *, PtrComparator> result;

    for (auto stop : allStops)
        for (auto line : stop->getLines())
            if (line != this)
                result.insert(line);
    return result;
}

BusLine *BusLine::lineWithMostMutualStops() {
    auto allStops = getAllStops();
    std::map<BusLine *, int> mutualStopsPerLine;

    for (auto stop : allStops)
        for (auto line : stop->getLines()) {
            if (line != this)
                mutualStopsPerLine[line]++;
        }

    auto x = std::max_element(mutualStopsPerLine.begin(), mutualStopsPerLine.end(),
                              [](const std::pair<BusLine *, int> &p1, const std::pair<BusLine *, int> &p2) {
                                  return p1.second < p2.second;
                              });

    if (x == mutualStopsPerLine.end())
        return nullptr;
    return x->first;
}

bool BusLine::hasStopsInOneDirection(BusStop *firstStop, BusStop *secondStop) const {
    return directionA_.hasStops(firstStop, secondStop) || directionB_.hasStops(firstStop, secondStop);
}

void BusLine::writeDirection(BusLine::Directions direction) const {
    if (direction == Directions::DIRECTION_A)
        std::cout << directionA_;
    else
        std::cout << directionB_;
}

bool operator<(const BusLine &line1, const BusLine &line2) {
    if (line1.lineNumber_ == line2.lineNumber_)
        return line1.lineName_ < line2.lineName_;
    return line1.lineNumber_ < line2.lineNumber_;
}

int BusLine::getLineNumberFromLineName() {
    std::regex reg("[^\\d]*(\\d+).*");
    std::smatch result;
    std::regex_match(lineName_, result, reg);
    return atoi(result.str(1).c_str());
}

std::set<BusStop *> BusLine::getAllStops() {
    auto vect1 = directionA_.getStops();
    auto vect2 = directionB_.getStops();

    std::set<BusStop*> result;
    result.insert(vect1.begin(), vect1.end());
    result.insert(vect2.begin(), vect2.end());
    return result;
}
