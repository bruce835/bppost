#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

int main() {
	ifstream index;
	int indexLine = 0;
	int targetLine;
	string indexString;
	string targetLineString;
	string title;
	string input;
	vector<string> indexLines;
	vector<string> otherLines;

	cout << "Target Line: ";
	cin >> targetLineString;
	targetLine = stoi(targetLineString);
	index.open("bruce835.github.io/index.html");

	cout << "\nTitle: ";
	cin >> title;

	while (indexLine < targetLine) {
		indexLine++;
		getline(index, indexString);
		indexLines.push_back(indexString);
	}

	indexLine = 0;
	while (!index.eof()) {
		indexLine++;
		getline(index, indexString);
		otherLines.push_back(indexString);
	}
	
	ofstream indexWrite("index.html", ios::trunc);
	for (const string& currentLine : indexLines)
	{
		indexWrite << currentLine << endl;
	}
	
	indexWrite << "\n<div id=\"post\">";
	indexWrite << "\n<h3>" << title << "</h3>";
	
	 cin.ignore(numeric_limits<streamsize>::max(), '\n');
	 bool writing = false;

	while (true) {
		cout << "Post contents: ";
		getline(cin, input);
		if (input == "image") {
			cout << "Image title: ";
		        getline(cin, input);
			indexWrite << "\n<img src=\"Images/4_2025/" << input << "\"></img>";
		}
		else if (input == "p") {
			cout << "Text: ";
			getline(cin, input);
			indexWrite << "\n<p>" << input << "<br>" <<  endl;
			writing = true;
			while (writing == true) {
				cout << "Text: ";
				getline(cin, input);
				if (input == "\\") {
					indexWrite << "</p>\n";
					writing = false;
				}
				else {
					indexWrite << input << "<br>\n";
				}
			}
		}
		else if (input == "done") {
			indexWrite << "</div>\n";
			break;
		}
	}

		for (const string& currentLine : otherLines) {
			indexWrite << currentLine << endl;
		}
			
	return 0;
}

