#include "json.hpp"
#include "bencode.h"
#include <string>
#include <iostream>
#include <cctype>
#include <sstream>
#include <iomanip>

std::string bytes_to_hex(std::string &bc){
    std::string actual {bc.substr(1, bc.size()-1)};
    std::stringstream ss{};
    for (char &bt : actual){
        ss << std::hex << std::setfill('0') << std::setw(2) << (int)bt;
    }
    return R"(")" + ss.str() + R"(")";
}

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
        std::cerr << "malformed string in element parsing " << sz << " " << s << '\n';
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
            std::string key {parse_bencode(bc, s)};
            res += key;
            res += ": ";
            std::string val {parse_bencode(bc, s)};
            if (key == R"("pieces")"){
                res += bytes_to_hex(val);
            }else{
                res += val;
            }
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
    }else if (std::isdigit(bc[s])){
        res += R"(")";
        res += parse_string(bc, s);
        res += R"(")";
    }else{
        std::cerr << "malformed string in element parsing " << s << '\n';
        std::cerr << res << '\n';
        std::exit(1);
    }
    return res;
}