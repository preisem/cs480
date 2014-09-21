#include <iostream>
#include <regex>
#include <string>
#include <fstream>

using namespace std;

int main(){
string
s, //config input file string
file, //name of input file
test_strings, //test file string
stringint, //string of ints used by the stringstream function
rest_of_string;

stringstream nums;

char a;

int
i =0, //multipurpose pointer
x=0, //pointer for end of strings with streamstream
loop = 0, //multipurpose loop counter
states = 0, //TOTAL NUMBER OF STATES NOT INCLUDING STATE 0 / FAIL STATE
final_states = 0, //NUMBER OF FINAL STATES
finals = 0, //output int of stringstream, used to put values of final states into an array
num_alpha = 0, //number of letters in the alphabet NOT INCLUDING EPSILON
start_state = 0, //the start state
s_transition = 0, f_transition = 0, a_transition = 0,
//the three above are used when putting information into the 3D array of transitions
//they hold the start state, final state, and alphabet number of a said state
current_state = 0, y_state = 0,
//above two used in testing inputs
//current state is the current state the machine is on, y state is the most recent split state
duplicate_trans = 0; //counter for the number of same transition from the current state to another state

ifstream fin, test_strings_file; //streams used to get data from input files
string next_number(char a, int i, int x, string s); //see declaration



/**PUTTING INPUT FILE INTO A STRING*/

cout<<"Enter the name of the file (including the extension)"<<endl;
cin>>file;
fin.open(file.data());

while(!fin.eof()){
    fin.get(a);
    s.insert(i,1,a);
    i++;
}
s.insert(i,1,'\n');
/**##################################**/
 i = 0;
 cout<<s;

/**
*GETTING DATA FROM INPUT FILE
**/


/** GETTING ALL STATES **/

stringint= next_number(a,i,x,s);
nums<<stringint;
nums>>states;
nums.str("");
nums.clear();
cout<<"States*"<<states<<"* "<<endl;

/**#######################**/

/** GETTING ALL FINAL STATES AND STORING THEM **/

i = x+2; //reseting pointers
//cout<<"i is at*"<<s.at(i)<<"* ";
stringint = next_number(a,i,x,s);
nums<<stringint;
nums>>final_states;
nums.str("");
nums.clear();
cout<<"Final States*"<<final_states<<"* "<<endl;
/****************/
int list_final_states[final_states]; //Makes an array of all final states
/***************/
x += 2;

while(loop < final_states){ //loops the number of times as there are final states
    i = x+2;
    //cout<<"i is at*"<<s.at(i)<<"* ";
    stringint = next_number(a,i,x,s);
    nums<<stringint;
    nums>>finals;
    nums.str("");
    nums.clear();
    list_final_states[loop] = finals;
    loop++;
    x += 2;
}//END OF FINAL STATES LOOP

//cout<<"x is at*"<<s.at(x)<<"* ";
i = x+2;
/********************************************/
//cout<<"i is at*"<<s.at(i)<<"* ";

/** GETTING THE START STATE **/
stringint = next_number(a,i,x,s);
    nums<<stringint;
    nums>>start_state;
    nums.str("");
    nums.clear();
    cout<<"Start_state is *"<<start_state<<"* "<<endl;
/****************************/

i += 2;
/** GETTING THE ALPHABET AND STORING IT **/
stringint = next_number(a,i,x,s);
nums<<stringint;
nums>>num_alpha;
nums.str("");
nums.clear();
/*******************************/
char alphabet[num_alpha+1]; //creates array for the alphabet with one extra for E transitions
/*******************************/
cout<<"Length of alphabet is *"<<num_alpha<<"* "<<endl;
alphabet[0]= 'E'; //first alphabet is Epsilon

i+=2;
loop = 0;

while(loop< num_alpha){
    alphabet[loop+1]= s.at(i);
    i++;
    loop++;
}//END OF NUM_ALPHA LOOP
/************************************/

/** CREATING THE 3D ARRAY TO HOLD ALL STATES AND TRANSITIONS **/
int transitions[states+1][num_alpha+1][states+1];
/**NOTE ALPHABET WILL BE STORED AS INT VALUE, EG 'E' = 0, a = '1', etc. **/


i++;
/** GETTING ALL TRANSITIONS **/
begining:
if(i + 2>= s.length()){  //KEEP AT TWO, NOT SURE WHY BUT KEEP IT
    goto bottom_of_data_input;
}

/** Getting the first state **/
stringint = next_number(a,i,x,s);
nums<<stringint;
nums>>s_transition;
nums.str("");
nums.clear();
/*****************************/

/** Getting the letter of the transition **/
i += 2;
loop = 0;
while(loop < num_alpha+1){
    if(s.at(i) == alphabet[loop]){
        a_transition = loop;
    }
   loop++;
}

i += 2;
/*********************************/

/** Getting the final state of the transition **/
stringint = next_number(a,i,x,s);
nums<<stringint;
nums>>f_transition;
nums.str("");
nums.clear();
/************************************/

/** Setting that that transition exists **/
transitions[s_transition][a_transition][f_transition] = true;
cout<<s_transition<<" "<<a_transition<<" "<<f_transition<<endl;
/*****************************************/


i += 2;
cout<<endl<<"i is at *"<<s.at(i)<<"*";
goto begining;
/** END OF GETTING DATA FROM INPUT FILE **/
bottom_of_data_input:


/**
 *GETTING STRINGS TO TEST FROM INPUT FILE
**/
i=0;
x=0;
a=' ';

/**PUTTING INPUT FILE INTO A STRING*/

cout<<endl<<"Enter the name of the file with test strings (including the extension)"<<endl;
cin>>file;
test_strings_file.open(file.data());

while(!test_strings_file.eof()){
    test_strings_file.get(a);
    test_strings.insert(i,1,a);
    i++;
}
test_strings.insert(i,1,'\n');
/**##################################**/

i=0,x=0;



/**
 *TESTING STRINGS
**/
bool machine(int current_state, string rest_of_string, string test_strings, int num_alpha, char alphabet[], int i, transitions[][num_alpha+1][states+1]);


current_state = start_state;

i = 0;

/**GOTO RECURSIVE FUNCTION**/

//cout<<machine(current_state, rest_of_string, test_strings, num_alpha, alphabet, i, transitions)<<endl;


/** THE REST OF MAIN IS COMMENTED OUT, THIS IS WHERE IM HAVING TROUBLE

/**SETTING THE CHARACTER TO THE CORRESPONDING ALPHABET NUMBER
loop = 0;
while(loop < num_alpha+1){
    if(s.at(i) == alphabet[loop]){
        x = loop;
    }

   loop++;
}
/**##########################################################

loop = 1; //skips 0 because pos0 = state 0 = fail state

/**SEE HOW MANY TRANSITIONS OF A CERTAIN ALPHA FROM THE CURRENT STATE THERE ARE
while( loop < states+1){
    if(transitions[current_state][x][loop] == true){
        duplicate_trans ++;
    }
loop++;
}
cout<<endl<<"NUMBER OF TRANSITIONS OF THE CURRENT CHAR FROM CURRENT STATE = "<<duplicate_trans<<endl;



if(duplicate_trans = 0){
    cout<<"NO CONSUMABLE TRANSITIONS FROM THIS STATE"<<endl;

}




else if(duplicate_trans = 1){
/**FIND THE STATE THE TRANSITION GOES TO AND MAKE IT CURRENT STATE
loop = 1;
    while( loop < states+1){
        if(transitions[current_state][x][loop] == true){
        current_state = loop;
        }
    loop++;
    }
    i++; //pointer is at next character
    goto top_of_tester;
}//END OF DUP TRAN = 1





**/
return 0;
}//END OF MAIN



string next_number(char a, int i, int x, string s){

a = s.at(i);
x = i+1;
while((s.at(x) =! ' ' )|| (s.at(x) =! '\n')){
    x++;
}
return s.substr(i,x-i);
}




bool machine(int current_state, string rest_of_string, string test_strings, int num_alpha, char alphabet[], int i , transitions[][][]){
int a = 0, b = 0, looper = 0;
char x;


x = test_strings.at(i);

/**SETTING THE CHARACTER TO THE CORRESPONDING ALPHABET NUMBER **/
while(looper < num_alpha+1){
    if(test_strings.at(i) == alphabet[looper]){
        a = looper;
    }

   looper++;
}
/**###########################################################**/

looper = 1;
/**SEE HOW MANY TRANSITIONS OF A CERTAIN ALPHA FROM THE CURRENT STATE THERE ARE**/
while( looper < states+1){
    if(transitions[current_state][a][looper] == true){
        b ++;
    }
looper++;
}
cout<<endl<<"NUMBER OF TRANSITIONS OF THE CURRENT CHAR FROM CURRENT STATE = "<<b<<endl;




}
