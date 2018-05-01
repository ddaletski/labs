#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

template<class T>
std::ostream& operator << (std::ostream& s, const std::vector<T>& vec) {
	s << "[ ";
	for (int i = 0; i < vec.size() - 1; ++i) {
		s << vec[i] << ", ";
	}
	s << vec.back() << " ]";
	return s;
}

struct SMark {
	std::string subject;
	int mark;

	friend std::ostream& operator << (std::ostream& s, const SMark& mark) {
		s << mark.subject << ": " << mark.mark;
		return s;
	}
};

struct SStudData {
	std::string name;
	int number;
	std::vector<SMark> marks;

	friend std::ostream& operator << (std::ostream& s, const SStudData& stud) {
		s << "name: " << stud.name << "\nnumber: " << stud.number << "\nmarks: " << stud.marks;
		return s;
	}
};

std::vector<SMark> marksFromString(const std::string& s) {
	std::istringstream sstream(s);
	std::string buf;

	std::vector<SMark> marks;
	while (std::getline(sstream, buf, ';')) {
		SMark mark;
		size_t delim_pos = buf.find(':');
		mark.subject = buf.substr(0, delim_pos);
		mark.mark = atoi(buf.substr(delim_pos + 1, buf.length() - delim_pos).c_str());
		marks.push_back(mark);
	}

	return marks;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Please, provide input file name\n";
		system("pause");
		return 0;
	}

	std::ifstream infile(argv[1]);
	if (!infile) {
		std::cout << "No such file: " << argv[1] << "\n";
		system("pause");
		return 0;
	}

	if (!infile.is_open()) {
		std::cout << "Error opening file " << argv[1] << "\n";
		system("pause");
		return 0;
	}

	std::map<int, SStudData> students;

	while (!infile.eof()) {
		SStudData student;
		std::string s;
		std::getline(infile, s);

		if (infile.eof())
			break;

		student.number = atoi(s.c_str());
		std::getline(infile, s);
		student.name = s;
		std::getline(infile, s);
		student.marks = marksFromString(s);

		students[student.number] = student;
	}

	for (auto kv : students) {
		std::cout << kv.second << "\n\n";
	}

	system("pause");
	return 0;
}