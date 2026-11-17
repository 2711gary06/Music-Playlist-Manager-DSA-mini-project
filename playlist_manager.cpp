#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Song {
    string title;
    string artist;
    double duration;
    Song* next;
    Song* prev;

    Song(string t, string a, double d) {
        title = t;
        artist = a;
        duration = d;
        next = nullptr;
        prev = nullptr;
    }
};

class PlaylistManager {
private:
    Song* head;
    Song* tail;
    Song* currentTrack;

public:
    PlaylistManager() {
        head = nullptr;
        tail = nullptr;
        currentTrack = nullptr;
    }

    void addSong(string title, string artist, double duration) {
        Song* newSong = new Song(title, artist, duration);
        if (!head) {
            head = tail = currentTrack = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        cout << "\n[Success] Added: \"" << title << "\" by " << artist << endl;
    }


    void displayPlaylist() {
        if (!head) {
            cout << "\n[Info] The playlist is empty!" << endl;
            return;
        }

        cout << "\n================ CURRENT PLAYLIST =================\n";
        cout << left << setw(20) << "Title" << setw(20) << "Artist" << setw(10) << "Duration" << endl;
        cout << "---------------------------------------------------\n";

        Song* temp = head;
        while (temp) {
            if (temp == currentTrack) {
                cout << left << setw(20) << (temp->title + " (*)") << setw(20) << temp->artist << setw(10) << temp->duration << " [Now Playing]" << endl;
            } else {
                cout << left << setw(20) << temp->title << setw(20) << temp->artist << setw(10) << temp->duration << endl;
            }
            temp = temp->next;
        }
        cout << "===================================================\n";
        cout << "(*) Current Track indicator" << endl;
    }

    void deleteSong(string title) {
        if (!head) {
            cout << "\n[Error] Playlist is empty!" << endl;
            return;
        }

        Song* temp = head;
        while (temp) {
            if (temp->title == title) {

                if (temp == currentTrack) {
                    if (currentTrack->next) {
                        currentTrack = currentTrack->next;
                    } else if (currentTrack->prev) {
                        currentTrack = currentTrack->prev;
                    } else {
                        currentTrack = nullptr;
                    }
                }


                if (temp->prev) {
                    temp->prev->next = temp->next;
                } else {
                    head = temp->next;
                }

                if (temp->next) {
                    temp->next->prev = temp->prev;
                } else {
                    tail = temp->prev;
                }

                delete temp;
                cout << "\n[Success] Deleted song: \"" << title << "\"" << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "\n[Error] Song with title \"" << title << "\" not found." << endl;
    }


    void playNext() {
        if (!currentTrack) {
            cout << "\n[Error] No songs in the playlist to play!" << endl;
            return;
        }
        if (currentTrack->next) {
            currentTrack = currentTrack->next;
            cout << "\n[Playing] " << currentTrack->title << " by " << currentTrack->artist << endl;
        } else {
            cout << "\n[Info] Reached the end of the playlist!" << endl;
        }
    }


    void playPrev() {
        if (!currentTrack) {
            cout << "\n[Error] No songs in the playlist to play!" << endl;
            return;
        }
        if (currentTrack->prev) {
            currentTrack = currentTrack->prev;
            cout << "\n[Playing] " << currentTrack->title << " by " << currentTrack->artist << endl;
        } else {
            cout << "\n[Info] You are at the beginning of the playlist!" << endl;
        }
    }


    void showCurrent() {
        if (currentTrack) {
            cout << "\n[Now Playing] \"" << currentTrack->title << "\" by " << currentTrack->artist << " (" << currentTrack->duration << " mins)" << endl;
        } else {
            cout << "\n[Info] No song is currently playing." << endl;
        }
    }
};

int main() {
    PlaylistManager myPlaylist;
    int choice;
    string title, artist;
    double duration;

    myPlaylist.addSong("Bohemian Rhapsody", "Queen", 5.55);
    myPlaylist.addSong("Blinding Lights", "The Weeknd", 3.20);
    myPlaylist.addSong("Hotel California", "Eagles", 6.30);

    do {
        cout << "\n--- MUSIC PLAYLIST MANAGER MENU ---" << endl;
        cout << "1. Add Song" << endl;
        cout << "2. Delete Song" << endl;
        cout << "3. Show Playlist" << endl;
        cout << "4. Play Next Song" << endl;
        cout << "5. Play Previous Song" << endl;
        cout << "6. Show Current Track" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter Song Title: ";
                getline(cin, title);
                cout << "Enter Artist: ";
                getline(cin, artist);
                cout << "Enter Duration (in mins): ";
                cin >> duration;
                myPlaylist.addSong(title, artist, duration);
                break;
            case 2:
                cout << "Enter Song Title to Delete: ";
                getline(cin, title);
                myPlaylist.deleteSong(title);
                break;
            case 3:
                myPlaylist.displayPlaylist();
                break;
            case 4:
                myPlaylist.playNext();
                break;
            case 5:
                myPlaylist.playPrev();
                break;
            case 6:
                myPlaylist.showCurrent();
                break;
            case 7:
                cout << "\nExiting Music Playlist Manager. Goodbye!" << endl;
                break;
            default:
                cout << "\n[Error] Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}
