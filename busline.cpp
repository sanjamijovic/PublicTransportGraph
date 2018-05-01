#include "busline.h"
#include "linedirection.h"
#include "busstop.h"
#include <regex>

BusLine::BusLine(const std::string &lineName, const std::string &firstStop, const std::string &lastStop) :
        lineName_(lineName),
        firstStop_(firstStop),
        lastStop_(lastStop),
        lineNumber_(getLineNumberFromLineName())
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

    numberOfStopsInZone_.insert(
            std::pair<int, int>(stop->getZoneID_(), getNumberOfStopsInZone(stop->getZoneID_()) + 1));
}

void BusLine::removeStop(BusStop *stop, BusLine::Directions direction) {
    if (direction == Directions::DIRECTION_A)
        directionA_.remove(stop);
    else
        directionB_.remove(stop);
    numberOfStopsInZone_.insert(
            std::pair<int, int>(stop->getZoneID_(), getNumberOfStopsInZone(stop->getZoneID_()) - 1));
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
