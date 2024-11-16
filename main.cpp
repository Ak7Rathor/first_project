#include <iostream>
#include "Storyboard.cpp"

using namespace std;

int main() {
    Storyboard storyboard;
    int choice;
    string title, text, newTitle, searchText;

    do {
        cout << "\n--- Storyboard Menu ---\n";
        cout << "1. Add Note\n";
        cout << "2. Search Note by Title\n";
        cout << "3. Search Note by Text\n";
        cout << "4. Delete Note\n";
        cout << "5. Modify Note Title\n";
        cout << "6. Modify Note Text\n";
        cout << "7. Display Notes\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice != 8) {
            switch (choice) {
                case 1: 
                    cout << "Enter title: ";
                    getline(cin, title);
                    cout << "Enter text: ";
                    getline(cin, text);
                    if (storyboard.addNote(title, text)) {
                        cout << "Note added successfully.\n";
                    } else {
                        cout << "Failed to add note. Ensure the title is unique and text is valid.\n";
                    }
                    break;

                case 2: 
                    cout << "Enter title to search: ";
                    getline(cin, title);
                    {
                        auto results = storyboard.searchNoteByTitle(title);
                        if (results.empty()) {
                            cout << "No note found with title: " << title << "\n";
                        } else {
                            for (const auto& note : results) {
                                cout << "Found - Title: " << note.title << ", Text: " << note.text << "\n";
                            }
                        }
                    }
                    break;

                case 3: 
                    cout << "Enter text to search: ";
                    getline(cin, searchText);
                    {
                        auto results = storyboard.searchNoteByText(searchText);
                        if (results.empty()) {
                            cout << "No note found with text containing: " << searchText << "\n";
                        } else {
                            for (const auto& note : results) {
                                cout << "Found - Title: " << note.title << ", Text: " << note.text << "\n";
                            }
                        }
                    }
                    break;

                case 4: 
                    cout << "Enter title to delete: ";
                    getline(cin, title);
                    if (storyboard.deleteNote(title)) {
                        cout << "Note deleted successfully.\n";
                    } else {
                        cout << "Note not found.\n";
                    }
                    break;

                case 5: 
                    cout << "Enter old title: ";
                    getline(cin, title);
                    cout << "Enter new title: ";
                    getline(cin, newTitle);
                    if (storyboard.modifyNoteTitle(title, newTitle)) {
                        cout << "Note title modified successfully.\n";
                    } else {
                        cout << "Note not found.\n";
                    }
                    break;

                case 6: 
                    cout << "Enter title of note to modify: ";
                    getline(cin, title);
                    cout << "Enter new text: ";
                    getline(cin, text);
                    if (storyboard.modifyNoteText(title, text)) {
                        cout << "Note text modified successfully.\n";
                    } else {
                        cout << "Note not found.\n";
                    }
                    break;

                case 7: 
                    storyboard.displayNotes();
                    break;

                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        }
    } while (choice != 8);

    cout << "Exiting program.\n";
    return 0;
}
