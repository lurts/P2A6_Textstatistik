#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <set>
#include "textstatistik.h"

bool isNotAlpha(char c) {
	// ohne static cast kommt ein fehler... warum?
	// funktioniert ohne cast in CLion aber nicht in Visual Studio
	return !isalpha(static_cast<unsigned char>(c));
}

// liest eine textdatei ein und gibt einen vektor mit den einzelnen wörtern in kleinbuchstaben zurück
std::vector<std::string> readFile(std::string path) {
	std::vector<std::string> words;
	std::string word;

	// pfad anpassen (nimmt an dass die txt dateien direkt im root vom projektordner liegen)
	path = std::string(PROJECT_DIR) + "/" + path;

	std::ifstream file(path);

	if (!file.is_open()) {
		// wenn datei nicht existiert leeren vektor zurückgeben
		return words;
	}

	while (file >> word) {
		// remove_if verschiebt alle zu entfernenden zeichen ans ende und gibt den iterator ab wann die "entfernten"
		// zeichen anfangen zurück
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

std::map<char, int> letterFreq(std::vector<std::string>& words) {
	// leere map anlegen in der die buchstaben und ihre häufigkeit gespeichert werden
	std::map<char, int> frequencyMap;

	// durch die buchstaben iterieren und mitzählen
	for (std::string word : words) {
		for (char c : word) {
			frequencyMap[c]++;
		}
	}

	return frequencyMap;
}

// gibt nur wörter von länge n in einem set zurück
std::set<std::string> wordFreq(std::vector<std::string>& words, unsigned int n) {
	// leeres set anlegen in der die wörter hinterlegt werden
	std::set<std::string> wordSet;

	// alle wörter durchlaufen und wenn diese n zeichen lang sind in die map aufnehmen
	for (std::string word : words) {
		if (word.length() == n) {
			wordSet.insert(word);
		}
	}

	return wordSet;
}

void printStatistic(std::string& path, unsigned int begin, unsigned int end) {
	// vektor mit worten aus datei lesen
	std::vector<std::string> words = readFile(path);

	// häufigkeitsmap für die buchstaben machen
	std::map<char, int> charCount = letterFreq(words);


	std::cout << "*** Häufigkeit der Buchstaben ***\n";

	for (auto p : charCount) {
		std::cout << std::setw(15) << p.first << "\t\t" << std::setw(5) << p.second << "\n";
	}
	std::cout << "\n\n*** Häufigkeit der Wörter ***\n";

	for (int i = begin; i <= end; i++)
	{
		std::cout << std::setw(15) << i << "\t\t" << std::setw(5) << wordFreq(words, i).size() << "\n";
	}

	// Benutzereingabe
	int n;
	std::cout << "Wörter mit n Buchstaben anzeigen.\nn: ";
	std::cin >> n;

	for (std::string word : wordFreq(words, n))
	{
		std::cout << word << ", ";
	}
}