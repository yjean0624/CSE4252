//Author: Kwangeon, Xingyue, Tony
//SleepTracer.h file

//Preprocessor Directives
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <climits>
#include <iterator>
#include <map>
#include <list>

//function prototypes
bool isValidDate(std::string);
bool isValidTime(double);
bool isValidYear(std::string);
bool isValidMonth(std::string);
std::string numToMonth(int);
std::string userInputDateHandler();
double userInputTimeHandler();
std::string userInputMonthHandler();
std::string userInputYearHandler();
std::map<std::string, double> createNewData();
std::map<std::string, double> readSavedData(std::string);
void writeData(std::map<std::string, double>*, std::string);
void addData(std::map<std::string, double>*, std::string, double);
void deleteData(std::map<std::string, double>*, std::string);
double viewData(std::map<std::string, double>*, std::string);
void changeData(std::map<std::string, double>*, std::string, double);
double calcMean(std::map<std::string, double>*);
double calcMedian(std::map<std::string, double>*);
std::list<double> calcModes(std::map<std::string, double>*);
double calcMonthMean(std::map<std::string, double>*, std::string, std::string);
double calcMonthMedian(std::map<std::string, double>*, std::string, std::string);
std::list<double> calcMonthModes(std::map<std::string, double>*, std::string, std::string);
std::map<std::string, double> extractDataByYear(std::map<std::string, double>*, std::string);
void plot(std::map<std::string, double>*, std::string);
