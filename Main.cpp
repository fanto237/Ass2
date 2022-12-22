#include <iostream>
#include <map>
#include "map_rb.h"
//#include "map_pt.h"

using namespace std;


int main() {

//    map_pt<char> mymap;
    map_rb<unsigned, char> mymap;
//    map<unsigned ,char> mymap;
    auto var1 = std::pair<unsigned, char>(12, 'a');
    auto var2 = std::pair<unsigned, char>(9, 'b');
    auto var3 = std::pair<unsigned, char>(6, 'c');
    auto var4 = std::pair<unsigned, char>(4, 'd');
    auto var7 = std::pair<unsigned, char>(34, 'e');
    auto var5 = std::pair<unsigned, char>(58, 'f');
    auto var6 = std::pair<unsigned, char>(22, 'g');

    auto res = mymap.insert(var1);
    auto res2 = mymap.insert(var2);
    auto res3 = mymap.insert(var3);
    auto res4 = mymap.insert(var4);
    auto res5 = mymap.insert(var5);
    auto res6 = mymap.insert(var6);
    auto res7 = mymap.insert(var7);


    auto result = mymap.find(4);
    if (result == mymap.end())
        cout << "find not work" << endl;
    else
        cout << result->first << " : " << result->second << endl;
    ++result;
    cout << result->first << " : " << result->second << endl;
    ++result;
    cout << result->first << " : " << result->second << endl;
    ++result;
    cout << result->first << " : " << result->second << endl;
    ++result;
    cout << result->first << " : " << result->second << endl;
    ++result;
    cout << result->first << " : " << result->second << endl;
    ++result;
    cout << result->first << " : " << result->second << endl;

}
