#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

// defining PRE_RELEASE directive
#define PRE_RELEASE

// student data information
struct STUDENT_DATA {
	std::string firstName;
	std::string lastName;

	#ifdef PRE_RELEASE
		std::string email;
	#endif
	};

// vector to store student data objects
std::vector<STUDENT_DATA> student_data;

int main(void) {
	STUDENT_DATA sd;

	// if PRE_RELEASE then open StudentData_Emails.txt file
	// else open StudentData.txt
	#ifdef PRE_RELEASE
		std::cout << "Application is running pre-release source code" << std::endl << std::endl;

		std::ifstream file("StudentData_Emails.txt");
	#else
		std::cout << "Application is running standard source code" << std::endl << std::endl;

		std::ifstream file("StudentData.txt");
	#endif

	// exit the application if cannot open the file
	if (!file.is_open()) {
		std::cout << "Wasn't able to open the file!!" << std::endl;

		return -1;
	};

	std::string line;

	// loop through each line of the file
	while (std::getline(file, line)) {
		std::istringstream ss(line);

		std::getline(ss, sd.lastName, ',');

		// if PRE_RELEASE mode then get firstName and email
		// else only get the first name.
		#ifdef PRE_RELEASE
			std::getline(ss, sd.firstName, ',');
			std::getline(ss, sd.email);
		#else
			std::getline(ss, sd.firstName);
		#endif

		// remove extra whitespace from first name
		sd.firstName = sd.firstName.substr(1, sd.firstName.length() - 1);

		// push the student object into the vector
		student_data.push_back(sd);

		// set the object values to default
		sd.firstName = "";
		sd.lastName = "";

		#ifdef PRE_RELEASE
			sd.email = "";
		#endif
	};

	// close the file
	file.close();

	// if in debug mode then print data
	#ifdef _DEBUG
		for (int i = 0; i < student_data.size(); i++) {
			std::cout << student_data[i].lastName << ", " << student_data[i].firstName;

			#ifdef PRE_RELEASE
				std::cout << ", " << student_data[i].email << std::endl;
			#else
				std::cout << std::endl;
			#endif
		};
	#endif

	return 1;
};