/************************************************************
 main.cpp
 Uzair Akram
 ReadMe: compile on cse machine using the following command:
 g++ -std=c++11 main.cpp
 Run executable using:
 ./a.out
 ************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// prototypes
static void readFile(string filename, vector< vector<string> >& V);
static void firstPass( vector< vector<string> > &picture);
static void secondPass(vector< vector<string> > &picture, vector<vector<string>> &relation);
static void display(vector< vector<string> > V);
static void biggestObject(vector< vector<string> > &picture);

// Global Variable
static int NUM_OF_OBJECTS = 0;


int main(int argc, const char * argv[]) {
    // Variables
    vector< vector<string> > picture;      // holds the square matrix of '1' and '0' denoting objects and background
    string filename;                       // stores the name of the file
    
    // get the file name
    cout << "Enter the filename: ";
    cin >> filename;
    
    // read file
    readFile(filename, picture);
    
    // display picture
    cout << "Picture:" << endl;
    display(picture);
    
    firstPass(picture);
    
    return 0;
}

void readFile(string filename, vector<vector<string> >& V){
    // variables
    ifstream inputFile;
    string line;                // line reads
    string temp = "";           // stores non demlimeter characters temporarily
    
    inputFile.open(filename);
    // If the file successfully opened, process it.
    if (inputFile)
    {
        // read file into line
        while (inputFile >> line)
        {
            vector<string> line_vector;             //line vector stores line
            // loop though the line
            for(int i =0; i < line.length(); i++){
                // break chracters into vector elements at delimeters
                if(line.at(i) != ',' && line.at(i) != '\n'){
                    temp = line.at(i);
                }else{
                    line_vector.push_back(temp);
                }
            }
            line_vector.push_back(temp);        // append element to line vector
            V.push_back(line_vector);           // append line vector to 2d vector
            line_vector.clear();                // clear line vector for next line
        }
        
        // Close the file.
        inputFile.close();
    }else{
        // Display an error message.
        cout << "Error opening the file.\n";
    }
    
    cout << endl;
}

// first pass function identifies new objects
static void firstPass( vector< vector<string> > &picture){
    
    vector<vector<string>> relation;                        // 2D vector of relationships
    
    int currentlabel = 0;                                   // labeling variable
    
    // loop through vector and look for objects
    for (int i =0; i < picture.size(); i++) {
        for (int j = 0; j < picture[i].size(); j++){
            
            
            // look for "1"
            if(picture[i][j] == "1"){
                
                // case 1
                if((i == 0 && j == 0) || (i == 0 && picture[0][j-1] == "0") || (j == 0 && picture[i-1][0] == "0") || (i>0 && j>0 && picture[i][j-1] == "0" && picture[i-1][j] == "0")){
                    currentlabel++;
                    picture[i][j] = to_string(currentlabel);
                }
                
                // case 2
                else if (i == 0 && picture[0][j-1] != "0"){
                    picture[i][j] = picture[i][j-1];
                }
                else if (j == 0 && picture[i-1][0] != "0"){
                    picture[i][j] = picture[i-1][j];
                }
                else if(picture[i][j-1] == "0" && picture[i-1][j] != "0"){
                    picture[i][j] = picture[i-1][j];
                }
                else if(i>0 && j>0 && picture[i][j-1] != "0" && picture[i-1][j] == "0"){
                    picture[i][j] = picture[i][j-1];
                }
                
                // case 3
                else if(picture[i][j-1] != "0" && picture[i-1][j] != "0"){
                    vector<string> temp;
                    // smaller label
                    if(picture[i-1][j] > picture[i][j-1]){
                        picture[i][j] = picture[i][j-1];
                        // column 0                      column 1
                        temp.push_back(picture[i][j-1]); temp.push_back(picture[i-1][j]);
                        relation.push_back(temp);
                    }else if(picture[i-1][j] < picture[i][j-1]){
                        picture[i][j] = picture[i-1][j];
                        // column 0                       // column 1
                        temp.push_back(picture[i-1][j]); temp.push_back(picture[i][j-1]);
                        relation.push_back(temp);
                    }else{  // if both equal
                        picture[i][j] = picture[i-1][j];
                    }
                }
                
                //continue;
            }   // end of outer if
            
        }
    }// end of loop
    
    // display first pass
    cout << "First-pass: " << endl;
    display(picture);
    
    // set number of objects
    NUM_OF_OBJECTS = currentlabel;
    
    // if a realtionship is found go to second pass
        if(relation.size() > 0)
            secondPass(picture,  relation);
}

// second pass indirect recursive function
static void secondPass(vector< vector<string> > &picture, vector<vector<string>> &relation){
    NUM_OF_OBJECTS--;           // update object count
    
    string from;                // label that will convert
    string to;                  // label 'from' will convert to
    
    to = relation[0][0];        // get 'to' from first column 0
    from = relation[0][1];      // get 'from' from column 1
    
    relation.erase(relation.begin());                                   // remove the first object from vector
    
    // check the relation vector
    for(int i =0; i < relation.size(); i++){
        if(relation[i][0] == to && relation[i][1] == from)              // check if the relation repeats
            relation.erase(relation.begin()+i);                         // remove the repeating relation
        
        if(relation[i][0] == from){                                      // check for a transistive relation
            relation[i][0] = to;
            NUM_OF_OBJECTS--;
        }
    }
    
    // convert 'from' to 'to'
    for (int i =0; i < picture.size(); i++) {
        for(int j = 0; j < picture[i].size(); j++){
            if(picture[i][j] == from){
                picture[i][j] = to;
            }// end of if
            
        }
    }// end of loop
    
    if(relation.size() > 0){                                                // if there are reltions continue resursion
        secondPass(picture, relation);
    }
    else{
        NUM_OF_OBJECTS++;
        cout << "Second Pass:" << endl;
        display(picture);                                                   // otherwise display results
        biggestObject(picture);
    }
}

// displays the vector
static void display(vector< vector<string> > V){
    
    // loop though the 2d vector
    for(int i = 0; i < V.size(); i++){
        for (int j = 0; j < V[i].size(); j++){
            cout << V[i][j] + " ";
        }
        cout << endl;
    }
    cout << endl;
}

// determine bigglest object
static void biggestObject(vector< vector<string> > &picture){
    
    string biggestObject;               // stores the biggest object label
    vector<string> label;               // a vector of unique labels
    int counter[NUM_OF_OBJECTS];        // counter array for each unique label
    int maxCountIndex = 0;              // stores the index of label with maximum count
    
    // initialize a counter array
    for(int n =0; n < NUM_OF_OBJECTS; n++){
        counter[n] = 0;
    }

    // create of vector of unique labels
    for(int i = 0; i < picture.size(); i++){                            // loop through picture
        for (int j = 0; j < picture[i].size(); j++){
            if(picture[i][j] != "0"){                                   // check for non-zero labels
                if(label.size() == 0)                                   // if the label vector is empty
                    label.push_back(picture[i][j]);                     // push back the non-zero label
                else{
                    for(int n =0; n < label.size(); n++){               // otherwise loop through label vector
                        if(picture[i][j] == label[n])                   // if the label isn't new break out of loop
                            break;
                        else
                            label.push_back(picture[i][j]);              // otherwise append new label to label-vector
                    }
                }
            }
        }
    }

    // count the occurance of  a variable
    for(int n =0; n < NUM_OF_OBJECTS; n++){                             // loop through number of objects/labels
        for(int i = 0; i < picture.size(); i++){                        // loop through picture vector
            for (int j = 0; j < picture[i].size(); j++){
                if(picture[i][j] == label[n])                           // check to find current label in picture
                    counter[n] ++;                                      // incrment the correponding count
            }
        }
    }

    // find the label with the maximum count
    int max = counter[0];                                       // max is initialized at first variable of vector
    for(int n = 0; n < NUM_OF_OBJECTS; n++){                    // counter loops through counter-vector

        if(counter[n] > max){                                   // find the maximum index
            max = counter[n];                                   // update maximum
            maxCountIndex = n;                                  // find max counter index
        }

    }

    biggestObject = label[maxCountIndex];                       // set biggest object

    // display
    cout << "Num of objects:" << NUM_OF_OBJECTS << endl << endl;
    cout << "Biggest Object: " << biggestObject << endl;
}
