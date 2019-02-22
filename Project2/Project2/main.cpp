/************************************************************
  main.cpp
  Project2      Group7
 Uzair Akram, Rory Spralls, Reeves Cota
 ReadMe: compile on cse machine using the following commands:
 g++ -std=c++11 main.cpp
 ./a.out
************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// prototypes
static void readFile(string filename, vector< vector<string> >& V, int& a, int& b, int& c);
static void mileStone(vector< vector<string> > V);
static void displayRegion(vector< vector<string> > V);
static void SIRtransition(int &period, int threshold, int InfectionPeriod, int display, vector< vector<string> > &today, vector< vector<int> > num, int i_count);
static void SIRtransitionA(int &period, int threshold, int InfectionPeriod, int display, vector< vector<string> > &today, vector< vector<int> > num, int i_count);

// Global
static int peakDay = 0;


int main(int argc, const char * argv[]) {
    // Variables
    vector< vector<string> > region;      // holds state of all variables
    vector< vector<int> > num;            // holds periods of all "i"s
    int Threshold;
    int Infectious_Period;
    int Display;
    string filename;
    int period = 0;                         // keeps track of period
    
    cout << "Enter the filename: ";
    cin >> filename;
    
    // read file
    readFile(filename, region, Threshold, Infectious_Period, Display);
    
    // print region day 0
    cout << "Day:0" << endl;
    for (int i =0; i < region.size(); i++){
        for (int j =0; j < region[i].size(); j++)
            cout << region[i][j] + " ";
        
        cout << endl;
    }
    cout << endl;
    
    // create num vector
    for (int i =0; i < region.size(); i++) {
        vector<int> tempV;
        for(int j = 0; j < region[i].size(); j++){
            tempV.push_back(0);
        }
        num.push_back(tempV);
    }
    
    // transition function through states
    SIRtransition(period, Threshold, Infectious_Period, Display, region, num, 0);
    
    
    
    
    return 0;
}

 void readFile(string filename, vector<vector<string> >& V, int& a, int& b, int& c){
    // variables
    ifstream inputFile;
    int spaceIndex = 0;
    string infectionPeriod;
    string threshold;
    string display;
    string line;                // line reads
    string temp = "";
    
    inputFile.open(filename);
    
    // If the file successfully opened, process it.
    if (inputFile)
    {
        // Read the numbers from the file and
        // display them.
        getline(inputFile, infectionPeriod);
        cout << infectionPeriod << endl;
        
        for(int i = 0; i < infectionPeriod.size(); i++)
        {
            if(infectionPeriod.at(i) == ':')
                spaceIndex = i;
        }
        try{
            temp = infectionPeriod.substr(spaceIndex+1, infectionPeriod.size());
            a = stoi(temp, nullptr, 10);
        }catch (exception e){
            cout << "Error casting";
        }
        
        getline(inputFile, threshold);
        cout << threshold << endl;
        
        for(int i = 0; i < threshold.size(); i++)
        {
            if(threshold.at(i) == ':')
                spaceIndex = i;
        }

        try{
            temp = threshold.substr(spaceIndex+1, threshold.size());
            b = stoi(temp, nullptr, 10);
        }catch (exception e){
            cout << "Error casting";
        }
        
        getline(inputFile, display);
        cout << display << endl;
        
        for(int i = 0; i < display.size(); i++)
        {
            if(display.at(i) == ':')
                spaceIndex = i;
        }

        try{
            temp = display.substr(spaceIndex+1, display.size());
            c = stoi(temp, nullptr, 10);
        }catch (exception e){
            cout << "Error casting";
        }
        
        
        // read into vector
        while (inputFile >> line)
        {
            
            vector<string> line_vector;
            
            for(int i =0; i < line.length(); i++){
                
                if(line.at(i) != ',' && line.at(i) != '\n'){
                    temp = line.at(i);
                    
                }else{
                    line_vector.push_back(temp);
                }
                
            }
            line_vector.push_back(temp);
            
            V.push_back(line_vector);
            
              line_vector.clear();
        }
            
            // Close the file.
        inputFile.close();
    }else{
                // Display an error message.
                cout << "Error opening the file.\n";
    }
    
    cout << endl;
}

static void mileStone(vector< vector<string> > S){
    int countS = 0;
    int countI = 0;
    int countR = 0;
    int countV = 0;
    
    for (int i =0; i < S.size(); i++) {
        for(int j = 0; j < S[i].size(); j++){
        if(S[i][j].compare("i")==0)
            countI++;
        else if(S[i][j].compare("s") == 0)
            countS++;
        else if(S[i][j].compare("r") == 0)
            countR++;
        else if(S[i][j].compare("v") == 0)
            countV++;
        } 
    }
    cout << "S: " << countS << endl << "I: " << countI << endl << "R: " << countR << endl << "V: " << countV << endl;
}


static void SIRtransition(int &period, int threshold, int InfectionPeriod, int display, vector< vector<string> > &today, vector< vector<int>> infected_period, int i_count){
    
    int InfectiousNeighbor = 0;
    int count_i = 0;
    period++;
    
    // display
    if(period % display == 0){
        cout << "Day:" << period << endl;
    }
    
    vector< vector<string> > tomorrow;
    
    // appending today to tomorrow vector
    for (int i =0; i < today.size(); i++) {
        tomorrow.push_back(today[i]);
    }
    
    
    // loop through vector and checks for SIR states
    for (int i =0; i < today.size(); i++) {
        for(int j = 0; j < today[i].size(); j++){
            
            // max column length
            unsigned long c = today.size()-1;
            // max row length
            unsigned long r = today[i].size()-1;
            
            // look for "s"
            if(today[i][j] == "s"){
                
                // upper right corner
                if(i == 0 && j == r){
                    // down
                    if (today[i+1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-right
                    if (today[i+1][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-left
                    if (today[i+1][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                }
                
                // upper left corner
                if(i == 0 && j == 0){
                        // down
                        if (today[i+1][j] == "i") {
                            InfectiousNeighbor++;
                        }
                        // right
                        if (today[i][j+1] == "i") {
                            InfectiousNeighbor++;
                        }
                        // left
                        if (today[i][r] == "i") {
                            InfectiousNeighbor++;
                        }
                        
                        // lower-right
                        if (today[i+1][j+1] == "i") {
                            InfectiousNeighbor++;
                        }
                        
                        // lower-left
                    if (today[i+1][r] == "i") {
                            InfectiousNeighbor++;
                        }
                }
                
                // lower right corner
                if(i == c && j == r){
                    // up
                    if (today[i-1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-right
                    if (today[i-1][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-left
                    if (today[i-1][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                }
                
                // lower left corner
                if(i == c && j == 0){
                    // up
                    if (today[i-1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][r] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-right
                    if (today[i-1][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-left
                    if (today[i-1][r] == "i") {
                        InfectiousNeighbor++;
                    }
                }
                
                // top side no corner
                if(i == 0 && j != r && j != 0){
                    // down
                    if (today[i+1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-right
                    if (today[i+1][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-left
                    if (today[i+1][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                }
                
                // Bottom no corner
                if(i == c && j != r && j != 0){
                    // up
                    if (today[i-1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-right
                    if (today[i-1][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-left
                    if (today[i-1][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                }
                
                // left side no corners
                if(j == 0 && i!=0 && i!= c){
                    // down
                    if (today[i+1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // up
                    if (today[i-1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][r] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-right
                    if (today[i+1][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-left
                    if (today[i+1][r] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-right
                    if (today[i-1][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-left
                    if (today[i-1][r] == "i") {
                        InfectiousNeighbor++;
                    }
                }
                
                // right side no corners
                if(j == r && i!=0 && i!= c){
                    // down
                    if (today[i+1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // up
                    if (today[i-1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-right
                    if (today[i+1][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-left
                    if (today[i+1][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-right
                    if (today[i-1][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-left
                    if (today[i-1][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                }
                
                // middle
                if(j > 0 && j < r && i > 0 && i < c){
                    // down
                    if (today[i+1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // up
                    if (today[i-1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-right
                    if (today[i+1][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-left
                    if (today[i+1][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-right
                    if (today[i-1][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-left
                    if (today[i-1][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                }
                
                if(InfectiousNeighbor >= threshold){
                    tomorrow[i][j] = "i";
                }
                InfectiousNeighbor = 0;
            }
            
            else if(today[i][j].compare("i") == 0){
                infected_period[i][j]++;
                count_i++;
                
                if (infected_period[i][j] >= InfectionPeriod){
                    tomorrow[i][j] = "r";
                }
            }
            // displlay
            if(period % display == 0)
            {
                cout << tomorrow[i][j] + " ";
            }
        }
        if(period % display == 0)
        {
            cout << endl;
        }
    }// end of loop
    cout << endl;
    
    if(count_i > i_count){
        peakDay = period;
    }
    
    if(count_i > 0){
        SIRtransitionA(period, threshold, InfectionPeriod, display, tomorrow, infected_period, count_i);
    }else if (period % display > 0 && count_i > 0){
        cout << "Day:" << period << endl;
        displayRegion(tomorrow);
    }
    
    // output final counts
    if (count_i == 0){
        // displays final conditions
        cout << "Outbreak Ends: Day " << --period << endl;
        cout << "Peak Day: Day " << --peakDay << endl;
        mileStone(tomorrow);
    }
    
}

static void SIRtransitionA(int &period, int threshold, int InfectionPeriod, int display, vector< vector<string> > &today, vector< vector<int> > infeted_period, int i_count){
    
    
    int InfectiousNeighbor = 0;
    int count_i = 0;
    
    period++;
    
    if(period % display == 0){
        cout << "Day:" << period << endl;
    }
    
    vector< vector<string> > tomorrow;
    
    for (int i =0; i < today.size(); i++) {
        tomorrow.push_back(today[i]);
    }
    
    
    for (int i =0; i < today.size(); i++) {
        for(int j = 0; j < today[i].size(); j++){
            
            // max column length
            unsigned long c = today.size()-1;
            // max row length
            unsigned long r = today[i].size()-1;
            
            if(today[i][j] == "s"){
                
                // upper right corner
                if(i == 0 && j == r){
                    // down
                    if (today[i+1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-right
                    if (today[i+1][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-left
                    if (today[i+1][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                }
                
                // upper left corner
                if(i == 0 && j == 0){
                    // down
                    if (today[i+1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][r] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-right
                    if (today[i+1][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-left
                    if (today[i+1][r] == "i") {
                        InfectiousNeighbor++;
                    }
                }
                
                // lower right corner
                if(i == c && j == r){
                    // up
                    if (today[i-1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-right
                    if (today[i-1][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-left
                    if (today[i-1][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                }
                
                // lower left corner
                if(i == c && j == 0){
                    // up
                    if (today[i-1][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][r] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-right
                    if (today[i-1][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-left
                    if (today[i-1][r] == "i") {
                        InfectiousNeighbor++;
                    }
                }
                
                // top side no corner
                if(i == 0 && j != r && j != 0){
                    // down
                    if (today[i+1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-right
                    if (today[i+1][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-left
                    if (today[i+1][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                }
                
                // Bottom no corner
                if(i == c && j != r && j != 0){
                    // up
                    if (today[i-1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-right
                    if (today[i-1][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-left
                    if (today[i-1][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                }
                
                // left side no corners
                if(j == 0 && i!=0 && i!= c){
                    // down
                    if (today[i+1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // up
                    if (today[i-1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][r] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-right
                    if (today[i+1][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-left
                    if (today[i+1][r] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-right
                    if (today[i-1][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-left
                    if (today[i-1][r] == "i") {
                        InfectiousNeighbor++;
                    }
                }
                
                // right side no corners
                if(j == r && i!=0 && i!= c){
                    // down
                    if (today[i+1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // up
                    if (today[i-1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-right
                    if (today[i+1][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-left
                    if (today[i+1][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-right
                    if (today[i-1][0] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-left
                    if (today[i-1][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                }
                
                // middle
                if(j > 0 && j < r && i > 0 && i < c){
                    // down
                    if (today[i+1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // up
                    if (today[i-1][j] == "i") {
                        InfectiousNeighbor++;
                    }
                    // right
                    if (today[i][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    // left
                    if (today[i][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-right
                    if (today[i+1][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // lower-left
                    if (today[i+1][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-right
                    if (today[i-1][j+1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                    // upper-left
                    if (today[i-1][j-1] == "i") {
                        InfectiousNeighbor++;
                    }
                    
                }
                
                if(InfectiousNeighbor >= threshold){
                    tomorrow[i][j] = "i";
                }
                InfectiousNeighbor = 0;
            }
            
            else if(today[i][j].compare("i") == 0){
                infeted_period[i][j]++;
                count_i++;
                
                if (infeted_period[i][j] >= InfectionPeriod){
                    tomorrow[i][j] = "r";
                }
            }
            
            // displlay
            if(period % display == 0)
            {
                cout << tomorrow[i][j] + " ";
            }
        }
        if(period % display == 0)
        {
            cout << endl;
        }
    }// end of loop
    
    cout << endl;
    
    // determine peakday
    if(count_i > i_count){
        peakDay = period;
    }
    
    
    // call the first function (indirect recurrsion) till region contains "i"
    if(count_i > 0){
        SIRtransition(period, threshold, InfectionPeriod, display, tomorrow, infeted_period, count_i);
    }else if(period % display > 0 && count_i > 0){
        cout << "Day:" << period << endl;
        displayRegion(tomorrow);
    }
    
    // output final counts
    if (count_i == 0){
        // displays final condiotns
        cout << "Outbreak Ends: Day " << --period << endl;
        cout << "Peak Day: Day " << --peakDay << endl;
        mileStone(tomorrow);
    }
}

// function displays vector
static void displayRegion(vector< vector<string> > V){
    
    // displays function
    for (int i =0; i < V.size(); i++) {
        for(int j = 0; j < V[i].size(); j++){
            cout << V[i][j] + " ";
        }
        cout << endl;
    }
    
}
