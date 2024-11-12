#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include "textstatistik.h"

bool isNotAlpha(char c) {
	// ohne static cast kommt ein fehler... warum?
	// funktioniert ohne cast in CLion aber nicht in Visual Studio
	return !isalpha(static_cast<unsigned char>(c));
}

// liest eine textdatei ein und gibt einen vektor mit den einzelnen w�rtern in kleinbuchstaben zur�ck
std::vector<std::string> readFile(std::string path) {
	std::vector<std::string> words;
	std::string word;

	// pfad anpassen (nimmt an dass die txt dateien direkt im root vom projektordner liegen)
    // PROJECT_DIR ist in CMakeLists festgelegt
	path = std::string(PROJECT_DIR) + "/" + path;

	std::ifstream file(path);

	if (!file.is_open()) {
		// wenn datei nicht existiert leeren vektor zur�ckgeben
		return words;
	}

	while (file >> word) {
		// remove_if verschiebt alle zu entfernenden zeichen ans ende und gibt den iterator ab wann die "entfernten"
		// zeichen anfangen zur�ck
		std::string::iterator  it = std::remove_if(word.begin(), word.end(), isNotAlpha);
		// erst hier wird wirklich was aus der string entfernt
		word.erase(it, word.end());
		// zum schluss alles zu kleinbuchstaben machen
		std::transform(word.begin(), word.end(), word.begin(), tolower);

		words.push_back(word);
	}

	file.close();
	return words;
}

std::map<char, int> letterFreq(const std::vector<std::string>& words) {
	// leere map anlegen in der die buchstaben und ihre h�ufigkeit gespeichert werden
	std::map<char, int> frequencyMap;

	// durch die buchstaben iterieren und mitz�hlen
	for (std::string word : words) {
		for (char c : word) {
			frequencyMap[c]++;
		}
	}

	return frequencyMap;
}

// gibt nur w�rter von l�nge n in einem set zur�ck
std::set<std::string> wordFreq(const std::vector<std::string>& words, const unsigned int n) {
	// leeres set anlegen in der die w�rter hinterlegt werden
	std::set<std::string> wordSet;

	// alle w�rter durchlaufen und wenn diese n zeichen lang sind in die map aufnehmen
	for (std::string word : words) {
		if (word.length() == n) {
			wordSet.insert(word);
		}
	}

	return wordSet;
}

void printStatistic(std::string& path, unsigned int minLength, unsigned int maxLength) {
	// vektor mit worten aus datei lesen
	std::vector<std::string> words = readFile(path);

	// h�ufigkeitsmap f�r die buchstaben machen
	std::map<char, int> charCount = letterFreq(words);


	std::cout << "*** H�ufigkeit der Buchstaben ***\n";

	// ein einzelnes element einer map wird zum "pair" 
	// (nach langer recherche im internet gefunden, wollte vermeiden "auto" als datentyp zu nutzen)
	for (std::pair<char, int> p : charCount) {
		std::cout << std::setw(15) << p.first << "\t\t" << std::setw(5) << p.second << "\n";
	}


	std::cout << "\n\n*** H�ufigkeit der W�rter ***\n";

	for (int i = minLength; i <= maxLength; i++)
	{
		std::cout << std::setw(15) << i << "\t\t" << std::setw(5) << wordFreq(words, i).size() << "\n";
	}

	// Benutzereingabe
	int n;
	std::cout << "W�rter mit n Buchstaben anzeigen.\nn: ";
	std::cin >> n;

	for (std::string word : wordFreq(words, n))
	{
		std::cout << word << ", ";
	}
}