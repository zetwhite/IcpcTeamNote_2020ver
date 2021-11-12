#include<iostream>
#include<set>
using namespace std;
 
int main(void){
    set<int> s;
 
    s.insert(40);    
    s.insert(10);
    s.insert(80);
    s.insert(30);
    s.insert(70);
    s.insert(60);
    s.insert(20);
    s.insert(50);
 
    set<int>::iterator iter;
    for(iter = s.begin(); iter != s.end(); iter++){
        cout << *iter << " " ;
    }
    cout << endl;
    
     
    //중복 값 넣어보기. 
    s.insert(20); 
    for(iter = s.begin(); iter != s.end(); iter++){
        cout << *iter << " " ;
    }    
    cout << endl;    
    
    //존재 하는 원소 찾기
    iter = s.find(30);
    if(iter != s.end()){
        cout << *iter << " : 존재 " << endl; 
    }else{
        cout << "존재하지 않음 " << endl; 
    }
 
    //존재 하지 않는 원소 찾기    
    iter = s.find(333);
    if(iter != s.end()){
        cout << *iter << " : 존재 " << endl; 
    }else{
        cout << "존재하지 않음 " << endl; 
    }
    
    
    return 0;    
}