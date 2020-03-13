#include "Input.h"

using namespace std;

Input::Input() {

}

Input::~Input() {

}

void Input::GetConfiguration() {
	// This gets the users input on if they wish to have the program generate the grid
	// or if they want to specify the filename. The return string will be empty if the
	// user wants to generate the grid randomly

	char answer = ' ';
	IsPreconfigWorld = false;

	cout << "Welcome to the Game of Life." << endl;
	cout << "============================" << endl;
	cout << endl;
	cout << "You have a choice of selecting a file that has a predefined grid set up" << endl;
	cout << "or for the program to create a random grid." << endl;
	cout << endl;
	cout << "Would you like to use a random configuration ? (Y/N) " << endl;
	cin >> answer;

	while ((answer != 'N' && answer != 'n') && 
		   (answer != 'Y' && answer != 'y')) {
		cout << "You entered " << answer << endl;
		cout << "Please enter only Y or N" << endl;
		cin >> answer;
	}

	if (answer == 'N' || answer == 'n') {
		IsPreconfigWorld = true;
		PreconfigFileName = GetFilename();
	}
	else
	{
		IsPreconfigWorld = false;
		GetHeight();
		GetWidth();
		GetDensity();
	}

	GetBoundryMode();

	GetGenerationOutputOption();
}
string Input::GetFilename() {
	// This gets the filename from the user.

	char answer = ' ';
	string filename;

	do {
		cout << "Please enter the filename: " << endl;
		cin >> filename;

		cout << "You entered " << filename << " is that correct ? (Y/N)" << endl;
		cin >> answer;

	} while (answer != 'Y' && answer != 'y');
	
	return filename;
}
void Input::GetHeight() {
	int answer;

	cout << "Enter the height of your world" << endl;
	cin >> answer;

	// https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
	while (std::cin.fail()) {
		std::cout << "Error" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> answer;
	}

	while (answer < 2) {
		cout << "You entered " << answer << endl;
		cout << "The world has to have a hieght greater than 1" << endl;
		cin >> answer;
		// https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
		while (std::cin.fail()) {
			std::cout << "Error" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> answer;
		}
	}

	GridHeight = answer;
}

void Input::GetWidth() {
	int answer;

	cout << "Enter the width of your world" << endl;
	cin >> answer;
	// https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
	while (std::cin.fail()) {
		std::cout << "Error" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> answer;
	}

	while (answer < 2) {
		cout << "You entered " << answer << endl;
		cout << "The world has to have a width greater than 1" << endl;
		cin >> answer;
		// https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
		while (std::cin.fail()) {
			std::cout << "Error" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> answer;
		}
	}

	GridWidth = answer;
}

void Input::GetDensity() {
	float answer;

	cout << "Enter a decimal value for density greater than 0 and less than or equal to 1:" << endl;
	cin >> answer;
	// https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
	while (std::cin.fail()) {
		std::cout << "Error" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> answer;
	}

	while (answer <= 0.0 || answer > 1.0) {
		cout << "You entered " << answer << endl;
		cout << "The value needs to be greater than 0 and less than or equal to 1" << endl;
		cin >> answer;
		// https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
		while (std::cin.fail()) {
			std::cout << "Error" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> answer;
		}
	}

	Density = answer;
}

void Input::GetBoundryMode() {
	// This gets the users input on how they wish to treat the boundry or the mode
	// the game should be played in.

	int answer = 0; // Assume Classic Mode

	cout << endl;
	cout << "The game can be played in three diffent modes:" << endl;
	cout << "0 = Classic mode: All locations off the grid are considered empty." << endl;
	cout << "1 = Doughnut mode: Based on a wrap around approach." << endl;
	cout << "2 = Mirror mode: References off the grid are bounced back." << endl;
	cout << endl;

	cout << "Which mode would you like to choose ? (0,1, or 2)? " << endl;
	cin >> answer;

	while ((answer < 0) ||
		(answer > 3)) {
		cout << "You entered " << answer << endl;
		cout << "Please enter only 0, 1, or 2" << endl;
		cin >> answer;
	}
	
	GameMode = answer;
}

void Input::GetGenerationOutputOption() {
	// This gets the users input on how they want to handle the per generation output.
	// 0 = Pause between generations using system ("pause")
	// 1 = Hit enter between generations
	// 2 = output to a file

	int answer = 0;

	cout << endl;
	cout << "You have a choice of how you want the display of the generations handled" << endl;
	cout << "0 = Pause between generations." << endl;
	cout << "1 = Hit enter between generations" << endl;
	cout << "2 = output to a file" << endl;
	cout << endl;
	cout << "Please select the option you wold like (0,1,2)" << endl;
	cin >> answer;

	while ((answer < 0) ||
		(answer > 3)) {
		cout << "You entered " << answer << endl;
		cout << "Please enter only 0, 1, or 2" << endl;
		cin >> answer;
	}

	OutputMode = answer;

	if (OutputMode == 2) {
		// 2 indicates that the user wants to output to a file so get the filename
		OutputFileName = GetFilename();

		// should redirect output to a file
		//https://stackoverflow.com/questions/20207560/print-function-to-an-output-file
		//https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
		const char* c = OutputFileName.c_str();
		freopen(c, "w", stdout);
	}


}

