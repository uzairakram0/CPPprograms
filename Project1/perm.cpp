/* The pupose of this assignment is to figure out:
 if a particualr permutation of N numbers is divisble by N*/

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
// prototypes
void hexPermutations();
int toHex(string num);

int main(){
    vector<unsigned long long int> N1;//Vector to store 1-digit permutation solutions
    vector<unsigned long long int> N2;//Vector to store 2-digit permutation solutions
    vector<unsigned long long int> N3;//Vector to store 3-digit permutation solutions
    vector<unsigned long long int> N4;//Vector to store 4-digit permutation solutions
    vector<unsigned long long int> N5;//Vector to store 5-digit permutation solutions
    vector<unsigned long long int> N6;//Vector to store 6-digit permutation solutions
    vector<unsigned long long int> N7;//Vector to store 7-digit permutation solutions
    vector<unsigned long long int> N8;//Vector to store 8-digit permutation solutions
    vector<unsigned long long int> N9;//Vector to store 9-digit permutation solutions
    vector<unsigned long long int> N10;//Vector to store 10-digit permutation solutions
    
    unsigned long long int t=0;
    
    // Single digit
    for(unsigned int n= 1; n < 10; n++){
        if(n % 1==0){
            N1.push_back(n);//Add solutions to vector
        }
    }
    
    // 2 digit
    for(int n = 1; n < 10; n++){
        // Loop  1-9
        char cn = '0' + n;
        // Casting int n to char (implicit converstion)
        for(unsigned int i = 0; i < N1.size(); i++){
            // Loop through previous vector
            string str = to_string(N1[i]);
            // Converting int vector elements to int
            for(int j = 0; j < str.length(); j++){
                // Loop through the string to Compare
                if(cn != str.at(j)){
                    // Compare vector element to char num to avoid repeating numbers in permuatation
                    int num = N1[i]*10 + n;
                    // Generate new num
                    if(num % 2 == 0){
                        // Check to see if it's divisible by num of digits
                        N2.push_back(num);
                    }
                    // Add num to vector
                }
            }
        }
    }
    
    //3 digit
    for(unsigned int i=0; i<N2.size(); i++){
        //loop through previous vector
        int num;//variable to be used to assigne value of 3 digit solution
        for(int n=1; n<10; n++){
            //loop through 1-9
            char cn='0'+n;
            string str = to_string(N2[i]);
            if((cn != str.at(0)) && (cn != str.at(1)) && (N2[i]*10+n)%3 == 0){
                num = N2[i]*10+n;
                
                N3.push_back(num);
            }
        }
    }
    
    //4 digit
    for(unsigned int i=0; i<N3.size(); i++){
        int num;
        for(int n=1; n<10; n++){
            char cn='0'+n;
            string str = to_string(N3[i]);
            if((cn != str.at(0)) && (cn != str.at(1)) && (cn != str.at(2)) && (N3[i]*10+n)%4 == 0){
                num = N3[i]*10+n;
                
                N4.push_back(num);
            }
        }
    }
    
    //5 digit
    for(unsigned int i=0; i<N4.size(); i++){
        int num;
        for(int n=1; n<10; n++){
            char cn='0'+n;
            string str = to_string(N4[i]);
            if((cn != str.at(0)) && (cn != str.at(1)) && (cn != str.at(2)) && (cn != str.at(3)) && (N4[i]*10+n)%5 == 0){
                num = N4[i]*10+n;
                
                N5.push_back(num);
            }
        }
    }
    //6 digit
    for(unsigned int i=0; i<N5.size(); i++){
        int num;
        for(int n=1; n<10; n++){
            char cn='0'+n;
            string str = to_string(N5[i]);
            if((cn != str.at(0)) && (cn != str.at(1)) && (cn != str.at(2)) && (cn != str.at(3)) && (cn != str.at(4)) && (N5[i]*10+n)%6 == 0){
                num = N5[i]*10+n;
                
                N6.push_back(num);
            }
        }
    }
    //7 digit
    for(unsigned int i=0; i<N6.size(); i++){
        int num;
        for(int n=1; n<10; n++){
            char cn='0'+n;
            string str = to_string(N6[i]);
            if((cn != str.at(0)) && (cn != str.at(1)) && (cn != str.at(2)) && (cn != str.at(3)) && (cn != str.at(4)) && (cn != str.at(5)) && (N6[i]*10+n)%7 == 0){
                num = N6[i]*10+n;
                
                N7.push_back(num);
            }
        }
    }
    //8 digit
    for(unsigned int i=0; i<N7.size(); i++){
        int num;
        for(int n=1; n<10; n++){
            char cn='0'+n;
            string str = to_string(N7[i]);
            if((cn != str.at(0)) && (cn != str.at(1)) && (cn != str.at(2)) && (cn != str.at(3)) && (cn != str.at(4)) && (cn != str.at(5)) && (cn != str.at(6)) && (N7[i]*10+n)%8 == 0){
                num = N7[i]*10+n;
                
                N8.push_back(num);
            }
        }
    }
    //9 digit
    for(unsigned int i=0; i<N8.size(); i++){
        int num;
        for(int n=1; n<10; n++){
            char cn='0'+n;
            string str = to_string(N8[i]);
            if((cn != str.at(0)) && (cn != str.at(1)) && (cn != str.at(2)) && (cn != str.at(3)) && (cn != str.at(4)) && (cn != str.at(5)) && (cn != str.at(6)) && (cn != str.at(7)) && (N8[i]*10+n)%9 == 0){
                num = N8[i]*10+n;
                
                N9.push_back(num);
            }
        }
    }
    //10 digit
    t=(N9[0]*10)+0;
    if(t%10 == 0){
        N10.push_back(t);
    }
    
    cout << "Count for 1 digit numbers: " << N1.size() << ", Count for 2 digits: " << N2.size() << ", Count for 3 digits: " << N3.size() << ", Count for 4 digits: " << N4.size() << ", Count for 5 digits: " << N5.size() << ", Count for 6 digit numbers: " << N6.size() << ", Count for 7 digit numbers: " << N7.size() << endl;//Ouptuts statements for 1-7 digit counts
    
    cout << "All possible solutions for 8 digit numbers: " << endl;//Output statement for 8 digit numbers
    
    for (int i=0; i < N8.size(); i++){//loop for ouputing 8 digit permutation solutions
        cout << N8.at(i) << endl;
    }
    
    cout << "All possible solutions for 9 digit numbers: " << endl;//Output statement for 9 digit numbers;
    
    for (int i=0; i < N9.size(); i++){//loop for ouptuting 9 digit permutation solutions
        cout << N9.at(i) << endl;
    }
    
    
    cout << "All possible solutions for 10 digit numbers: " << endl;//output for 10 digit numbers
    
    
    cout << N10[0] << endl;//Output for 10 digit permutation solution
    //hexPermutations();
    try{
        hexPermutations();
    }catch(exception e){
        cout << "Error: cannot run hex permutations" << endl;
    }
    
    return 0;
}

void hexPermutations()//void function for calculating the hex permutations
{
    cout << "Hex" << endl;
    
    vector<unsigned long long int> N1;
    vector<string> N2;
    vector<string> N3;
    vector<string> N4;
    vector<string> N5;
    vector<string> N6;
    vector<string> N7;
    vector<string> N8;
    vector<string> N9;
    vector<string> N10;
    
    unsigned long long int t=0;
    
    // Single digit
    for(unsigned int n= 1; n < 10; n++){
        if(n % 1==0){
            N1.push_back(n);
        }
    }
    
    // 2 digit
    for(unsigned int i = 0; i < N1.size(); i++){         // Loop through previous vector
        //cout << N1[i] << endl;
        
        int num = 1;
        string str = to_string(N1[i]);                  // Converting int vector elements to int
        string snum;
        
        for(int n = 1; n < 10; n++){                            // Loop  1-9
            char cn = '0' + n;                                  // Casting int n to char (implicit converstion)
            
            
            for(int j = 0; j < str.length(); j++){          // Loop through the string to Compare
                if(cn != str.at(j)){                        // Compare vector element to char num to avoid repeating numbers in permutation
                    
                    num = N1[i]*10 + n;                 // Generate new num
                    snum = to_string(num);
                    num = stoi(snum, nullptr, 16);
                    
                    if(num % 2 == 0){                       // Check to see if it's divisible by num of digits
                        N2.push_back(snum);                 // Add num to vector
                    }
                }
            }
        }
    }
    
    // 3 digit
    for(unsigned int i=0; i<N2.size(); i++){
        //cout << N2[i] << endl;
        
        string snum;
        string str = N2[i];
        int num1 = stoi(str, nullptr, 10);
        
        for(int n = 1; n<10; n++){
            char cn='0'+n;
            
            if((cn != str.at(0)) && (cn != str.at(1)) ){
                
                int num = num1*10+n;
                snum = to_string(num);
                num = stoi(snum, nullptr, 16);
                if(num%3 == 0){
                    N3.push_back(snum);
                }
            }
        }
    }
    
    // 4 digit
    for(unsigned int i=0; i<N3.size(); i++){
        //cout << N3[i] << endl;
        
        string snum;
        string str = N3[i];
        int num1 = stoi(str, nullptr, 10);
        
        for(int n=1; n<10; n++){
            char cn='0'+n;
            
            if((cn != str.at(0)) && (cn != str.at(1)) && (cn != str.at(2)) ){
                
                int num = num1 *10+n;
                snum = to_string(num);
                num = stoi(snum, nullptr, 16);
                
                if (num % 4 == 0){
                    N4.push_back(snum);
                }
            }
        }
    }
    
    // 5 digit
    for(unsigned int i=0; i<N4.size(); i++){
        //cout << N4[i] << endl;
        
        string str = N4[i];
        string snum;
        int num1 = stoi(str, nullptr, 10);
        for(int n=1; n<10; n++){
            char cn='0'+n;
            
            if((cn != str.at(0)) && (cn != str.at(1)) && (cn != str.at(2)) && (cn != str.at(3))){
                
                int num = num1 * 10 + n;
                string snum = to_string(num);
                num = stoi(snum, nullptr, 16);
                
                if(num %5 == 0){
                    N5.push_back(snum);
                }
            }
        }
    }
    
    // 6 digit
    for(unsigned int i=0; i<N5.size(); i++){
        //cout << N5[i] << endl;
        
        string str = N5[i];
        int num1 = stoi(str, nullptr, 10);
        string snum;
        
        for(int n=1; n<10; n++){
            char cn='0'+n;
            
            if((cn != str.at(0)) && (cn != str.at(1)) && (cn != str.at(2)) && (cn != str.at(3)) && (cn != str.at(4))){
                
                int num = num1 *10+n;
                snum = to_string(num);
                num = stoi(snum, nullptr, 16);
                
                if(num%6 == 0){
                    N6.push_back(snum);
                }
            }
        }
    }
    
    // 7 digit
    for(unsigned int i=0; i<N6.size(); i++){
        //cout << N6[i] << endl;
        
        string str = N6[i];
        int num1 = stoi(str, nullptr, 10);
        string snum;
        
        for(int n=1; n<10; n++){
            char cn='0'+n;
            
            
            
            if((cn != str.at(0)) && (cn != str.at(1)) && (cn != str.at(2)) && (cn != str.at(3)) && (cn != str.at(4)) && (cn != str.at(5))){
                
                int num = num1 *10+n;
                string snum = to_string(num);
                num = stoi(snum, nullptr, 16);
                
                if(num%7 == 0){
                    N7.push_back(snum);
                }
            }
        }
    }
    
    // 8 digit
    for(unsigned int i=0; i<N7.size(); i++){
        //cout << N7[i] << endl;
        
        string str = N7[i];
        long long int num1 = stoll(str, nullptr, 10);
        
        for(int n=1; n<10; n++){
            char cn='0'+n;
            
            if((cn != str.at(0)) && (cn != str.at(1)) && (cn != str.at(2)) && (cn != str.at(3)) && (cn != str.at(4)) && (cn != str.at(5)) && (cn != str.at(6))){
                
                long long int num = num1 *10+n;
                string snum = to_string(num);
                num = stoll(snum, nullptr, 16);
                if(num%8 == 0){
                    N8.push_back(snum);
                }
            }
        }
    }
    
    // 9 digit
    for(unsigned int i=0; i<N8.size(); i++){
        //cout << N8[i] << endl;
        
        string str = N8[i];
        long long int num1 = stoll(str, nullptr, 10);
        
        for(int n=1; n<10; n++){
            char cn='0'+n;
            
            if((cn != str.at(0)) && (cn != str.at(1)) && (cn != str.at(2)) && (cn != str.at(3)) && (cn != str.at(4)) && (cn != str.at(5)) && (cn != str.at(6)) && (cn != str.at(7))){
                
                long long int num = num1 *10+n;
                string snum = to_string(num);
                num = stoll(snum, nullptr, 16);
                
                if(num%9 == 0){
                    N9.push_back(snum);
                }
            }
        }
    }
    
    for(unsigned int i=0; i<N9.size(); i++){
        //cout << N9[i] << endl;
        
        string str = N9[i];
        long long int num1 = stoll(str, nullptr, 10);
        
        for(int n=0; n<10; n++){
            char cn='0'+n;
            
            if((cn != str.at(0)) && (cn != str.at(1)) && (cn != str.at(2)) && (cn != str.at(3)) && (cn != str.at(4)) && (cn != str.at(5)) && (cn != str.at(6)) && (cn != str.at(7)) && (cn != str.at(8))){
                
                long long int num = num1 *10+n;
                string snum = to_string(num);
                stoll(snum, nullptr, 16);
                
                if(num%10 == 0){
                    N10.push_back(snum);
                }
            }
        }
    }
    
    cout << "Count for 1 digit numbers: " << N1.size() << ", Count for 2 digits: " << N2.size() << ", Count for 3 digits: " << N3.size() << ", Count for 4 digits: " << N4.size() << ", Count for 5 digits: " << N5.size() << ", Count for 6 digit numbers: " << N6.size() << ", Count for 7 digit numbers: " << N7.size() <<  ", Count for 8 digit numbers: " << N8.size() << ", Count for 9 digit numbers: " << N9.size() << endl;
    
    cout << "All possible solutions for 8 digit numbers: " << endl;
    
    for (int i=0; i < N8.size(); i++){
        cout << N8.at(i) << endl;
    }
    
    cout << "All possible solutions for 9 digit numbers: " << endl;
    
    for (int i=0; i < N9.size(); i++){
        cout << N9.at(i) << endl;
    }
    
    
    cout << "All possible solutions for 10 digit numbers: " << endl;
    
    
    // letter hex
    vector<string> NA;
    vector<string> NB;
    vector<string> NC;
    vector<string> ND;
    vector<string> NE;
    vector<string> NF;
    
    
    // A Digit
    for(unsigned int i=0; i < N10.size(); i++)
    {
        cout << N10[i] << endl;
        
        const int l = N10[i].length();
        
        for(int j = 0; j <= l; j++){
            
            string s = N10[i];
            s.insert(j, "a");
            //cout << s << endl;
            long long int num = stoll(N10[i], nullptr, 16);               // converts the number to decimal equivalent of its hex
            //cout << num << endl;
            if ((num % 11) == 0){                                   // checks for even divisibility
                
                string str = to_string(num);
                NA.push_back(str);
            }
        }
    }
    
    // B digit
    for(unsigned int i=0; i < NA.size(); i++)
    {
        
        const int l = NA[i].length();
        for(int j = 0; j <= l; j++){
            
            string s = NA[i];
            s.insert(j, "b");
            long long int num = stoi(s, nullptr, 16);
            
            if ((num % 12) == 0){
                
                string str = to_string(num);
                NB.push_back(str);
            }
        }
    }
    // C digit
    for(unsigned int i=0; i < NB.size(); i++)
    {
        
        const int l = NB[i].length();
        for(int j = 0; j <= l; j++){
            
            string s = NB[i];
            s.insert(j, "c");
            long long int num = stoi(s, nullptr, 16);
            
            if ((num % 13) == 0){
                
                string str = to_string(num);
                NC.push_back(str);
            }
        }
    }
    // D digit
    for(unsigned int i=0; i < NC.size(); i++)
    {
        
        const int l = NC[i].length();
        
        for(int j = 0; j <= l; j++){
            
            string s = NC[i];
            s.insert(j, "d");
            long long int num = stoi(s, nullptr, 16);
            
            if ((num % 14) == 0){
                
                string str = to_string(num);
                ND.push_back(str);
            }
        }
    }
    // E digit
    for(unsigned int i=0; i < ND.size(); i++)
    {
        
        const int l = ND[i].length();
        
        for(int j = 0; j <= l; j++){
            
            string s = ND[i];
            s.insert(j, "e");
            long long int num = stoi(s, nullptr, 16);
            
            if ((num % 15) == 0){
                
                string str = to_string(num);
                NE.push_back(str);
            }
        }
    }
    // F digit
    for(unsigned int i=0; i < NE.size(); i++)
    {
        
        const int l = NE[i].length();
        for(int j = 0; j <= l; j++){
            
            string s = NE[i];
            s.insert(j, "f");
            
            long long int num = stoi(s, nullptr, 16);
            
            if ((num % 16) == 0){
                
                string str = to_string(num);
                NF.push_back(str);
            }
        }
    }
    
    for(unsigned int i=0; i < NF.size(); i++)
        cout << ", 15 digit numbers: " << NF[i] << endl;
    
    if(NA.size() == 0){
        cout << "There are no solutions for 11 digit numbers" << endl;
    }
    else{
        cout<< "All possible solutions for 11 digit numbers" << endl;
        for(unsigned int i = 0; i < NA.size(); i++){
            cout << NA.at(i) << endl;
        }
    }
    
    if(NB.size() == 0){
        cout << "There are no solutions for 12 digit numbers" << endl;
    }
    else{
        cout<< "All possible solutions for 12 digit solutions" << endl;
        for(unsigned int i = 0; i < NB.size(); i++){
            cout << NB.at(i) << endl;
        }
    }
    
    if(NC.size() == 0){
        cout << "There are no solutions for 13 digit numbers" << endl;
    }
    else{
        for(unsigned int i = 0; i < NC.size(); i++){
            cout << NC.at(i) << endl;
        }
    }
    
    if(ND.size() == 0){
        cout << "There are no solutions for 14 digit numbers" << endl;
    }
    else{
        cout<< "All possible solutions for 11 digit numbers" << endl;
        for(unsigned int i = 0; i < ND.size(); i++){
            cout << ND.at(i) << endl;
        }
    }
    
    if(NE.size() == 0){
        cout << "There are no solutions for 15 digit numbers" << endl;
    }
    else{
        cout<< "All possible solutions for 11 digit numbers" << endl;
        for(unsigned int i = 0; i < NE.size(); i++){
            cout << NE.at(i) << endl;
        }
    }
    
    if(NF.size() == 0){
        cout << "There are no solutions for 16 digit numbers" << endl;
    }
    else{
        cout<< "All possible solutions for 11 digit numbers" << endl;
        for(unsigned int i = 0; i < NF.size(); i++){
            cout << NF.at(i) << endl;
        }
    }
    
    /*cout << "Count for 11 digits: " << NA.size() << ", Count for 12 digits: " << NB.size() << ", Count for 13 digits: " << NC.size() << ", Count for 14 digits: " << ND.size() <<  ", Count for 14 digits: " << NE.size() << ", Count for 15 digits: " << NF.size() << endl;*/
    
    /*cout << "11 digit numbers: " << NA[0] << ", 12 digits: " << NB[0] << ", 13 digits: " << NC[0] << ", 14 digits: " << ND[0] << ", for 15 digits: " << NE[0] << ", 16 digit numbers: " << NF[0];*/
}
