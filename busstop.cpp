#include "busstop.h"

BusStop::BusStop(int stopID, const std::string &stopName, Location location, int zoneID) :
        stopID_(stopID),
        stopName_(stopName),
        location_(location),
        zoneID_(zoneID)
{}

int BusStop::getStopID_() const {
    return stopID_;
}

const std::string &BusStop::getStopName_() const {
    return stopName_;
}

int BusStop::getZoneID_() const {
    return zoneID_;
}

const Location &BusStop::getLocation_() const {
    return location_;
}

bool operator<(const BusStop &stop1, const BusStop &stop2) {
    return stop1.stopID_ < stop2.stopID_;
}

std::ostream &operator<<(std::ostream &os, const BusStop &s) {
    return os << s.stopID_ << " " << s.stopName_ << " " << s.location_ << " " << s.zoneID_ ;
}

std::set<BusLine *> BusStop::getLines() {
    return lines_;
}

bool BusStop::isStopForLine(BusLine * line) {
    return lines_.find(line) != lines_.end();
}

void BusStop::addLine(BusLine *line) {
    lines_.insert(line);
}

void BusStop::removeLine(BusLine *line) {
    lines_.erase(line);
}
