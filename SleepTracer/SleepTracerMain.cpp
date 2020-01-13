//Author: Kwangeon, Xingyue, Tony
//function.cpp

#include "SleepTracer.h"

using namespace std;

//The default input/output file name will be autosave
//Key: date in the form of mm/dd/yyyy (string)
//Value: sleep time (double) with up to hundredth place precision

//MAIN
int main(){
	ifstream fin;
	fin.open("autosave");
	cout.precision(2);
	cout << fixed;
	string time, fileName, month, year;
	double hour;
	int size;
	map<string, double>::iterator iter;
	map<string, double> M;
	list<double> modes;
	list<double>::iterator it;
	if(!fin.is_open()){
		cout << "Hello, new user!\nThis program will keep track of your hours of sleep." << endl;
		M = createNewData();
	}else{
		fin.close();
		M = readSavedData("autosave");
	}
	char choice;
	do{
		cout << "********************MENU********************" << endl;
		cout << "A. Create new sets of data (Default File: autosave)" << endl;
		cout << "B. Read in saved data from a text file" << endl;
		cout << "C. Write data into a text file" << endl;
		cout << "D. Add a data set to the map data holder" << endl;
		cout << "E. Deletes a data set from the map data holder" << endl;
		cout << "F. View record on specific date" << endl;
		cout << "G. Change record for specific date" << endl;
		cout << "H. Calculate mean for the entire data set" << endl;
		cout << "I. Calculate median for the entire data set" << endl;
		cout << "J. Calculate mode for the entire data set" << endl;
		cout << "K. Calculate mean for a specific month and year" << endl;
		cout << "L. Calculate median for a specific month and year" << endl;
		cout << "M. Calculate mode for a specific month and year" << endl;
		cout << "N. Statistical summary for the entire data set" << endl;
		cout << "O. Statistical summary for the specified month and year" << endl;
		cout << "P. Plot data" << endl;
		cout << "Q. Quit" << endl;
		cout << "********************************************" << endl;
		cout << "Enter your selection: ";
		cin >> choice;
		choice = toupper(choice);
		switch (choice) {
			case 'A': 
				M = createNewData(); 
				break;
			case 'B': 
				cout << "Enter the name of the input data file: ";
				cin >> fileName;
				M = readSavedData(fileName);
				break;				 
			case 'C': 
				cout << "Enter the name of the output data file: ";
				cin >> fileName;
				writeData(&M, fileName);
				break; 
			case 'D': 
				time = userInputDateHandler();
				addData(&M, time, userInputTimeHandler()); break; 
			case 'E': 
				deleteData(&M, userInputDateHandler()); 
				break; 
			case 'F': 
				time = userInputDateHandler();
				cout << "The hour of sleep on " << time << " was " << viewData(&M, time) << endl;
				break; 
			case 'G': 
				time = userInputDateHandler();
				changeData(&M, time, userInputTimeHandler()); break; 
			case 'H': 
				cout << "The mean of the data is " << calcMean(&M) << endl; 
				break; 
			case 'I': 
				cout << "The median of the data is " << calcMedian(&M) << endl; 
				break; 
			case 'J': 
				modes = calcModes(&M);
				cout << "The mode(s) of the data is/are "; 
				for(it = modes.begin(); it != modes.end(); ++it){
					cout << *it << " ";
				}
				if(modes.empty()){ cout << "None"; }
				cout << endl;
				break; 
			case 'K': 
				month = userInputMonthHandler();
				year = userInputYearHandler();
				cout << "The mean for the month of " << numToMonth(atoi(month.c_str())) << " in " << year << " is " << calcMonthMean(&M, month, year);
				cout << endl;
				break; 
			case 'L': 
				month = userInputMonthHandler();
				year = userInputYearHandler();
				cout << "The median for the month of " << numToMonth(atoi(month.c_str())) << " in " << year << " is " << calcMonthMean(&M, month, year);
				cout << endl;
				break; 
			case 'M': 
				month = userInputMonthHandler();
				year = userInputYearHandler();
				modes = calcMonthModes(&M, month, year);
				cout << "The mode(s) for the month of " << numToMonth(atoi(month.c_str())) << " in " << year << " is/are "; 
				for(it = modes.begin(); it != modes.end(); ++it){
					cout << *it << " ";
				}
				if(modes.empty()){ cout << "None"; }
				cout << endl;
				break; 
			case 'N': 
				cout << "********************Summary********************" << endl;
				cout << "Number of Data Points: " << M.size() << endl;
				cout << "Mean: " << calcMean(&M) << endl;
				cout << "Median: " << calcMedian(&M) << endl;
				modes = calcModes(&M);
				cout << "Mode(s): "; 
				for(it = modes.begin(); it != modes.end(); ++it){
					cout << *it << " ";
				}
				if(modes.empty()){ cout << "None"; }
				cout << endl;
				cout << "***********************************************" << endl;
				break; 
			case 'O': 
				month = userInputMonthHandler();
				year = userInputYearHandler();
				size = 0;
				iter = M.begin();
				for(; iter != M.end(); ++iter){
					if(((iter -> first).substr(0,2).compare(month) == 0) && ((iter -> first).substr(6).compare(year) == 0)){ size++; }
				}
				cout << "********************Summary********************" << endl;
				cout << "Month: " << month << endl;
				cout << "Year: " << year << endl;
				cout << "Number of Data Points: " << size << endl;
				cout << "Mean: " << calcMonthMean(&M, month, year) << endl;
				cout << "Median: " << calcMonthMedian(&M, month, year) << endl;
				modes = calcMonthModes(&M, month, year);
				cout << "Mode(s): "; 
				if(modes.empty()){ cout << "None"; }
				for(it = modes.begin(); it != modes.end(); ++it){
					cout << *it << " ";
				}
				cout << endl;
				cout << "***********************************************" << endl;
				break; 
			case 'P': 
				plot(&M, userInputYearHandler());
				break; 
			case 'Q': 
				cout << "Exit Program" << endl; 
				break; 
			default: 
				cout << "Invalid Option! Please try again!" << endl; 
				break;
		}
	} while(choice != 'Q');
	writeData(&M, "autosave");
	cout << "Current Data Autosaved to \"autosave\"\n";
}
