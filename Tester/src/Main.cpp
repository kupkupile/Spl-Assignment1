#include "Restaurant.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

Restaurant* backup = nullptr;

// Forward declartion
bool compareOutput(string output_file, string expected_output_file, bool toVerb);

int main(int argc, char** argv){
    string test_number = argv[2];
    string path = "PUT ABSOLUTE PATH TO YOUR PROJECT FOLDER HERE";
    // Exmaple:
    // string path = "/home/shaked/Documents/assignment1";
    string command_file = "/inputFiles/cmd" + test_number + ".txt";
    string output_file = "/outputFiles/result" + test_number + ".txt";
    string expected_output_file = "/outputFiles/expcted" + test_number + ".txt";
    
    ifstream commands(path + command_file); // create new cin
    streambuf *cinbuf = cin.rdbuf(); // backup the old cin
    cin.rdbuf(commands.rdbuf()); // redirect cin to the file
    
    ofstream output(path + output_file); // create new cout
    streambuf *coutbuf = cout.rdbuf(); // backup the old cout
    cout.rdbuf(output.rdbuf()); // redirect cout to the file
    //////////////////////////////////////////////////////////////////////////////////////////////
    
    if(argc!=4){
        cout << "usage: rest <config_path>" << endl;
        return 0;
    }
    
    string configurationFile = argv[1];
    Restaurant rest(configurationFile);
    rest.start();
    
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    cin.rdbuf(cinbuf); // restore cin
    cout.rdbuf(coutbuf); // restore cout
    commands.close(); // always close after you are done
    output.close(); // always close after you are done
    
    bool result = compareOutput(path + output_file, path + expected_output_file, (strcmp(argv[3], "-v") == 0));
    cout << (result ? "PASS" : "FAIL") << endl;
    
    return 0;
}

bool compareOutput(string output_file, string expected_output_file, bool toVerb) {
    vector<string> lines;
    ifstream file;
    string line;
    bool result = true;
    
    file.open(output_file);
    if(!file.fail()) {
        while(getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        cout << "Error couldn't open output_file" << endl;
        file.close();
        return false;
    }
    
    file.open(expected_output_file);
    if(!file.fail()) {
        int counter = 0;
        while(getline(file, line)) {
            if(toVerb) {
                cout << "Output(" << (counter+1) << "):\t" << lines[counter] << endl;
                cout << "Expected(" << (counter+1) << "):\t" << line;
                if(line != lines[counter]) {
                    cout << "\tFAILED" << endl;
                    result = false;
                } else
                    cout << "\tPASS" << endl;
            } else {
                if(line != lines[counter]) {
                    cout << "Output(" << (counter+1) << "):\t" << lines[counter] << endl;
                    cout << "Expected(" << (counter+1) << "):\t" << line << endl;
                    result = false;
                }
            }
            counter++;
        }
        file.close();
    } else {
        cout << "Error couldn't open expected_output_file" << endl;
        file.close();
        return false;
    }
    
    return result;
}
