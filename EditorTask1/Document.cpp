#include "Document.h"

using namespace std;  


Document::Document(){
        vec.push_back("");
}

void Document::a(){
        string txt;
        vector<string>::iterator it;
        
        getline(cin,txt);
        cout<<txt<<endl;
        while(txt[0] != '.'){
                it=vec.begin();
                index++;    
                vec.insert(it+index,txt); 
                getline(cin,txt);
                cout<<txt<<endl;
        }
}
void Document::i(){
        index--;
        a();
        index++;
}

void Document::p(){    
        cout<<vec[index]<<endl;
}

void Document::n(){
        cout<<index<<"\t"<<vec[index]<<endl;
}

void Document::percentP(){
        for(int i=1;i<vec.size();i++){
             cout<<vec[i]<<endl;
        }
}
void Document::num(int num){
        index=num;
        p();
}
void Document::c(){ 
       d();
       a();
}
void Document::d(){
        vec.erase (vec.begin()+index);
        if(index!=1) index--;

}
void Document::t_search (string s){
       old_search=s;
       for(int i=index;i<vec.size();i++){
               size_t found= vec[i].find(s);
               if(found!=string::npos){
                       index=i;
                       p();
                       return;
               }
       }
       for (int i = 1; i <index; i++){
               size_t found= vec[i].find(s);
               if(found!=string::npos){
                       index=i;
                       p();
                       return;
               }
       }
       cout<<"?"<<endl;
}
void Document::r_search (){
      index++;
      t_search(old_search);
}

void Document::b_search (string s){
        for(int i=index-1;i>0;i--){
               size_t found= vec[i].find(s);
               if(found!=string::npos){
                       index=i;
                       p();
                       return;
               }
       }
       for (int i = vec.size()-1; i >index; i--){
               size_t found= vec[i].find(s);
               if(found!=string::npos){
                       index=i;
                       p();
                       return;
               }
       }
       cout<<"?"<<endl;
}
void Document::s_old_new(string s){
        stringstream check1(s); 
        string old; 
        string news;
        getline(check1, old, '/');
        getline(check1, news, '/');
        vec[index].replace(vec[index].find(old),old.size(),news);
}