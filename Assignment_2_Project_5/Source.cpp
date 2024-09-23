#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

// student data information
struct STUDENT_DATA {
	std::string firstName;
	std::string lastName;
};

// vector to store student data objects
std::vector<STUDENT_DATA> student_data;

int main(void) {
	STUDENT_DATA sd;

	std::ifstream file("StudentData.txt");

	// exit the application if cannot open the file
	if (!file.is_open()) {
		std::cout << "Wasn't able to open the file!!" << std::endl;

		return -1;
	};

	std::string line;

	while (std::getline(file, line)) {
		std::istringstream ss(line);

		std::getline(ss, sd.lastName, ',');

		std::getline(ss, sd.firstName);

		// remove extra whitespace from first name
		sd.firstName = sd.firstName.substr(1, sd.firstName.length() - 1);

		// push the student object into the vector
		student_data.push_back(sd);

		// set the object values to default
		sd.firstName = "";
		sd.lastName = "";
	};


	// close the file
	file.close();


	// if in debug mode then print data
	#ifdef _DEBUG
		for (int i = 0; i < student_data.size(); i++) {
			std::cout << student_data[i].lastName << ", " << student_data[i].firstName;	
		};
	#endif

	return 1;
};