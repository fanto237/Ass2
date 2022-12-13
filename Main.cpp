#include <iostream>
//#include "ISCAS.h"
//#include "ROBDD.h"
#include "map_rb.h"

using namespace std;


int main() {

    map_rb<int, char> mymap;
    auto var1 = std::pair<int, char>(11, 'a');
    auto var2 = std::pair<int, char>(1, 'b');
    auto var3 = std::pair<int, char>(3, 'c');
    auto var4 = std::pair<int, char>(25, 'd');
    auto res = mymap.insert(var1);
    auto res2 = mymap.insert(var2);
    auto res3 = mymap.insert(var3);
    auto res4 = mymap.insert(var4);

//     cout << "the result is : " << res.second << endl;


//    cout << "key 0: " <<  res.first->first << "\nchar 0: " << res.first->second << "\nresult insert 0 : " << res.second << std::endl;
//    cout << "key 1: " <<  res2.first->first << "\nchar 1: " << res2.first->second << "\nresult insert 1 : " << res2.second << std::endl;
//    cout << "key 2: " <<  res3.first->first << "\nchar 2: " << res3.first->second << "\nresult insert 2 : " << res3.second << std::endl;

//    auto result = mymap.find(1);
//    if(result == mymap.end())
//        cout << "find not work" << endl;
//    else
//        cout << result->first << " : " << result->second << endl;

    cout << mymap << endl;


    //    for(auto i = mymap.begin(); i != mymap.end(); i++){
//        cout << "key : " <<  i->first << "\nchar : " << i->second << endl;
//        cout << "+++++++++" << endl;
//    }

//int *list = new int[4];
//int a = 123;
//    list[0] = 1;
//    list[1] = 14;
//    list[2] = a;
//    list[3] = 13;
//
//    cout << &list[2] << " | "<< (list+2) << " | " << &a << endl;
}
