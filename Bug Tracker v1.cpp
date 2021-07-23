//very basic program to, as filename suggests, track bugs

//original program design can be found at geeksforgeeks.org/bug-tracking-system
//I've taken inspiration from there, rewrote it in C++ since that's the language I'm more familiar with,
//and will tweak what I see fit as I need to

/* TO-DO:
- (possibly) change time-dependent functions to rely on <chrono> instead of current <ctime>
- fix strcat_s in fileBug to work with string variables
    -> find a way to get strings to work with this project in the first place
- see about making this its own library
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

int main()
{
    cout << "**************************";
    cout << "BUG TRACKING SYSTEM";
    cout << "**************************" << "\n";

    int number, i = 1;

    //bug ID initialized to 0
    int id = 0;

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
    char name[20], bugType[50];
    string bugDescription;
    string bugPriority;
    //int bugStatus; commented out since VS noted it's an unreferenced variable

    fstream ifile;

    //user name
    cout << "Enter your name: " << "\n";
    cin >> name;
    char ids[10];
    _itoa_s(id, ids, 10);
    strcat_s(name, ids);
    char ex[] = ".txt";
    strcat_s(name, ex);

    //filename of the bug
    cout << "Filename: " << name << "\n";
    ifile.open(name);

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
    cin >> bugType;

    //bug type
    ifile << "TYPE OF BUG: " << "\n" << bugType;
    ifile << "\n";

    //bug priority
    cout << "Enter bug priority:" << "\n";
    cin >> bugPriority;

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
    char name[50];
    string nameStr(name); //leaving this unused for the moment until I can get strcat_s (or an equivalent) to work with actual strings

    //bug file name
    cout << "Enter file name: " << "\n";
    cin >> name;
    char ex[] = ".txt";
    strcat_s(name, ex);
    
    //opening the bug in append mode
    ifile.open(name, ios_base::app);

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
    cout << "**************************";

    ifstream ifile;
    char name[50];

    //asking the filename report the bug of the file
    cout << "Enter the file name:" << "\n";
    cin >> name;
    char ex[] = ".txt";
    strcat_s(name, ex);

    //opening the file in read mode
    //subsequent code heavily altered from original gfg's code upon implementation - updated to C++ standards
    ifile.open(name);

    while (!ifile.eof())
    {
        cout << ifile.rdbuf();
    }

    ifile.close();
}