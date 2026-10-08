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
    nlohmann::json json {nlohmann::json::parse(parse_bencode(s, x))};
    std::cout << std::setw(4) << json << '\n';
    return 0;
}
