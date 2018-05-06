#include <iostream>
#include "textparser.h"
#include "network.h"
#include "busstop.h"
#include "location.h"
#include "invalidfile.h"

TextParser::TextParser(Network &network) : network_(network) {}

void TextParser::collectData(const std::string &fileName) {
    std::ifstream file(fileName);

    std::string errorMessages;

    if (file.is_open()) {
        // empty file
        if (file.peek() == std::ifstream::traits_type::eof()) {
            file.close();
            throw InvalidFile("File " + fileName + " empty");
        }

        std::regex reg("([^!]*)!([^!]*)!([^!]*)!\r?");
        std::string textLine;

        while (std::getline(file, textLine)) {
            std::smatch result;
            if (regex_match(textLine, result, reg)) {
                std::string lineName = result.str(1);
                std::string firstStop = result.str(2);
                std::string lastStop = result.str(3);
                auto newLine = new BusLine(lineName, firstStop, lastStop);
                network_.addLine(newLine);

                // file path prefix
                unsigned long pos = fileName.find_last_of("/\\");
                std::string lineFileName = fileName.substr(0, pos + 1) + lineName + "_dir";

                // collecting stops for direction A and B
                try {
                    collectStopsData(lineFileName + "A.txt", newLine, BusLine::Directions::DIRECTION_A);
                    collectStopsData(lineFileName + "B.txt", newLine, BusLine::Directions::DIRECTION_B);
                } catch(std::exception& e) {
                    errorMessages += e.what();
                    errorMessages += '\n';
                }

            } else {
                network_.clear();
                file.close();
                throw InvalidFile("Invalid format in file " + fileName);
            }
        }

    } else {
        file.close();
        throw InvalidFile("File " + fileName + " not found");
    }

    file.close();
    if (errorMessages != "")
        throw InvalidFile(errorMessages);

}

void TextParser::collectStopsData(const std::string &fileName, BusLine *line, BusLine::Directions direction) {
    std::ifstream file(fileName);

    if (file.is_open()) {

        // empty file
        if (file.peek() == std::ifstream::traits_type::eof()) {
            file.close();
            network_.removeLine(line);
            throw InvalidFile("File " + fileName + " empty");
        }

        std::regex reg("([^!]*)!([^!]*)!([^!]*)!([^!]*)!([1-4])\r?");
        std::string textLine;

        while (std::getline(file, textLine)) {

            std::smatch result;
            if (regex_match(textLine, result, reg)) {
                int stopID = atoi(result.str(1).c_str());

                // if the stop exists in the network not needed to make a new one
                BusStop *oldStop = network_.getStop(stopID);
                if (oldStop != nullptr) {
                    line->addStop(oldStop, direction);
                    continue;
                }

                std::string stopName = result.str(2);
                double latitude = atof(result.str(3).c_str());
                double longitude = atof(result.str(4).c_str());
                Location location(latitude, longitude);
                int zoneID = atoi(result.str(5).c_str());

                BusStop *newStop = new BusStop(stopID, stopName, location, zoneID);
                line->addStop(newStop, direction);
                network_.addStop(stopID, newStop);

            } else {
                network_.removeLine(line);
                file.close();
                throw InvalidFile("Invalid format in file " + fileName);
            }
        }

    } else {
        file.close();
        network_.removeLine(line);
        throw InvalidFile("File " + fileName + " not found");
    }

    file.close();

}


