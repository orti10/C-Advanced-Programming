#include "Editor.h"

using namespace std;

Editor::Editor(){
    Document();
}

 void Editor::loop(){
    
    string command;
    getline(cin,command);
    cout<<command<<endl;
    while(command!="Q"){
        switch(command[0]){
            case 'p':
            d.p();
            break;
            
            case 'n':
            d.n();
            break;

            case '%':
            d.percentP();
            break;

            case 'a':
            d.a();
            break;

            case 'i':
            d.i();
            break;

            case 'c':
            d.c();
            break;

            case 'd':
            d.d();
            break;

            case '/':
            if(command.size()>1){
                d.t_search(command.substr(1));
            }
            else{
                d.r_search();
            }
            break;

            case '?':
            d.b_search(command.substr(1));
            break;

            case 's':
            d.s_old_new(command.substr(2));
            break;
            
        }
        if(command[0]>'0' && command[0]<='9'){
            d.num(stoi(command));
        }
        getline(cin,command);
        cout<<command<<endl;
    }
}