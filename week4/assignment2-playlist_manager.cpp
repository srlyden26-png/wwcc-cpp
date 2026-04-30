#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Define the nested structs
struct Artist {
    string name;
    string hometown;
};

struct Song {
    string title;
    Artist artist;
    string genre;
    int durationSeconds;
};

// Helper function to format seconds into M:SS
string formatDuration(int seconds) {
    int minutes = seconds / 60;
    int secs = seconds % 60;
    string secondsStr = (secs < 10) ? "0" + to_string(secs) : to_string(secs);
    return to_string(minutes) + ":" + secondsStr;
}

// Helper to convert string to lowercase for case-insensitive comparison
string toLowercase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

void displaySong(const Song& s, int index) {
    cout << index + 1 << ". " << s.title << endl;
    cout << "   Artist: " << s.artist.name << " (" << s.artist.hometown << ")" << endl;
    cout << "   Genre: " << s.genre << endl;
    cout << "   Duration: " << formatDuration(s.durationSeconds) << endl << endl;
}

int main() {
    const int PLAYLIST_SIZE = 5;
    Song playlist[PLAYLIST_SIZE];
    int totalRuntime = 0;
    int longestIndex = 0;

    cout << "PERSONAL PLAYLIST MANAGER" << endl;
    cout << "--------------------------" << endl;

    // 1. Populate the array with user input
    for (int i = 0; i < PLAYLIST_SIZE; i++) {
        cout << "Enter information for Song " << i + 1 << ":" << endl;
        cout << "  Title: ";
        getline(cin >> ws, playlist[i].title);
        cout << "  Artist name: ";
        getline(cin, playlist[i].artist.name);
        cout << "  Artist hometown: ";
        getline(cin, playlist[i].artist.hometown);
        cout << "  Genre: ";
        getline(cin, playlist[i].genre);
        cout << "  Duration (seconds): ";
        cin >> playlist[i].durationSeconds;

        totalRuntime += playlist[i].durationSeconds;
        if (playlist[i].durationSeconds > playlist[longestIndex].durationSeconds) {
            longestIndex = i;
        }
    }

    // 2. Display Full Playlist
    cout << "\nYOUR PLAYLIST:" << endl;
    cout << "--------------" << endl;
    for (int i = 0; i < PLAYLIST_SIZE; i++) {
        displaySong(playlist[i], i);
    }

    // 3. Display Stats
    cout << "Playlist Stats:" << endl;
    cout << "  Total runtime: " << formatDuration(totalRuntime) << endl;
    cout << "  Longest song:  " << playlist[longestIndex].title 
         << " (" << formatDuration(playlist[longestIndex].durationSeconds) << ")" << endl;

    // 4. Search by Artist
    string searchArtist;
    bool foundArtist = false;
    cout << "\nSearch by artist: ";
    getline(cin >> ws, searchArtist);
    cout << "Songs by " << searchArtist << ":" << endl;
    for (int i = 0; i < PLAYLIST_SIZE; i++) {
        if (toLowercase(playlist[i].artist.name) == toLowercase(searchArtist)) {
            cout << "  - " << playlist[i].title << " (" << formatDuration(playlist[i].durationSeconds) << ")" << endl;
            foundArtist = true;
        }
    }
    if (!foundArtist) cout << "  No results found for that artist." << endl;

    // 5. Search by Genre
    string searchGenre;
    bool foundGenre = false;
    cout << "\nSearch by genre: ";
    getline(cin >> ws, searchGenre);
    cout << "Songs in genre \"" << searchGenre << "\":" << endl;
    for (int i = 0; i < PLAYLIST_SIZE; i++) {
        // Simple check to see if the search string is inside the genre (e.g., "metal" in "Neoclassical metal")
        if (toLowercase(playlist[i].genre).find(toLowercase(searchGenre)) != string::npos) {
            cout << "  - " << playlist[i].title << " (" << formatDuration(playlist[i].durationSeconds) << ")" << endl;
            foundGenre = true;
        }
    }
    if (!foundGenre) cout << "  No results found for that genre." << endl;

    return 0;
}
