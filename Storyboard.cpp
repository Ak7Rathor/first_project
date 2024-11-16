#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <regex>

using namespace std;

class Note {
public:
    string title;
    string text;

    Note(const string& t, const string& tx) : title(t), text(tx) {}
};

class Storyboard {
private:
    vector<Note> notes;
    const string filename = "notes.txt";

    bool isValidText(const string& text) {
        regex validTextRegex("^[A-Za-z0-9 .,]+$");
        return regex_match(text, validTextRegex);
    }

    void saveToFile() {
        ofstream outFile(filename, ios::trunc);
        if (!outFile) {
            cerr << "Error: Could not open file for saving.\n";
            return;
        }
        for (const auto& note : notes) {
            outFile << note.title << "\n" << note.text << "\n";
        }
        outFile.close();
    }

    void loadFromFile() {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "Error: Could not open file for loading. Starting with an empty storyboard.\n";
            return;
        }
        string title, text;
        while (getline(inFile, title) && getline(inFile, text)) {
            notes.emplace_back(title, text);
        }
        inFile.close();
    }

public:
    Storyboard() {
        loadFromFile();
    }

    bool addNote(const string& title, const string& text) {
        if (!isValidText(text)) {
            cout << "Invalid text. Only letters, numbers, spaces, '.', ',' are allowed.\n";
            return false;
        }

        for (const auto& note : notes) {
            if (note.title == title) {
                cout << "A note with this title already exists.\n";
                return false;
            }
        }

        notes.emplace_back(title, text);
        saveToFile();
        return true;
    }

    vector<Note> searchNoteByTitle(const string& title) const {
        vector<Note> results;
        for (const auto& note : notes) {
            if (note.title == title) {
                results.push_back(note);
            }
        }
        return results;
    }

    vector<Note> searchNoteByText(const string& text) const {
        vector<Note> results;
        for (const auto& note : notes) {
            if (note.text.find(text) != string::npos) {
                results.push_back(note);
            }
        }
        return results;
    }

    bool deleteNote(const string& title) {
        auto it = remove_if(notes.begin(), notes.end(), [&](const Note& note) {
            return note.title == title;
        });

        if (it != notes.end()) {
            notes.erase(it, notes.end());
            saveToFile();
            return true;
        }
        return false;
    }

    bool modifyNoteTitle(const string& oldTitle, const string& newTitle) {
        for (auto& note : notes) {
            if (note.title == oldTitle) {
                note.title = newTitle;
                saveToFile();
                return true;
            }
        }
        return false;
    }

    bool modifyNoteText(const string& title, const string& newText) {
        if (!isValidText(newText)) {
            cout << "Invalid text. Only letters, numbers, spaces, '.', ',' are allowed.\n";
            return false;
        }

        for (auto& note : notes) {
            if (note.title == title) {
                note.text = newText;
                saveToFile();
                return true;
            }
        }
        return false;
    }

    void displayNotes() const {
        if (notes.empty()) {
            cout << "No notes available.\n";
            return;
        }

        for (const auto& note : notes) {
            cout << "Title: " << note.title << ", Text: " << note.text << "\n";
        }
    }
};
