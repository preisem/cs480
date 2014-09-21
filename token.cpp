/* Matthew P
 * Last Revision 8/24/14
 * version 2.1
 */


#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

int main(){
string s, file, compares; //S = file string, file = file name, compares = substr for reserves
string reserves[5] ={"int", "real", "round", "roundup", "rounddown"}; //array of reserves
char a;
int i =0, n=0, token_count = 0;
ifstream fin;

/**PUTTING INPUT FILE INTO A STRING*/

cout<<"Enter the name of the file to be lexi-smexied (including the extension)"<<endl;
cin>>file;
fin.open(file.data());

while(!fin.eof()){
    fin.get(a);
    s.insert(i,1,a);
    i++;
}
s.insert(i,1,'\n');
/****************************************************/


i = 0;
/**START OF LEXI**/

begining:   //start of command
if(i>=s.length()){
    goto bottom;
}
a = s.at(i);


/**
 *IF STARTS WITH OPERATORS, EXPRESIONS, EOCs OR WHITESPACES
**/
switch (a){
            case '+': cout<<"OPER          +"<<endl;
                i++, token_count++;
                goto begining;
            case '-': cout<<"OPER          -"<<endl;
                i++, token_count++;
                 goto begining;
            case '/':
                if(s.at(i+1) == '/'){
                    while (s.at(i) != '\n'){
                        i++;
                    }
                   goto begining;
                }
                else{
                   cout<<"OPER          /"<<endl; //NEEDS TO BE UPDATED WITH COMMENT
                i++, token_count++;
                 goto begining;
                }

            case '*': cout<<"OPER          *"<<endl;
                i++, token_count++;
                goto begining;
            case '=': cout<<"OPER          ="<<endl;
                i++, token_count++;
                 goto begining;
            case '(': cout<<"OPEN_EXP      ("<<endl;
                i++, token_count++;
                 goto begining;
            case ')': cout<<"CLOSE_EXP     )"<<endl;
                i++, token_count++;
                 goto begining;
            case ' ':
                i++;
                goto begining;
            case '\n':
                i++;
                goto begining;
            case '.':
                cout<<"EOC           ."<<endl;
                i++, token_count++;
                goto begining;
            default:
                break;
        }

/**
 *IF IT STARTS WITH A DIGIT
 **/
if(isdigit(a)){
   n = i, i++;
    a = s.at(i);

    while(isdigit(a) || a == ' ' || a == '\n'){    //KEEPS LOOPING UNTIL IT FINDS SOMETHING NOT A DIGIT
        i++;
        a= s.at(i);
    }

 if(a=='.'){
    i++;
    a = s.at(i);
    if(isdigit(a) == false){
        i = i-2; //goes back to last digit in number
        cout<<"INTEGER       ";
        token_count++;
        /****************Printing out number******/
        while(n <= i){
            if(s.at(n)== ' ' || s.at(n) == '\n') n++;
            else cout<<s.at(n), n++;
        }
        cout<<endl;
        /****************Printing out number******/
        i++;
        goto begining;
    }//END OF IF THERE ISNT A DIGIT AFTER '.'

    else{ //IF THERE IS A DIGIT AFTER A '.'
        while(isdigit(a) || a == ' ' || a == '\n'){    //KEEPS LOOPING UNTIL IT FINDS SOMETHING NOT A DIGIT
            i++;
            a= s.at(i);
        }
        i--;
        cout<<"REAL          ";
        token_count++;
        /****************Printing out number******/
        while(n <= i){
            if(s.at(n)== ' ' || s.at(n) == '\n') n++;
            else cout<<s.at(n), n++;
        }
        cout<<endl;
        /****************Printing out number******/
        i++;
        goto begining;


    }//END OF IF THERE IS A DIGIT AFTER '.'

 }//END OF IF THERE IS A '.'

else{ //IF THERE IS NOT A '.'
        i--;
     cout<<"INTEGER       ";
     token_count++;
        /****************Printing out number******/
        while(n <= i){
            if(s.at(n)== ' ' || s.at(n) == '\n') n++;
            else cout<<s.at(n), n++;
        }
        cout<<endl;
        /****************Printing out number******/
        i++;
        goto begining;
    }


}//END OF IS DIGIT IF STATEMENT

/**
 *IF IT STARTS WITH AN APLHA
**/
if(isalpha(a)){
   n = i, i++;
   a = s.at(i);
   while(isdigit(a) || isalpha(a)){ //LOOPS UNTIL NOT A DIGIT OR ALPHA
        i++;
        a= s.at(i);
   }

   /** COMPARING TO RESERVE WORDS**/
   compares = s.substr(n,i-n); //puts the possible identifier into a new string

    if(reserves[0].compare(compares) == 0){ //IF MATCHES RESERVE WORD 'int'
            cout<<"RESERVED      int"<<endl;
            token_count++;
    goto begining;
    }

    else if(reserves[1].compare(compares) == 0){ //IF MATCHES RESERVE WORD 'real'
            cout<<"RESERVED      real"<<endl;
            token_count++;
    goto begining;
    }

    else if(reserves[2].compare(compares) == 0){ //IF MATCHES RESERVE WORD 'round'
            cout<<"RESERVED      round"<<endl;
            token_count++;
    goto begining;
    }

    else if(reserves[3].compare(compares) == 0){ //IF MATCHES RESERVE WORD 'roundup'
            cout<<"RESERVED      roundup"<<endl;
            token_count++;
    goto begining;
    }

    else if(reserves[4].compare(compares) == 0){ //IF MATCHES RESERVE WORD 'rounddown'
            cout<<"RESERVED      rounddown"<<endl;
            token_count++;
    goto begining;
    }
    else{ //MATCHES NO RESERVES
            i--;
        cout<<"IDENT         ";
        token_count++;
        /****************Printing out number******/
        while(n <= i){
            if(s.at(n)== ' ' || s.at(n) == '\n') n++;
            else cout<<s.at(n), n++;
        }
        cout<<endl;
        /****************Printing out number******/
        i++;
        goto begining;
    }
}//END OF IF IT STARTS WITH ALPHA

else{
    cout<<"BAD_CHAR      "<<s.at(i)<<endl;
    i++;
    goto begining;
}

bottom:
    cout<<token_count;
    return 0;
}

