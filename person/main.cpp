#include <iostream>
#include "person.h"
#include "student.h"
#include "teacher.h"
#include <vector>
#include <functional>

class Menu {
    typedef std::function<void(void)> callback_t;
    std::vector<std::pair<std::string, callback_t>> _actions;

public:
    void add_action(const std::string& descr,
                    const callback_t& callback) {
        _actions.push_back({descr, callback});
    }

    int run() {
        int choice = -1;
        while (true) {
            std::cout << "Choose one of the actions:\n";
            std::cout << "0. Exit\n";
            for(int i = 0; i < _actions.size(); ++i) {
                std::cout << i + 1 << ". " << _actions[i].first << "\n";
            }

            std::cin >> choice;
            if( choice > _actions.size() || choice < 0 )
                continue;

            _actions[choice-1].second();
        }
    }
};

int main(int argc, char* argv[]) {
    std::vector<Person*> persons;

    Menu menu;
    menu.add_action("Enter a new student", [&]() {
        std::string name;
        uint grade;
        uint group;
        std::cout << "Enter name: ";
        std::cin.ignore(1, '\n');
        std::getline(std::cin, name);
        std::cout << "Enter grade: ";
        std::cin >> grade;
        std::cout << "Enter group: ";
        std::cin >> group;

        persons.push_back(new Student{name.c_str(), grade, group});
    });

    menu.add_action("Enter a new teacher", [&]() {
        std::string name;
        std::string department;
        std::cout << "Enter name: ";
        std::cin.ignore(1, '\n');
        std::getline(std::cin, name);
        std::cout << "Enter department: ";
        std::getline(std::cin, department);
        persons.push_back(new Teacher{name.c_str(), department.c_str()});
    });

    menu.add_action("Print students list", [&]() {
        if(persons.empty()) {
            std::cout << "there are no students in the list\n";
            return;
        }
        std::cout << "students: \n";
        for(auto personPtr : persons) {
            if(dynamic_cast<Student*>(personPtr)) {
                std::cout << (*personPtr) << std::endl;
            }
        }
    });

    menu.add_action("Print teachers list", [&]() {
        if(persons.empty()) {
            std::cout << "there are no teachers in the list\n";
            return;
        }
        std::cout << "teachers: \n";
        for(auto personPtr : persons) {
            if(dynamic_cast<Teacher*>(personPtr)) {
                std::cout << (*personPtr) << std::endl;
            }
        }
    });

    while(true) {
        menu.run();
    }

    return 0;
}
