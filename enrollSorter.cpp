// important to run this program w/ C++ 11 compiler

#include <iostream>
#include <string>                               // for strings
#include <fstream>                              // for file streams
#include <vector>
#include <bits/stdc++.h>                        // for sort() implementation

using namespace std;

struct enrollee
{
    string userid = "";
    string fname = "";
    string lname = "";
    string insurance = "";
    string version = "";
};

int main()
{
    ifstream inputFile;               // create input file stream for reading only
    vector <enrollee> enrollVector;   // array of structs to store each enrollee and their respective data
    int vectorPos = 0;

    // open the input file to read
    inputFile.open("input.csv");
    // read the file until we reach the end
    while(!inputFile.eof())
    {
        enrollee tempEnrollee;
        string userid = "";
        string fname = "";
        string lname = "";
        string insurance = "";
        string sversion = "";

        // read in and store the cols of each row in a temp var
        getline(inputFile,userid,',');
        getline(inputFile,fname,',');
        getline(inputFile,lname,',');
        getline(inputFile,insurance,',');
        getline(inputFile,sversion);

        // assign those vars to an enrollee object
        tempEnrollee.userid = userid;
        tempEnrollee.fname = fname;
        tempEnrollee.lname = lname;
        tempEnrollee.insurance = insurance;
        tempEnrollee.version = sversion;

        // push the enrollee object onto the enrollVector
        enrollVector.push_back(tempEnrollee);

        // count how many enrollees we add for later po
        vectorPos++;
    }

    // close inputFile stream
    inputFile.close();

    // this call to sort will sort the enrollVector by insurance, then lname, then fname, then version
    sort( enrollVector.begin(), enrollVector.end(), []( const enrollee &e1, const enrollee &e2 )
         {
             return tie( e1.insurance, e1.lname, e1.fname, e1.userid, e1.version ) < tie( e2.insurance, e2.lname, e2.fname, e2.userid, e2.version );
         });


    // set up output stream
    string tempInsurance;
    ofstream outputFile;

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
        outputFile << enrollVector[i].lname << "," << enrollVector[i].fname << ","
                    << enrollVector[i].userid << "," << enrollVector[i].insurance << ","
                    << enrollVector[i].version << endl;
    }

    // close outputFile stream
    outputFile.close();

    cout << "Output insurance files created. Check folder." << endl;

    return 0;
}
