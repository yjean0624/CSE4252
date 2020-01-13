//Author: Kwangeon, Xingyue, Tony
//SleepTracerFunctions.cpp
//Thie file contains function implementations for the program

#include "SleepTracer.h"

using namespace std;

//The default input/output file name will be autosave
//Key: date in the form of mm/dd/yyyy (string)
//Value: sleep time (double) with up to hundredth place precision

//Checks if the date is in correct format
bool isValidDate(string date){
	if(date.size() != 10){
		return false;
	} else if((date.at(2) != date.at(5)) && (date.at(5) != '/')){
		return false;
	}
	string mm = date.substr(0,2);
	string dd = date.substr(3,2);
	string yyyy = date.substr(6);
	int month = atoi(mm.c_str());
	int day = atoi(dd.c_str());
	int year = atoi(yyyy.c_str());
	if(month * day * year == 0){ return false; }
	if(0 >= month || 13 <= month){ return false; }
	if(0 >= day || 32 <= day){ return false; }
	if(0 > year){ return false; }
	return true;
}
//Checks if sleep time is non-negative. If there are invalid characters, then time is set to default '0.0'
bool isValidTime(double time){
	return time >= 0.0 && time <= 24.0;
}
//Checks if year is non-negative with four digits. If there are invalid characters, then time is set to default '0'
bool isValidYear(string year){
	if(year.size() != 4){ return false; }
	int y = atoi(year.c_str());
	return y >= 0 ;
}
//Checks if the numerical representation of month is of correct form.
bool isValidMonth(string m){
	if(m.size() != 2){ return false; }
	int month = atoi(m.c_str());
	if(month <=0 || month >= 13){ return false; }
	return true;
}
//Converts number to corresponding month and returns the string; default should not occurs since the function assumes the input is a valid number for the function
string numToMonth(int m){
	switch (m) {
		case 1: return "January";
		case 2: return "February";
		case 3: return "March";
		case 4: return "April";
		case 5: return "May";
		case 6: return "June";
		case 7: return "July";
		case 8: return "August";
		case 9: return "September";
		case 10: return "October";
		case 11: return "November";
		case 12: return "December";
		default: break;
	}
}
//Evaluates the user input for date. Return value is always of the right form.
string userInputDateHandler(){
	string date;
	cout << "Enter the date in mm/dd/yyyy format (ex: 04/05/1987 for April 5, 1987)" << endl;
	cin >> date;
	while(!isValidDate(date)){
		cout << "Invalid date format!!!\nEnter the date in mm/dd/yyyy format (ex: 04/05/1987 for April 5, 1987)" << endl;
		cin >> date;
	}
	return date;
}
//Evaluates the user input for sleep time. If there are invalid characters, then time is set to default '0.0'
double userInputTimeHandler(){
	string temp;
	double hour;
	cout << "Enter the amount of sleep you had for the day in hours. Decimal values will be rounded to the nearest hundredth. Non-numerical input will default to 0.0 hrs." << endl;
	cin >> temp;
	hour = atof(temp.c_str());
	while(!isValidTime(hour)){
		cout << "Invalid time!!!\nEnter the amount of sleep you had for the day in hours. Decimal values will be rounded to the nearest hundredth. Non-numerical input will default to 0.0 hrs." << endl;
		cin >> temp;
		hour = atof(temp.c_str());
	}
	hour = double(int(hour * 100 + 0.5)) / 100;
	return hour;
}
//Evaluates the user input for month. Ensures the returned value is a string from "01" to "12"
string userInputMonthHandler(){
	string month;
	cout << "Enter the numerical representation of the desired month with one leading zero if the month is not October, November, or December: ";
	cin >> month;
	while(!isValidMonth(month)){
		cout << "Invalid month!!!\nEnter the numerical representation of the desired month with one leading zero if the month is not October, November, or December: ";
		cin >> month;
	}
	return month;
}
//Evaluates the user input for year. Ensures the returned value is a string from "0000" to "9999"
string userInputYearHandler(){
	string year;
	cout << "Enter a year with FOUR digits. Place leading zero's in front when necessary: ";
	cin >> year;
	while(!isValidYear(year)){
		cout << "Invalid month!!!\nEnter a year with FOUR digits. Place leading zero's in front when necessary: ";
		cin >> year;
	}
	return year;
}
//Creates new file IO for a new user (OVERRIDES EXISTING data.txt)
map<string, double> createNewData(){
	fstream fout;
	string date;
	double time;
	int num;
	map<string, double> data;
	fout.open("autosave", ios::out);
	if(!fout.is_open()){
		cerr << "Unable to open file autosave" << endl;
		exit(10);
	}else{
		cout << "Enter the number of data sets you wish to enter: ";
		cin >> num;
		for(int c = 0; c < num; c++){
			date = userInputDateHandler();
			time = userInputTimeHandler();			
			addData(&data, date, time);
			fout << date << endl;
			fout << time << endl;
		}
	}
	fout.close();
	return data;
}

//Returns either an empty map or map with data depending on the input file
map<string, double> readSavedData(string fileName){
	ifstream fin;
	string date;
	string temp;
	double sleepTime;
	map<string, double> M;
	fin.open(fileName.c_str(), ios::in);
	if(!fin.is_open()){
		cerr << "Unable to open file " << fileName << endl;
		cout << "Empty array returned" << endl;		
	}
	else{
		while(getline(fin, date)){
			getline(fin, temp);
			sleepTime = atof(temp.c_str());
			M.insert(std::pair<string, double>(date, sleepTime));
		}
		fin.close();
	}
	return M;
}
//Writes data to the output file so that it can be used again next time (OVERRIDES DATA IN fileName)
void writeData(map<string, double> *M, string fileName){
	ofstream fout;
	fout.open(fileName.c_str(), ios::out);
	if(!fout.is_open()){
		cerr << "Unable to open file " << fileName << endl;
	}
	else{
		map<string, double>::iterator it = (*M).begin();
		for(; it != (*M).end(); ++it){
			fout << it->first << endl;
			fout << it->second << endl;
		}
	}
	fout.close();
}
//Adds a single key,value pair to the map if applicable
void addData(map<string, double> *M, string date, double time){
	map<string, double>::iterator it = (*M).find(date);
	if(it != (*M).end()){
		cout << "The date already exists" <<endl;
	}
	else {
		time = double(int(time * 100 + 0.5)) / 100;
		(*M).insert(std::pair<string, double>(date, time));
	}
}
//Deletes a map pair from the map if applicable
void deleteData(map<string, double> *M, string date){
	map<string, double>::iterator it = (*M).find(date);
	if(it != (*M).end()){
		(*M).erase(it);
	}
	else {
		cout << "The date does not exist" << endl;
	}
}
//Returns the sleep time on the date requested
double viewData(map<string, double> *M, string date){
	map<string, double>::iterator it = (*M).find(date);
	if(it != (*M).end()){
		return it->second;
	}
	else {
		cout << "The date does not exist" << endl;
		return -1;
	}
}
//Changes the sleep time data in the map for the date provided
void changeData(map<string, double> *M, string date, double newTime){
	map<string, double>::iterator it = (*M).find(date);
	if(it != (*M).end()){
		newTime = double(int(newTime * 100 + 0.5)) / 100;
		(*it).second = newTime;
	}
	else {
		cout << "The date does not exist" << endl;
	}
}
//Calculates the mean of the map data and returns the value
double calcMean(map<string, double> *M){
	double mean = 0;
	map<string, double>::iterator it = (*M).begin();
	for(; it != (*M).end(); ++it){
		mean += it->second;
	}
	mean /= (*M).size();
	return mean;
}
//Calculates the median of the map data and returns the value
double calcMedian(map<string, double> *M){
	double median = 0;
	list<double> L;
	int c = 0;
	list<double>::iterator itr;
	map<string, double>::iterator it = (*M).begin();
	for(; it != (*M).end(); ++it){
		L.push_back(it->second);
		c++;
	}
	L.sort();
	itr = L.begin();
	for (int i = 0; i < L.size()/2; i++) {
		itr++;
	}
	if (L.size() % 2 == 0) {
		median = (*itr + *--itr)/2;
	}
	else {		
		median = *itr;
	}
	return median;
}
//Calculates the mode of the map data and returns a list of the modes
list<double> calcModes(map<string, double> *M) {
	list<double> modes;
	int counter = 1;
	int maxFrequency = 1;
	list<double>::iterator itr;
	list<double>::iterator it2;
	map<string, double>::iterator it = (*M).begin();
	list<double> L;
	for (; it != (*M).end(); ++it) {
		L.push_back(it->second);
	}
	L.sort();
	for (itr = L.begin(), it2 = ++L.begin(); it2 != L.end(); ++itr, ++it2) {
		if (*itr == *it2) {
			counter++;
			if (counter >= maxFrequency) {
				if (counter > maxFrequency) {
					maxFrequency = counter;
					modes.clear();
				}				
				modes.push_back(*itr);
			}
		}
		else {
			counter = 1;
		}
	}
	return modes;
}
//Calculates the mean for the month specified
double calcMonthMean(map<string, double> *M, string month, string year){
	map<string, double> temp;
	map<string, double>::iterator it = (*M).begin();
	for(; it != (*M).end(); ++it){
		if((it->first).substr(0,2).compare(month) == 0 && (it->first).substr(6).compare(year) == 0){
			temp.insert(std::pair<string, double>(it->first, it->second));
		}
	}
	double mean = calcMean(&temp);
	return mean;
}
//Calculates the median for the month specified
double calcMonthMedian(map<string, double> *M, string month, string year){
	map<string, double> temp;
	map<string, double>::iterator it = (*M).begin();
	for(; it != (*M).end(); ++it){
		if((it->first).substr(0,2).compare(month) == 0 && (it->first).substr(6).compare(year) == 0){
			temp.insert(std::pair<string, double>(it->first, it->second));
		}
	}
	double median = calcMedian(&temp);
	return median;
}
//Calculates the mode for the month specified
list<double> calcMonthModes(map<string, double> *M, string month, string year){
	map<string, double> temp;
	map<string, double>::iterator it = (*M).begin();
	for(; it != (*M).end(); ++it){
		if((it->first).substr(0,2).compare(month) == 0 && (it->first).substr(6).compare(year) == 0){
			temp.insert(std::pair<string, double>(it->first, it->second));
		}
	}
	list<double> modes = calcModes(&temp);
	return modes;
}
//Returns a map with data sets in the specified year
map<string, double> extractDataByYear(map<string, double> *M, string year){
	map<string, double> temp;
	map<string, double>::iterator it = (*M).begin();
	for(; it != (*M).end(); ++it){
		if((it->first).substr(6).compare(year) == 0){
			temp.insert(std::pair<string, double>(it->first, it->second));
		}
	}
	return temp;
}

//Plot data using gnuplot
void plot(map<string, double> *M, string year){
	map<string, double> data = extractDataByYear(M, year);
	if(data.size() <= 1){
		cout << "There must be at least two data points for the year " << year << endl;
	}
	else{
		ofstream fout;
		fout.open((year + "PlotData.output").c_str(), ios::out);
		if(!fout.is_open()){
			cerr << "Unable to open file " << year << "PlotData.output" << endl;
		}
		else{
			for(map<string, double>::iterator it = data.begin(); it != data.end(); ++it){
				fout << (it->first).substr(0,5) << " " << it->second << endl;;
			}
			string begin = ((data.begin()) -> first).substr(0,5);
			string end = ((--data.end()) -> first).substr(0,5);
			FILE *gp = popen(("gnuplot -e \"filename='" + year + "PlotData.output'\" input.plg\n").c_str(), "w");
			ofstream fout;
			fout.open("input.plg");
			fout << "set terminal png size 1280,960\n";
			fout << "set output '" << year << "LineGraph.png'\n";
			fout << "set timefmt '%m/%d'\n";
			fout << "set xdata time\n";
			fout << "set xrange ['" << begin << "':'" << end << "']\n";
			fout << "set format x '%m/%d'\n";
			fout << "set style line 1 lt 9 lw 2 pt 7 ps 2\n";
			fout << "set key off\n";
			fout << "set title 'Sleep Time for Year " << year << "'\n";
			fout << "set xlabel 'Date (month/day)'\n";
			fout << "set ylabel 'Sleep Time (hours)'\n";
			fout << "set yrange [\"0.0\":\"24.0\"]\n";
			fout << "plot '" << year << "PlotData.output' using 1:2 ls 1 with linespoints\n"; 
			fout.close();
			fclose(gp);
			system(("gio open " + year + "LineGraph.png").c_str());
			system("rm input.plg");
			system(("rm " + year + "PlotData.output").c_str());
		}
	}
}
