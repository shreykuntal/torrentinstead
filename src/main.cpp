#include "bencode.h"
#include "json.hpp"
#include <iostream>
#include <string>

int main(){
    //test bencode parsing
    std::string s{"d8:announce26:http://tracker.example.com4:infod4:name8:test.txt6:lengthi1234e5:piece20:12345678901234567890ee"};
    int i{0};
    std::cout << parse_bencode(s, i) << "\n";
}
