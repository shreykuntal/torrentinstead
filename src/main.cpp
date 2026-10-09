#include <iostream>
#include <fstream>
#include "headers/bencode.h"
#include "json.hpp"
#include <string>
#include <iomanip>

int main(){
    std::fstream inf{"ex.torrent"};
    if (!inf){
        std::cerr << "Can't open\n";
        return 1;
    }
    char b;
    std::string s{};
    while (inf.get(b)){
        s += b;
    }
    int x {0};
    std::string out {parse_bencode(s, x)};

    //use copy initialization instead of direct list to avoid parsing whole as list
    nlohmann::json json = nlohmann::json::parse(out);
    std::cout << json["announce"] << '\n';
    return 0;
}
