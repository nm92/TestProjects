
//<!*---------- MUST BE RUN WITH C++ 11 COMPILER ----------*!>

#include <iostream>             // for input/output
#include <string>               // for strings
#include <fstream>              // for file streams
#include <vector>               // for vectors
#include <bits/stdc++.h>        // for sort() implementation

using namespace std;

struct enrollee
{
    string userid = "";
    string fname = "";
    string lname = "";
    string insurance = "";
    string version = "";
};

// INPUT: 2 enrollee structs/objects
// OUTPUT: bool value (true/false)
// FUNCTION: compare all of the values of 2 enrollee structs/objects
//              if they are NOT the same, return true
//              if they are the same, return false
//              (kind of backwards, but easier to think about when implementing the function in the code below)
bool notSameEnrollee (enrollee e1, enrollee e2)
{
    // I know I could put all this on one return line, but I think this way is more readable

    // if they have the same attributes, then they must be the same enrollee, so return false
    if (e1.userid == e2.userid && e1.fname == e2.fname && e1.lname == e2.lname && e1.insurance == e2.insurance && e1.version == e2.version)
    {
        return false;
    }
    // otherwise if they have different attributes, then they are different enrollees, so return true
    else
    {
        return true;
    }
}

int main()
{
    ifstream inputFile;               // create input file stream for reading only
    vector <enrollee> enrollVector;   // vector of enrollee structs to store each enrollee and their respective data
    int numDuplicates = 0;            // count number of enrollees received from input file w/ duplicate user id's and insurances
    string tempInsurance;             // temp var used to compare insurance strings to check for a new unique insurance

    // open the input file to read
    inputFile.open("input.csv");
    // read the file until we reach the end of the file
    while(!inputFile.eof())
    {
        enrollee tempEnrollee;
        string userid = "";
        string fname = "";
        string lname = "";
        string insurance = "";
        string sversion = "";

        // read in the cols of each row in the excel file, and store them in their respective temp vars
        getline(inputFile,userid,',');
        getline(inputFile,fname,',');
        getline(inputFile,lname,',');
        getline(inputFile,insurance,',');
        getline(inputFile,sversion);

        // assign those temp vars to an enrollee object
        tempEnrollee.userid = userid;
        tempEnrollee.fname = fname;
        tempEnrollee.lname = lname;
        tempEnrollee.insurance = insurance;
        tempEnrollee.version = sversion;

        // push the enrollee object onto the enrollVector
        enrollVector.push_back(tempEnrollee);
    }

    // close inputFile stream
    inputFile.close();

    // this call to sort will sort the enrollVector by insurance, then lname, then fname, then userid, then version
    sort( enrollVector.begin(), enrollVector.end(), []( const enrollee &e1, const enrollee &e2 )
         {
             return tie( e1.insurance, e1.lname, e1.fname, e1.userid, e1.version ) < tie( e2.insurance, e2.lname, e2.fname, e2.userid, e2.version );
         });

    // open an output file stream to write deleted enrollees to
    ofstream outputFile;
    outputFile.open("deleted.csv");

    // loop thru the enrollVector to check for duplicate id's w/ the same insurance
    for (int i = 0; i < enrollVector.size(); i++)
    {
        for (int j = 0; j < enrollVector.size(); j++)
        {
            // if the user id's AND the insurances match AND they are not the same object, then erase the one w/ the lower version
            if ( (enrollVector[i].userid == enrollVector[j].userid) && (enrollVector[i].insurance == enrollVector[j].insurance) && (notSameEnrollee(enrollVector[i], enrollVector[j])) )
            {
                // if i < j, then delete i
                if (enrollVector[i].version < enrollVector[j].version)
                {
                    // print out a message stating which enrollees were received from the input file, but deleted due to a duplicate userid/insurance
                    outputFile << enrollVector[i].userid << "," << enrollVector[i].fname << "," << enrollVector[i].lname << "," << enrollVector[i].insurance << "," << enrollVector[i].version << endl;
                    enrollVector.erase(enrollVector.begin()+i);
                    numDuplicates++;
                }
                // otherwise delete j
                else
                {
                    // print out a message stating which enrollees were received from the input file, but deleted due to a duplicate userid/insurance
                    outputFile << enrollVector[j].userid << "," << enrollVector[j].fname << "," << enrollVector[j].lname << "," << enrollVector[j].insurance << "," << enrollVector[j].version << endl;
                    enrollVector.erase(enrollVector.begin()+j);
                    numDuplicates++;
                }
            }
        }
    }
    // close the output file stream
    outputFile.close();

    // if there were duplicates that were deleted, alert the user w/ further related info
    if (numDuplicates > 0)
    {
        cout << numDuplicates << " enrollee(s) were received from the input file, but deleted due to duplicate id/insurance." << endl;
        cout << "Check deleted.csv file for list of deleted enrollees." << endl;
    }
    // otherwise just alert the user of no duplicates and delete the output file since it is empty and not needed
    else
    {
        remove("deleted.csv");
        cout << "No duplicates detected/deleted." << endl;
    }

    // write sorted data to their respective files
    for (int i = 0; i < enrollVector.size(); i++)
    {
        // if we come across a new insurance name, then start a new file for it
        if (tempInsurance != enrollVector[i].insurance)
        {
            // to reuse outputFile stream, we must close one stream before reopening another
            outputFile.close();
            tempInsurance = enrollVector[i].insurance;
            outputFile.open( tempInsurance + ".csv");
        }

        // write data to the file
        outputFile << enrollVector[i].userid << "," << enrollVector[i].fname << ","
                    << enrollVector[i].lname << "," << enrollVector[i].insurance << ","
                    << enrollVector[i].version << endl;
    }

    // close output file stream
    outputFile.close();

    return 0;
}
