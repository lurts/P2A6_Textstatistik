#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>

// text aus datei einlesen
std::vector<std::string> readFile(std::string path);

// häufigkeit der buchstaben bestimmen
std::map<char, int> letterFreq(std::vector<std::string>& words);

// häufigkeit der wörter bestimmen
std::set<std::string> wordFreq(std::vector<std::string>& words, unsigned int n);

// tabelle ausgeben
void printStatistic(std::string& path, unsigned int begin, unsigned int end);