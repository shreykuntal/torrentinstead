#include "json.hpp"
#include "bencode.h"
#include <string>
#include <iostream>

std::string parse_string(std::string &bc, int &s){
    int sz{0};
    while (s < bc.size() && bc[s] != ':'){
        sz = 10*sz + (bc[s] - '0');
        s++;
    }
    s++;
    std::string elm;
    while (s < bc.size() && sz > 0){
        elm += bc[s];
        sz--;
        s++;
    }
    if (sz > 0){
        std::cerr << "malformed string in element parsing\n";
    }
    return elm;
}

std::string parse_int(std::string &bc, int &s){
    std::string elm{};
    while (s < bc.size() && bc[s] != 'e'){
        elm += bc[s];
        s++;
    }
    if (s == bc.size()){
        std::cerr << "malformed string in element parsing\n";
    }
    return elm;
}

std::string parse_bencode(std::string &bc, int &s){
    std::string res{};
    if (bc[s] == 'd'){
        res += "{";
        s++;
        while (bc[s] != 'e'){
            res += parse_bencode(bc, s);
            res += ": ";
            res += parse_bencode(bc, s);
            if (bc[s] != 'e'){
                res += ',';
            }
        }
        res += "}";
        s++;
    }else if (bc[s] == 'l'){
        res += "[";
        s++;
        while (bc[s] != 'e'){
            res += parse_bencode(bc, s);
            if (bc[s] != 'e'){
                res += ',';
            }
        }
        res += "]";
        s++;
    }else if (bc[s] == 'i'){
        s++;
        res += parse_int(bc, s);
        s++;
    }else if (bc[s] >= '0' && bc[s] <= '9'){
        res += R"(")";
        res += parse_string(bc, s);
        res += R"(")";
    }else{
        std::cerr << "malformed string in element parsing\n";
    }
    return res;
}