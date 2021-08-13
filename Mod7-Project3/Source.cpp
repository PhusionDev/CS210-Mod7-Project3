/**
 * Corner Grocer Purchase History Utility
 * 
 * This application provides a menu allowing a user to:
 * 1.) Print a list of items purchased and how many were purchased in a day.
 * 2.) Print a purchase frequency in a day for a specified item.
 * 3.) Print a histogram representing the purchase frequency of all items in a day.
 * 4.) Exit the application
 * 
 * @author Jared Hodgkins
 * @date August 11th, 2021
 */

#include <Python.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

bool quit = false;

/**
 * This data structure simply holds the values for an item
 * and the amount of times it was purchased
 */
struct PurchaseData {
	string itemName;    // hold the item name
	int count; // hold the purchase frequency
};

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/**
 * This function opens a specified file and reads the data line by line
 * and stores the values into a PurchaseData struct and ultimately into
 * a vector of PurchaseData and is then returned.
 * @param fileName the path/name of the file to be opened
 * @return a vector representing the day's purchased items
 */
vector<PurchaseData> GetFrequencyDataFromFile(string fileName) {
	ifstream inFS;  // create an input file stream
	vector<PurchaseData> itemPurchaseData;  // create a vector to store cities/temps in °F
	PurchaseData currentData;   // create a structure to hold current item and purchase count
	string currentLine;	// store the current line being read from file

	inFS.open(fileName, ios::in);    // open specified file
	if (!inFS.is_open()) {  // check if file could not be opened
		cout << "Could not open file: " << fileName << endl;
		return vector<PurchaseData> {}; // return an empty vector
	}

	while (!inFS.eof()) {   // read until end of file
		getline(inFS, currentLine);	// get the current line and store the contents
		
		if (!(currentLine == "")) {	// check if current line is not empty
			stringstream ss(currentLine);	// create a stringstream from the data in current line

			ss >> currentData.itemName;	// store the first value in the string stream (item name) into current data
			ss >> currentData.count;	// store the second value in the string stream (item frequency) into current data

			itemPurchaseData.push_back(currentData);    // add current data to vector
		}
	}

	inFS.close();   // close the file stream

	return itemPurchaseData;    // return the vector of items purchased
}

/**
 * Prints a textual graphic display representing the purchase frequency of each
 * item sold for the day.
 */
void PrintPurchaseHistogram() {
	vector<PurchaseData> data = GetFrequencyDataFromFile("frequency.dat");	// load the data from file and get a vector of data

	for (unsigned int i = 0; i < data.size(); ++i) {	// loop through each purchased item's data
		cout << data.at(i).itemName << " ";	// print the item name
		for (unsigned int j = 0; j < data.at(i).count; ++j) {	// loop for each time item was purchased
			cout << "*";	// print an asterisk representing an item was purchased
		}
		cout << endl;
	}
}

/**
 * Takes a selection made by user and decides which action to perform
 * @param selection represents the selection entered from user's input
 */
void ProcessMenuSelection(string selection) {
	cout << endl;

	// Option 4: Exit application
	if (selection == "4") {
		quit = true;	// set global quit variable to true
		cout << "Exiting application..." << endl;	// display exit message
		return;
	}

	// Option 1: Print purchase frequency of all items
	if (selection == "1") {
		cout << "Printing report of today's purchased items..." << endl;

		// call Python method to print purchase frequency of all items
		CallProcedure("PrintItemsPurchasedFrequency");
		cout << endl;
		return;
	}

	// Option 2: Print frequency for specific item
	if (selection == "2") {
		string userInput;	// define a variable to hold item name to search for from user input

		cout << "Which item would you like to view purchase frequency for?:" << endl;
		cin.ignore();	// clear any existing input in cin buffer
		cin >> userInput;	// get item name from user

		// call Python method to get purchase frequency of specific item
		cout << userInput << ": " << callIntFunc("PrintItemPurchaseFrequency", userInput) << endl;

		cout << endl;

		return;
	}

	// Option 3: Print histogram of day's purchase frequencies.
	if (selection == "3") {
		cout << "Generating Histogram Report..." << endl;

		// call Python method to generate a frequency.dat file for a day's purchases
		CallProcedure("GeneratePurchaseFrequencyReport");
		PrintPurchaseHistogram();	// print the histogram based on data from frequency.dat

		cout << endl;
		return;
	}

	cout << "Please enter a valid selection..." << endl << endl;
}

/**
 * Prints an application menu for the user, displaying the choices
 * available to them.
 */
void PrintMenu() {
	cout << "             Corner Grocer Sales History Utility" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "1. Display today's items purchased report" << endl;
	cout << "2. Display today's purchase report for a specific item" << endl;
	cout << "3. Display histogram of today's purchased items" << endl;
	cout << "4. Exit Application" << endl;
	cout << "Please enter your selection as a number 1-4:" << endl;
}

int main()
{
	string userSelection;	// holds the selection a user makes

	while (!quit) {	// loop while global application quit state is false
		PrintMenu();	// Print the application menu
		cin >> userSelection;	// get menu selection from user
		ProcessMenuSelection(userSelection);	// process the user's menu selection
	}

	return 0;
}