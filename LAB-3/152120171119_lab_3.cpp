#include <iostream>
#include <string>

using namespace std;

struct Song
{
    string title;
    string artist;
    int ratings[3];
    Song *next;
    Song *prev;
};

Song *head = nullptr;
Song *tail = nullptr;
Song *current = nullptr;

void add(string title, string artist, int r0, int r1, int r2)
{
    Song *newSong = new Song;

    newSong->title = title;
    newSong->artist = artist;
    newSong->ratings[0] = r0;
    newSong->ratings[1] = r1;
    newSong->ratings[2] = r2;
    newSong->next = nullptr;
    newSong->prev = nullptr;

    if (head == nullptr)
    {
        head = newSong;
        tail = newSong;
        current = newSong;
    }
    else
    {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }
}

void goNext()
{
    if (current->next == nullptr)
    {
        cout << "End of the list.\n";
        return;
    }
    cout << "Playing next song.. \n";
    current = current->next;
    cout << "Song: " << current->title << "\n\n";
}

void goPrev()
{
    if (current->prev == nullptr)
    {
        cout << "Top of the list.\n";
        return;
    }
    cout << "Playing previous song.. \n";
    current = current->prev;
    cout << "Song: " << current->title << "\n\n";
}

void removeCurrent()
{
    cout << "Removing the current song.. \n";
    Song *toDelete = current;

    if (toDelete->prev != nullptr)
        toDelete->prev->next = toDelete->next;
    else
        head = toDelete->next;

    if (toDelete->next != nullptr)
        toDelete->next->prev = toDelete->prev;
    else
        tail = toDelete->prev;

    if (toDelete->next != nullptr)
        current = toDelete->next;
    else
        current = toDelete->prev;

    delete toDelete;
}

void display() {
    cout << "\n --- PLAYLIST --- \n";
    for (Song *node = head; node != nullptr; node = node->next) {
        if (node == current)
            cout << "--> ";
        else
            cout << "    ";
 
        cout << node->title << " - " << node->artist << "\n";
        cout << "    Ratings: [ ";
        for (int i = 0; i < 3; i++) {
            cout << node->ratings[i];
            if (i < 2) cout << " | ";
        }
        cout << " ]\n";
    }
    cout << "----------------\n\n";
}

int main() {
    add("Bohemian Rhapsody",       "Queen",        9, 10, 9);
    add("Hotel California",        "Eagles",       8,  9, 8);
    add("Stairway to Heaven",      "Led Zeppelin", 7,  8, 9);
    add("Smells Like Teen Spirit", "Nirvana",      8,  7, 9);
 
    display();

    int secim;
 
    while (true) {
        cout << "1) Next Song  2) Previous Song  3) Remove the Song  4) Display  0) Exit\n";
        cout << "Choice: ";
        cin >> secim;
 
        switch (secim) {
            case 1: goNext();        break;
            case 2: goPrev();        break;
            case 3: removeCurrent(); break;
            case 4: display();       break;
            case 0: return 0;
            default: cout << "[!] Invalid choice.\n";
        }
    }
}