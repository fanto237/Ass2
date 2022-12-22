#include <iostream>
//#include "map_rb.h"
#include "map_pt.h"

using namespace std;


int main() {

    map_pt<char> mymap;
//    map_rb<unsigned ,char> mymap;
    auto var1 = std::pair<unsigned , char>(0, 'a');
    auto var2 = std::pair<unsigned, char>(1, 'b');
    auto var3 = std::pair<unsigned, char>(2, 'c');
    auto var4 = std::pair<unsigned, char>(3, 'd');
    auto var7 = std::pair<unsigned, char>(34, 'd');
    auto var5 = std::pair<unsigned, char>(17, 'd');
    auto var6 = std::pair<unsigned, char>(24, 'd');

    auto res = mymap.insert(var1);
    auto res2 = mymap.insert(var2);
    auto res3 = mymap.insert(var3);
    auto res4 = mymap.insert(var4);
    auto res5 = mymap.insert(var5);
    auto res6 = mymap.insert(var6);
    auto res7 = mymap.insert(var7);


    cout << "-----------------" << endl;

    cout << "key 0: " << res.first->first << "\nchar 0: " << res.first->second << "\nresult insert 0 : " << res.second << std::endl;
    cout << "key 1: " << res2.first->first << "\nchar 1: " << res2.first->second << "\nresult insert 1 : " << res2.second << std::endl;
    cout << "key 2: " << res3.first->first << "\nchar 2: " << res3.first->second << "\nresult insert 2 : " << res3.second << std::endl;
    cout << "key 3: " << res3.first->first << "\nchar 2: " << res4.first->second << "\nresult insert 2 : " << res3.second << std::endl;
    cout << "key 4: " << res3.first->first << "\nchar 2: " << res5.first->second << "\nresult insert 2 : " << res3.second << std::endl;
    cout << "key 5: " << res3.first->first << "\nchar 2: " << res6.first->second << "\nresult insert 2 : " << res3.second << std::endl;
    cout << "key 6: " << res3.first->first << "\nchar 2: " << res7.first->second << "\nresult insert 2 : " << res3.second << std::endl;

    cout << "-----------------" << endl;

//    auto result = mymap.find(24);
//    if (result == mymap.end())
//        cout << "find not work" << endl;
//    else
//        cout << result->first << " : " << result->second << endl;

//    cout << mymap << endl;


    //    for(auto i = mymap.begin(); i != mymap.end(); i++){
//        cout << "key : " <<  i->first << "\nchar : " << i->second << endl;
//        cout << "+++++++++" << endl;
//    }

//    int a = 3;
//    for (int i = 0; i < 4; ++i){
//        bool f = ( a & ( 1 << i) ) != 0;
//        cout << f << endl;
//    }

//char c = '\t';
//int count = 2;
//for(int i = 0; i < count; ++i)
//    cout << c;
//cout << "teste tab" << endl;
}
