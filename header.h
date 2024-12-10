#include <iostream>
using namespace std;

class Song
{
    public:
    string songName;
    string artist;
    string filePath;

    Song(string n, string a, string p) : songName(n), artist(a), filePath(p) {}
    void displaySong ()
    {
        cout << "Song : " << songName << "Artist: " << artist << endl;
    }
};

class Playlist
{
    private:
    class Node 
    {
        public:
        Song song;
        Node* next;

        Node (Song s) : song (s), next(nullptr) {}
    };

    Node* front;
    Node* rear;

    public: Playlist() : front(nullptr), rear(nullptr) {}

    void enqueue(Song song)
    {
        Node* temp = new Node (song);

        if (rear == nullptr)
        {
            rear = front = temp;
        }
        else 
        {
            rear -> next = temp;
            rear = temp;
        }

        cout << endl << "Song " << temp->song.songName << " by " << temp->song.artist << " is added in the playlist." << endl;
    }

    Song dequeue()
    {
        if (front == nullptr)
        {
            cout << "The playlist is empty!" << endl;
            return Song("", "", "");
        }
        Node* temp = front;
        Song song = temp->song;
        front = front->next;

        if (front == nullptr) 
        {
            rear = nullptr;
        }

        delete temp;
        cout << "Song " << song.songName << " by " << song.artist << " is playing..." << endl;
        return song;
    }


    void playNextSong ()
    {
        if (front == nullptr)
        {
            cout << "There are no songs in the playlist." << endl;
        }
        else
        {
            front -> song.displaySong();
            Node* temp = front;
            front = front -> next;

            if (front == nullptr)
            {
                rear = nullptr;
            }
            delete temp;
        }
    }

    bool isEmpty() 
{
    return front == nullptr;
}

    ~Playlist()
    {
        while (front!=nullptr)
        {
            Node*temp = front;
            front = front-> next;
            delete temp;
        }
    }
};

class Undo 
{
    private:
    class Node 
    {
        public: 
        Song song;
        Node* next;

        Node (Song s) : song(s), next(nullptr) {}
    };
    Node* top;

    public:
    Undo() : top(nullptr) {}

    void pushSong (Song song)
    {
        Node* temp = new Node (song);
        temp->next = top;
        top = temp;

        cout << endl << "Skipped song " << temp->song.songName << " by " << temp->song.artist << endl;
    }

    Song popSong ()
    {
        if (top == nullptr)
        {
            cout << "No songs to undo" << endl;
            return Song("", "", "");
        }
        Node*temp = top;
        Song song = temp-> song;
        top = top->next;
        delete temp;
        cout << "Now playing " << song.songName << " by " << song.artist << endl;
        return song;
    }

    ~Undo()
    {
        while (top!= nullptr)
        {
            Node* temp = top;
            top = top-> next;
            delete temp;
        }
    }
};

class SongHistory
{
    private:
    class Node 
    {
        public:
        Song song;
        Node* prev;
        Node* next;

        Node(Song s) : song(s), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

    public:
    SongHistory() : head(nullptr), tail(nullptr) {}

    void addSong(Song song)
    {
         Node* temp = new Node(song);
        if (tail == nullptr) 
        {
            head = tail = temp;
        } 
        else
        {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
        cout << "Played: " << song.songName << " by " << song.artist << endl;
    }

    void showHistory()
    {
        Node*curr = head;
        cout << " +-----------------------------+" << endl;
        cout << " +         Song History        +" << endl;
        cout << " +-----------------------------+" << endl; 
        while (curr!=nullptr)
        {
            curr->song.displaySong();
            cout << endl;
            curr = curr -> next;
        }
    }

    ~SongHistory()
    {
        while (head!=nullptr)
        {
         Node* temp = head;
         temp = temp -> next;
         delete temp;
        }
    }
};