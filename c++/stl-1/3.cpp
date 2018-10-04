#include <iostream>
#include <regex>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <functional>

template<class T>
std::ostream& operator << (std::ostream& stream, const std::vector<T>& v) {
    stream << "[\n";
    for(auto it = v.begin(); it != v.end(); ++it) {
        stream << (*it) << "\n";
    }
    stream << "]";
    return stream;
}

class Train {
public:
    enum train_type_t {
        EXPRESS,
        PASSENGER
    };

    size_t number;
    train_type_t type;
    std::string destination;
    std::string departTime;
    size_t rideTime;

    Train(size_t num, train_type_t type, const std::string& dest, const std::string& departTime, size_t rideTime)
        : number(num), type(type), destination(dest), departTime(departTime), rideTime(rideTime) {}


    friend std::ostream& operator << (std::ostream& str, const Train& t) {
        std::string type_s = t.type == Train::train_type_t::EXPRESS ? "express" : "passenger";
        str << t.number << " ; " << t.destination << " ; " << type_s << " ; " << t.departTime << " ; " << t.rideTime;
        return str;
    }
};


std::vector<Train> findAll(std::vector<Train>::iterator begin,
                           std::vector<Train>::iterator end,
                           std::function<bool(const Train&)> predicate) {
    std::vector<Train> result;
    for(auto it = std::find_if(begin, end, predicate); it != end; it = std::find_if(++it, end, predicate)) {
        result.push_back(*it);
    }
    return result;
}

size_t timeToMins(const std::string& timestamp) {
    return atoi(timestamp.substr(0, 2).c_str()) * 60 + atoi(timestamp.substr(3, 2).c_str());
}


int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Обязательный параметр: infile" << std::endl;
        return 0;
    }

    std::string filename = argv[1];

    std::ifstream infile (filename);
    if(!infile || !infile.is_open()) {
        std::cout << "Не удалось открыть файл " << filename << std::endl;
        return 0;
    }

    std::vector<Train> trains;
    std::regex expr("[ ]*([0-9]+)[ ]*;[ ]*([a-zA-Z ]+?)[ ]*;[ ]*([a-zA-Z]+)[ ]*;[ ]*([0-9]{2}:[0-9]{2})[ ]*;[ ]*([0-9]+)[ ]*");
    std::string buf;
    while(true) {
        std::getline(infile, buf);
        if(buf.size() == 0 || buf[0] == '\n' || buf[0] == '\r')
            break;

        std::match_results<std::string::const_iterator> match;
        if(!std::regex_match(buf, match, expr)) {
            std::cout << "Ошибка в строке: " << buf << std::endl;
            continue;
        }

        size_t num = atoi(match[1].str().c_str());
        std::string dest = match[2].str();
        std::string type_s = match[3].str();
        Train::train_type_t type = type_s == "express" ?
                    Train::train_type_t::EXPRESS :
                    Train::train_type_t::PASSENGER;

        std::string dep_time = match[4].str();
        size_t ride_time = atoi(match[5].str().c_str());

        trains.push_back(Train(num, type, dest, dep_time, ride_time));
    }

    std::sort(trains.begin(), trains.end(), [](const Train& t1, const Train& t2) {
        return timeToMins(t1.departTime) < timeToMins(t2.departTime);
    });

    std::cout << "Поезда, отсортировынные по времени отправления: ";
    std::cout << trains << std::endl;

    std::string rangeStart = "08:00";
    std::string rangeEnd = "12:00";
    auto trainsInRange = findAll(trains.begin(), trains.end(), [&](const Train& t) {
        return timeToMins(t.departTime) >= timeToMins(rangeStart) &&
               timeToMins(t.departTime) <= timeToMins(rangeEnd);
    });

    std::cout << "Поезда, отправляющиеся между " << rangeStart << " и " << rangeEnd << ": ";
    std::cout << trainsInRange << std::endl;

    std::string arrivalPoint = "Minsk";

    auto trainsToPoint = findAll(trains.begin(), trains.end(), [&](const Train& t) {
        return t.destination == arrivalPoint;
    });

    std::cout << "Поезда, отправляющиеся в " << arrivalPoint << ": ";
    std::cout << trainsToPoint << std::endl;

    auto expressTrainsToPoint = findAll(trainsToPoint.begin(), trainsToPoint.end(), [](const Train& t){
        return t.type == Train::train_type_t::EXPRESS;
    });


    std::cout << "Экспрессы, отправляющиеся в " << arrivalPoint << ": ";
    std::cout << expressTrainsToPoint << std::endl;

    auto fastestTrainToPoint = *std::max_element(trainsToPoint.begin(),
                                                trainsToPoint.end(),
                                                [&](const Train& t1, const Train& t2) {
        return t1.rideTime > t2.rideTime;
    });

    std::cout << "Самый быстрый поезд, отправляющийся в " << arrivalPoint << ": ";
    std::cout << fastestTrainToPoint << std::endl;

    return 0;
}
