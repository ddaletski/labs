#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
#include <locale>


struct Student {
    Student (const std::string& name, size_t grade, size_t group)
        : name(name), grade(grade), group(group) {}

    size_t grade;
    size_t group;
    std::string name;

    friend std::ostream& operator << (std::ostream& str, const Student& stud) {
        str << stud.name << " ; " << stud.grade << " ; " << stud.group;
        return str;
    }
};


int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Обязательный параметр: infile" << std::endl;
        return 0;
    }

    std::string filename = argv[1];
    std::string outname1 = "out1_" + filename;
    std::string outname2 = "out2_" + filename;

    std::ifstream infile (filename);
    if(!infile || !infile.is_open()) {
        std::cout << "Не удалось открыть файл " << filename << std::endl;
        return 0;
    }

    std::ofstream outfile1 (outname1);
    std::ofstream outfile2 (outname2);

    std::vector<Student> students;
    std::regex expr("[ ]*([^;]+?)[ ]*;[ ]*([0-9]+)[ ]*;[ ]*([0-9]+)[ ]*");
    std::string buf;
    while(true) {
        std::getline(infile, buf);
        if(buf == "")
            break;
        std::match_results<std::string::const_iterator> match;
        if(!std::regex_match(buf, match, expr)) {
            std::cout << "Ошибка в строке " << buf << std::endl;
            break;
        }

        std::string name = match[1].str();
        std::string group = match[2].str();
        std::string grade = match[3].str();
        students.push_back(Student(name, atoi(group.c_str()), atoi(grade.c_str())));
    }

    std::vector<Student> students2 = students;

    std::sort(students.begin(), students.end(), [](const Student& s1, const Student& s2) {
        return s1.name < s2.name;
    });

    std::sort(students2.begin(), students2.end(), [](const Student& s1, const Student& s2) {
        if(s1.grade < s2.grade)
            return true;
        else if (s1.grade > s2.grade)
            return false;
        else {
            if (s1.group < s2.group)
                return true;
            else if (s1.group > s2.group)
                return false;
            else {
                return s1.name < s2.name;
            }
        }
    });

    std::for_each(students.begin(), students.end(), [&](const Student& s) {
        outfile1 << s << "\n";
    });

    std::for_each(students2.begin(), students2.end(), [&](const Student& s) {
        outfile2 << s << "\n";
    });

    return 0;
}
