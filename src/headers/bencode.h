#ifndef TORRENTINSTEAD_BENCODE_H
#define TORRENTINSTEAD_BENCODE_H

#include <string>

std::string bytes_to_hex(std::string &bc);

std::string parse_string(std::string &bc, int &s);

std::string parse_int(std::string &bc, int &s);

std::string parse_bencode(std::string &bc, int &s);

#endif
