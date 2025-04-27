#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

int p(ofstream& indexWrite, string& input) {
     bool writing = true;
     cout << "Text: ";
     getline(cin, input);
     indexWrite << "\n<p>" << input << "<br>" <<  endl;
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
     return 1;
}

int post(ofstream& indexWrite, string& input) {
        while (true) {
                cout << "Post contents: ";
                getline(cin, input);
                if (input == "image") {
                        cout << "Image title: ";
                        getline(cin, input);
                        indexWrite << "\n<img src=\"Images/4_2025/" << input << "\"></img>";
                }
		
                else if (input == "p") {
			while(true) {
				if(p(indexWrite, input) == 1)
				{
					break;
				}
			}
                }
                else if (input == "done") {
                        indexWrite << "</div>\n";
			indexWrite << "\n<!-- ENDOFPOST -->" << endl;
                        break;
                }
        }
	return 0;
}

int main() {
	ifstream index;
        int indexLine = 0;
        int targetLine;
        string path;
        string indexString;
        string targetLineString;
        string title;
        string input;
        vector<string> indexLines;
        vector<string> otherLines;

	cout << "Path to file(includes filename): ";
	getline(cin, path);
	index.open(path);

	cout << "\nTitle: ";
	cin >> title;

	while (!index.eof()) {
		indexLine++;
		getline(index, indexString);
		if (indexString == "<!-- ENDOFPOST -->") {
			targetLine = indexLine;
			break;
		}
		indexLines.push_back(indexString);
	}

	indexLine = 0;
	while (!index.eof()) {
		indexLine++;
		getline(index, indexString);
		otherLines.push_back(indexString);
	}
	
	ofstream indexWrite(path, ios::trunc);
	for (const string& currentLine : indexLines)
	{
		indexWrite << currentLine << endl;
	}
	
	indexWrite << "\n<div id=\"post\">";
	indexWrite << "\n<h3>" << title << "</h3>";
	
	 cin.ignore(numeric_limits<streamsize>::max(), '\n');

	 while(true) {
		 if (post(indexWrite, input) == 0) {
			for (const string& currentLine : otherLines) {
				indexWrite << currentLine << endl;
			}
		break;
		}
	 }
			
	return 0;
}

