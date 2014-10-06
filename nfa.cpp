/*
 *@author = Matt Preisendorfer
 * State Machine Creator and Tester
 * Compiler: MinGW(g++)
 * Version 0.8, revision #70-bagillion-zillion
 * Last Revision 10/5/14 
 * NOTE: sstream is unstable and only works with C++11 only
 * refer to your complier for enabling sstream
 */


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>



using namespace std;

int main(){
string
s, //config input file string
file, //name of input file
test_strings, //test file string
stringint, //string of ints used by the stringstream function
rest_of_string,
test_string;        


stringstream nums;

char a;

int
d = 0,b = 0, c = 0, //used for clearing the transitions array
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
bool transitions[states+1][num_alpha+1][states+1];

/**CLEARING THE ARRAY**/
while(b <= states){
    c = 0;
    while(c <= num_alpha){
        d = 0;
        while(d <= states){
            transitions[b][c][d] = 0;
            d++;
        }
    c++;
    }
b++;
}


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
/*****************************************/


i += 2;

goto begining;
/** END OF GETTING DATA FROM INPUT FILE **/
bottom_of_data_input:

/**LISTING ALL TRANSITIONS**/
cout<<"LIST OF ALL TRANSITIONS: "<<endl;
i=1,x=0, loop = 1;

while(i <= states){ //i starts at 1 == state 1, states = all states not including 0

    x = 0;
    while(x <= num_alpha){//x starts at 0, 0 == E transition, num_alpha has all alphabet except E transition

        loop = 1;
        while(loop <= states){ //same as first while loop
            if(transitions[i][x][loop] == true) cout<<i<<" "<<x<<" "<<loop<<endl;
            loop++;

        }
    x++;
    }
i++;
}
/**############################################################**/


/*******************************************************************************************************
********************************************************************************************************
********************************************************************************************************
*******************************************************************************************************/


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


i = 0;
x = 0;


while(test_strings.at(x) != '\n'){
    x++;
}
test_string = test_strings.substr(i,x-i);
cout<<"*"<<test_string<<"*"<<endl;







/**
 *TESTING STRINGS
**/
bool machine(int final_states, int list_final_states[], string test_string,int states, int current_state, string rest_of_string, int num_alpha, char alphabet[], int i, char a /** , transitions[][][] **/);







current_state = start_state;

i = 0;


cout<<machine( final_states, list_final_states, test_string, states, current_state, rest_of_string, num_alpha, alphabet, i, a);




cin>>a;



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




bool machine(int final_states, int list_final_states[], string test_string, int states, int current_state, string rest_of_string, int num_alpha, char alphabet[], int i, char a /** , transitions[][][] **/){

int b = 0, looper = 0, num_of_trans = 0;
bool found_trans = false, e_found_trans = false;



//STEP 0.5: if a == \n then check to see if on an final state or not
if(rest_of_string == "\n" || rest_of_string == ""){
    while(looper < final_states ){
        if(current_state == list_final_states[looper]){
            return true; //if the current state is on one of the final states, return true
        }
    looper++;    
    }
return false;  //if it is not one of the final states then it must return false   
}

//####################################################################
//STEP 1: get current state, get current position on the string to be tested, get the character to be tested 
a = rest_of_string.at(i);
//#########################################################################################################




//STEP 2: convert the char to the corresponding alphabet integer EG a=1, E=0, etc. 

looper = 0;
while(looper < num_alpha+1){
    if(rest_of_string.at(i) == alphabet[looper]){
        b = looper;
    }

   looper++;
}

// b = the number of the character
//################################################################################

//STEP 3: see how many transitions there are from current state
looper = 1;

while(looper < states+1){
    if(/** transitions[current_state][b][looper] **/ == true){
        num_of_trans++;
    }
    if(/** transitions[current_state][0][looper] **/ == true){
        num_of_trans++;
    }
looper++;    
}
//##############################################################

//STEP 4: if there are no transitions, return false, otherwise continue
if(num_of_trans == 0){
    return false;
}
//##############################################################

//STEP 5: pick a non E transition to take
looper = 1;

while(looper < states+1  || found_trans == false){
    if(/** transitions[current_state][b][looper] **/ == true){
        found_trans = true;
    }
looper++;    
}
//############################################

//STEP 6: if no non E transition are found, find the next E transition to take
if(found_trans == false){
    looper = 1;
    while(looper < states+1 || e_found_trans == false){
        if(true/** transitions[current_state][0][looper] **/ == true){
        e_found_trans = true;
        }
    looper++;    
    }       
}
//looper = some transition that we can take
//found_trans = if false, e_found_trans must be true
//e_found_trans = if false, found_trans must be true
//############################################################################


//STEP 7: Take the transition
if(found_trans == true){
    i++; //consumes a char
     //shortens the rest_of_string
    rest_of_string = test_string.substr(i,test_string.length() - i+1); //if i = 3,     test_string = abbabaabab        rest_of_string = baabab    
                                                                     // length = 10-4                xxxx^^^^^^          
}
//otherwise it is an e transition so dont consume a char
current_state = looper; //take the transition
//#########################

//STEP 8: run the function at the new state
if(machine(final_states, list_final_states, test_string, states, current_state, rest_of_string, num_alpha, alphabet, i, a /** , transitions[][][] **/) == true){
    return true; //if the function returns true, the rest of the string is accepted so end the function
}
//#########################################

//STEP 9: if the function returns false, find another state to go to
if(found_trans == true){ //if a non e transition was found before, continue looking for one
    found_trans = false;
    
    while(looper < states+1  || found_trans == false){
        if(/** transitions[current_state][b][looper] **/ == true){
            found_trans = true;
        }
        looper++;
    }
    
    
}
//STEP 9.5: if there is no new transition found look for an E transition

if(found_trans == false && e_found_trans == false){ //no more trans were found and e trans were not searched before
    looper = 1; //resets looper for counting if it didnt find or didnt search for an e transition previously
}

if(e_found_trans == true){ //if a e transition was found previously 
    e_found_trans == false; //if it was previously found then reset to not found
}

while(looper < states+1 || e_found_trans == false){ //loops to find an E transition
        if(/** transitions[current_state][0][looper] **/ == true){
        e_found_trans = true;
        }
    looper++;    
    }       
//########################################################################

//STEP 10: if no new transitions of any kind are found
if(e_found_trans == false && found_trans == false){
    return false;
}



}
