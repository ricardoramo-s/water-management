#include "DataReader.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>

DataReader::DataReader(std::string path, std::string name) {

    this->path = std::move(path);
    this->name = std::move(name);

    readCities();
    readPipes();
    readReservoirs();
    readStations();
}

void DataReader::readCities() {

    std::string filePath = path + "Cities" + name + ".csv";

    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Unable to open file: " << filePath << std::endl;
    }

    std::string line;

    getline(file, line); // Skip first line (header)

    while (getline(file, line)) {

        std::istringstream ss(line);
        std::string city;
        int id;
        std::string code;
        double demand;
        std::string population;
        int n = 0;    // the n word in the line

        std::string word;

        while (getline(ss, word, ',')) {

            switch (n) {
                case 0:
                    city = word;
                    break;

                case 1:
                    id = stoi(word);
                    break;

                case 2:
                    code = word;
                    break;

                case 3:
                    demand = stod(word);
                    break;

                case 4:
                    population = word;
                    break;

                default:
                    std::cout << "Error: " << word << '\n';
                    break;
            }
            n++;
        }


    }

    file.close();
}

void DataReader::readPipes() {

    std::string filePath = path + "Pipes" + name + ".csv";

    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Unable to open file: " << filePath << std::endl;
    }

    std::string line;

    getline(file, line); // Skip first line (header)

    while (getline(file, line)) {

        std::istringstream ss(line);
        std::string org;
        std::string dest;
        double capacity;
        bool direction;
        int n = 0;    // the n word in the line

        std::string word;

        while (getline(ss, word, ',')) {

            switch (n) {
                case 0:
                    org = word;
                    break;

                case 1:
                    dest = word;
                    break;

                case 2:
                    capacity = stod(word);
                    break;

                case 3:
                    direction = (word == "1");
                    break;

                default:
                    std::cout << "Error: " << word << '\n';
                    break;
            }
            n++;
        }


    }

    file.close();
}

void DataReader::readReservoirs() {

    std::string filePath = path + "Reservoirs" + name + ".csv";

    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Unable to open file: " << filePath << std::endl;
    }

    std::string line;

    getline(file, line); // Skip first line (header)

    while (getline(file, line)) {

        std::istringstream ss(line);
        std::string reservoir;
        std::string municipality;
        int id;
        double maxDelivery;
        int n = 0;    // the n word in the line

        std::string word;

        while (getline(ss, word, ',')) {

            switch (n) {
                case 0:
                    reservoir = word;
                    break;

                case 1:
                    municipality = word;
                    break;

                case 2:
                    id = stoi(word);
                    break;

                case 3:
                    maxDelivery = stod(word);
                    break;

                default:
                    std::cout << "Error: " << word << '\n';
                    break;
            }
            n++;
        }


    }

    file.close();
}

void DataReader::readStations() {

    std::string filePath = path + "Cities" + name + ".csv";

    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Unable to open file: " << filePath << std::endl;
    }

    std::string line;

    getline(file, line); // Skip first line (header)

    while (getline(file, line)) {

        std::istringstream ss(line);
        int id;
        std::string code;
        int n = 0;    // the n word in the line

        std::string word;

        while (getline(ss, word, ',')) {

            switch (n) {
                case 0:
                    id = stoi(word);
                    break;

                case 1:
                    code = word;
                    break;

                default:
                    std::cout << "Error: " << word << '\n';
                    break;
            }
            n++;
        }


    }

    file.close();
}
