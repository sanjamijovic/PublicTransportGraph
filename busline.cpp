#include "busline.h"
#include "linedirection.h"
#include "busstop.h"
#include "network.h"
#include <regex>
#include <set>

BusLine::BusLine(const std::string &lineName, const std::string &firstStop, const std::string &lastStop) :
        lineName_(lineName),
        lineNumber_(getLineNumberFromLineName()),
        firstStop_(firstStop),
        lastStop_(lastStop) {}

void BusLine::setName(const std::string &lineName) {
    lineName_ = lineName;
    lineNumber_ = getLineNumberFromLineName();
}

void BusLine::setFirstStop(const std::string &firstStop) {
    firstStop_ = firstStop;
}

void BusLine::setLastStop(const std::string &lastStop) {
    lastStop_ = lastStop;
}

unsigned long BusLine::getNumberOfStops(BusLine::Directions direction) const {
    return (direction == DIRECTION_A ? directionA_ : directionB_).getNumberOfStops();
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

const std::string &BusLine::getName() const {
    return lineName_;
}

const std::string &BusLine::getFirstStop() const {
    return firstStop_;
}

const std::string &BusLine::getLastStop() const {
    return lastStop_;
}

void BusLine::addStop(BusStop *stop, BusLine::Directions direction) {
    (direction == DIRECTION_A ? directionA_ : directionB_).add(stop);

    stop->addLine(this);
    numberOfStopsInZone_[stop->getZoneID_()] = numberOfStopsInZone_[stop->getZoneID_()] + 1;
}

void BusLine::removeStop(BusStop *stop, BusLine::Directions direction) {
    (direction == DIRECTION_A ? directionA_ : directionB_).remove(stop);
    auto otherDirection = (direction == DIRECTION_A ? directionB_ : directionA_);
    if (!otherDirection.hasStop(stop))
        stop->removeLine(this);
    numberOfStopsInZone_[stop->getZoneID_()] = numberOfStopsInZone_[stop->getZoneID_()] - 1;
}

void BusLine::removeAllStops() {
    for (auto stop : getAllStops())
        stop->removeLine(this);

    directionA_.removeAllStops();
    directionB_.removeAllStops();
    for (int i = 0; i < Network::LAST_ZONE; i++)
        numberOfStopsInZone_[i] = 0;
}

std::set<BusLine *, PtrComparator> BusLine::linesWithMutualStops() {
    auto allStops = getAllStops();
    std::set < BusLine * , PtrComparator > result;

    for (auto stop : allStops)
        for (auto line : stop->getLines())
            if (line != this)
                result.insert(line);
    return result;
}

BusLine *BusLine::lineWithMostMutualStops() {
    auto allStops = getAllStops();
    std::map < BusLine * , int > mutualStopsPerLine;

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

BusStop *BusLine::nextStopInDirection(BusStop *stop, BusLine::Directions direction) {
    return (direction == DIRECTION_A ? directionA_ : directionB_).nextStop(stop);
}

unsigned long BusLine::numOfMutualStops(BusLine *line1, BusLine *line2) {
    auto line1Stops = line1->getAllStops();
    auto line2Stops = line2->getAllStops();
    std::set <BusStop *> result;
    std::set_intersection(line1Stops.begin(), line1Stops.end(), line2Stops.begin(), line2Stops.end(),
                          std::inserter(result, result.begin()));
    return result.size();
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

std::string BusLine::label() const {
    return lineName_;
}

std::set<BusStop *> BusLine::getAllStops() {
    auto vect1 = directionA_.getStops();
    auto vect2 = directionB_.getStops();

    std::set <BusStop *> result;
    result.insert(vect1.begin(), vect1.end());
    result.insert(vect2.begin(), vect2.end());
    return result;
}

std::ostream &operator<<(std::ostream &os, const BusLine &line) {
    return os << line.getName() << " : " << line.firstStop_ << " -> " << line.lastStop_;
}
