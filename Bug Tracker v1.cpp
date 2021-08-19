//very basic program to, as filename suggests, track bugs

/* TO-DO:
- (possibly) change time-dependent functions to rely on <chrono> instead of current <ctime>
- see about making this its own library
- investigate why report() does not exit to driver function
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

void fileBug(int id); //function files bug into the tracking system
void changeStatus(); //function to change status of a desired bug
void report();  //function to report bug in the bug tracking system
                //upon having written the function, this description is a little misleading - the function actually just reads the file and prints it to the screen

//custom written string concatenation function, as strcat was having issues with my compiler
string strCat(string base, string toAdd);

int main()
{
    cout << "**************************";
    cout << "BUG TRACKING SYSTEM";
    cout << "**************************" << "\n";

    int number, i = 1;

    //bug ID initialized to 0
    int id = 0;
    cout << id; //here to check for something

    //while loop to run
    while (i != 0)
    {
        cout << "\n" << "1. FILE A NEW BUG" << "\n";
        cout << "2. CHANGE THE STATUS OF A BUG" << "\n";
        cout << "3. GET BUG REPORT" << "\n";
        cout << "4. EXIT";
        cout << "\n\n" << "ENTER YOUR CHOICE: ";

        cin >> number;

        //using switch to go case by case
        //I hear these are more efficient than if-else blocks
        switch (number)
        {
        case 1: //case to create a new bug
            id++;
            
            fileBug(id);
            break;
        case 2: //case to change bug status
            changeStatus();
            break;
        case 3: //case to report bug - prints to screen
            report();
            break;
        case 4:
            i = 0;
            break;
        default:
            cout << "\n" << "Invalid entry. Please try again." << "\n";
            break;
        }
    }

    return 1;
}

void fileBug(int id)
{
    cout << "*************************";
    cout << "FILING A BUG";
    cout << "*************************" << "\n";

    //current time - modified from gfg's original code because VS is anal about ctime's security for some reason
    //yes, I know time_t is going to output seconds since POSIX epoch, I will figure out a way to change that later
    //yes, I am also aware that <chrono> exists now, and I might end up implementing that instead in the future
    time_t currentTime = time(NULL);
    char timeBuffer[26] = {};
    ctime_s(timeBuffer, 26, &currentTime);

    //I assume that these are here to initialize cstrings for each of these things, except bugStatus of course
    //might just change these to string later, since C++ and all that
    string name;
    string name_ids;
    string fileName;
    string bugType;
    string bugDescription;
    string bugPriority;
    //int bugStatus; commented out since VS noted it's an unreferenced variable

    fstream ifile;

    //including following line in an attempt to fix the first getline in next block being skipped
    cin.ignore();

    //user name
    cout << "Enter your name: " << "\n";
    getline(cin, name);
    string ids;
    ids = to_string(id);
    name_ids = strCat(name, ids);
    string ex = ".txt";
    fileName = strCat(name, ex);

    //filename of the bug
    cout << "Filename: " << fileName << "\n";
    ifile.open(fileName);

    //case when file cannot be created
    if (!ifile)
        cout << "Cannot create output file!" << "\n";

    ifile << "DATE AND TIME : " << ctime_s(timeBuffer, 26, &currentTime);

    //ID in the text file
    ifile << "BUG ID : " << id << "\n";

    //adding new line in text file
    ifile << "\n";

    //Bug ID
    cout << "BUG ID : " << id << "\n";

    ifile << "BUG FILED BY: " << "\n" << name << "\n";
    ifile << "\n";

    cout << "Enter bug type:" << "\n";
    getline(cin, bugType);

    //bug type
    ifile << "TYPE OF BUG: " << "\n" << bugType;
    ifile << "\n";

    //bug priority
    cout << "Enter bug priority:" << "\n";
    getline(cin, bugPriority);

    ifile << "BUG PRIORITY: " << "\n" << bugPriority;
    ifile << "\n";

    //bug description
    cout << "Enter the bug description:\n";
    getline(cin, bugDescription);

    ifile << "BUG DESCRIPTION: " << "\n" << bugDescription;
    ifile << "\n";

    cout << "Status of bug:" << "\n";
    cout << "1. NOT YET ASSIGNED" << "\n";
    cout << "2. IN PROCESS" << "\n";
    cout << "3. FIXED" << "\n";
    cout << "4. DELIVERED" << "\n";
    cout << "ENTER YOUR CHOICE" << "\n";

    int j; //we're going to give this a better name later
    cin >> j;

    //date and time of bug creation
    ifile << "DATE AND TIME:" << ctime_s(timeBuffer, 26, &currentTime);

    ifile << "BUG STATUS: ";

    //switchboard for bug status
    switch (j)
    {
    case 1:
        ifile << "NOT YET ASSIGNED" << "\n";
        break;
    case 2:
        ifile << "IN PROCESS" << "\n";
        break;
    case 3:
        ifile << "FIXED" << "\n";
        break;
    case 4:
        ifile << "DELIVERED" << "\n";
        break;
    default:
        cout << "INVALID CHOICE" << "\n";
        break;
    }

    ifile.close();
}

void changeStatus()
{
    cout << "**************************";
    cout << "Change Status";
    cout << "**************************" << "\n";


    //current time - modified from gfg's original code because VS is anal about ctime's security for some reason
    //yes, I know time_t is going to output seconds since POSIX epoch, I will figure out a way to change that later
    //yes, I am also aware that <chrono> exists now, and I might end up implementing that instead in the future
    time_t currentTime = time(NULL);
    char timeBuffer[26] = {};
    ctime_s(timeBuffer, 26, &currentTime);

    fstream ifile;
    string name;
    string fileName;

    //obligatory conclusion of program-breaking prevention function here
    cin.ignore();

    //bug file name
    cout << "Enter file name: " << "\n";
    getline(cin, name);
    string ex = ".txt";
    fileName = strCat(name, ex);
    
    //opening the bug in append mode
    ifile.open(name, ios_base::app);

    //case when file cannot be opened
    if(!ifile)
        cout << "Cannot open desired file!" << "\n";

    cout << "\n" << "1. NOT YET ASSIGNED" << "\n";
    cout << "2. IN PROCESS" << "\n";
    cout << "3. FIXED" << "\n";
    cout << "4. DELIVERED" << "\n";
    cout << "ENTER YOUR CHOICE: ";

    //change the status
    int k;
    cin >> k;

    ifile << "\n";
    ifile << "DATE AND TIME : " << ctime_s(timeBuffer, 26, &currentTime);

    ifile << "BUG STATUS:";

    //changing the status on the basis of the user input
    switch (k)
    {
    case 1:
        ifile << "NOT YET ASSIGNED" << "\n";
        break;
    case 2:
        ifile << "IN PROCESS" << "\n";
        break;
    case 3:
        ifile << "FIXED" << "\n";
        break;
    case 4:
        ifile << "DELIVERED" << "\n";
        break;
    default:
        cout << "INVALID CHOICE" << "\n";
        break;
    }

    ifile.close();
}

void report()
{
    cout << "**************************";
    cout << "REPORT";
    cout << "**************************" << "\n";

    ifstream ifile;
    string name;
    string fileName;

    //inclusion of program-breaking prevention function here
    cin.ignore();

    //asking the filename report the bug of the file
    cout << "Enter the file name:" << "\n";
    getline(cin, name);
    string ex = ".txt";
    fileName = strCat(name, ex);

    //opening the file in read mode
    //subsequent code heavily altered from original gfg's code upon implementation - updated to C++ standards
    ifile.open(fileName);

    //case when file cannot be opened
    if(!ifile)
        cout << "Cannot open desired file!" << "\n";

    while (!ifile.eof())
    {
        cout << ifile.rdbuf();
    }

    ifile.close();
}

string strCat(string base, string toAdd)
{
    //alternate to c-standard's strcat
    //this function works exclusively with strings, a space between the two different strings was omitted
    //  due to this function being used only in the context of creating/opening files
    
    string meow;
    meow = base + toAdd;

    return meow;
}