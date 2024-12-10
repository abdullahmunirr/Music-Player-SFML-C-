#include "header.h"
#include <iostream>
#include <SFML/Audio.hpp>
using namespace std;

class SongPlayer
{
    Playlist playlist;
    Undo undo;
    sf::Music music;
    bool isPlaying;
    string currentFilePath;
    string filePath;

public:
    SongPlayer() : isPlaying(false) {}
    void menu()
    {
        cout << "+----------------------------------+" << endl;
        cout << "|            Now Playing           |" << endl;
        cout << "|                                  |" << endl;
        cout << "|     01:23 ━━━━●───── 03:43       |" << endl;
        cout << "|          ㅤ◁ㅤ ❚❚ ㅤ▷            |" << endl;
        cout << "|                                  |" << endl;
        cout << "+----------------------------------+" << endl;
        cout << "|     1. Play a song               |" << endl;
        cout << "|     2. Resume current song       |" << endl;
        cout << "|     3. Add song to the playlist  |" << endl;
        cout << "|     4. Next Song                 |" << endl;
        cout << "|     5. Delete song               |" << endl;
        cout << "|     7. Undo deletion             |" << endl;
        cout << "|     8. Exit                      |" << endl;
        cout << "+----------------------------------+" << endl;
        cout << endl;

        cout << "Choose an option : ";
    }

    void clearScreen()
    {
        system("clear");
    }

    void playSong()
    {
        if (playlist.isEmpty())
        {
            cout << "No songs in the playlist" << endl;
            return;
        }

        Song currentSong = playlist.dequeue();
        if (!music.openFromFile(currentSong.filePath))
        {
            cout << "Error: Could not load the song" << endl;
            return;
        }
        music.play();
        isPlaying = true;
        cout << "Now playing: " << currentSong.songName << " by " << currentSong.artist << endl;
    }

    void resumeSong()
    {
        if (isPlaying)
        {
            cout << "A song is already playing" << endl;
        }
        else if (!currentFilePath.empty() && music.getStatus() == sf::Music::Paused)
        {
            music.play();
            cout << "Resuming song..." << endl;
        }
        else
        {
            cout << "No song to resume!" << endl;
        }
    }

    void addSong()
    {
        string songName, artist, filePath;
        cout << "Enter song name: ";
        getline(cin, songName);
        cout << "Enter artist name: ";
        getline(cin, artist);
        cout << "Enter file path of the song: ";
        getline(cin, filePath);

        Song newSong(songName, artist, filePath);
        playlist.enqueue(newSong);
    }

    void nextSong()
    {
        playSong();
    }

    void deleteSong()
    {
        if (playlist.isEmpty())
        {
            cout << "No songs to delete from the playlist." << endl;
            return;
        }

        Song deletedSong = playlist.dequeue();
        undo.pushSong(deletedSong);
    }

    void undoDeletion()
    {
        Song lastDeletedSong = undo.popSong();
        if (lastDeletedSong.songName != "")
        {
            playlist.enqueue(lastDeletedSong);
        }
    }

    void playSpecificSong(Song song)
    {
        currentFilePath = song.filePath;
        if (!music.openFromFile(currentFilePath))
        {
            cout << "Error: Could not load the song!\n";
            return;
        }
        music.play();
        isPlaying = true;
        cout << "Now playing: " << song.songName << " by " << song.artist << endl;
    }

    void showHistory()
    {
        //
    }

    ~SongPlayer()
    {
        music.stop();
    }
};

int main()
{
    SongPlayer sp;
    int option = 0;
    while (option != 8)
    {
        sp.clearScreen();
        sp.menu();
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (option)
        {
            case 1:
                sp.playSong();
                break;
            case 2:
                sp.resumeSong();
                break;
            case 3:
                sp.addSong();
                break;
            case 4:
                sp.nextSong();
                break;
            case 5:
                sp.deleteSong();
                break;
            case 6:
                sp.undoDeletion();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;

                cout << endl << endl;
        }

        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}