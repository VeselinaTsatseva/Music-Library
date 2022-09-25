//
//  Playlist.cpp
//  Music Library
//
//  Created by Veselina Tsatseva on 7.12.20.
//

#include "Playlist.hpp"

const string constructWord(const string& line, size_t& i)
{
    if (line[i] == ' ')
    {
        i++;
    }
    
    string word;
    while (isalpha(line[i]))
    {
        word += line[i++];
    }
    
    return word;
}

void Playlist::generateSongs(const string& username, const string& playlistName)
{
    ifstream file("UserAccounts.txt");
    
    if (!file.is_open())
    {
        cout<<"Can't open file.\n";
        return;
    }
    
    size_t begin, end, size, spacePos;
    string line, genresList, genreName, userName;
    list<string> userFavGenres;
    
    while (getline(file, line))
    {
        spacePos = line.find(" ");
        userName = line.substr(0, spacePos);
        
        if(userName == username)
        {
            begin = line.find("[") + 1; 
            end = line.find("]");
            genresList = line.substr(begin, end - begin);
            
            size = genresList.size();
            for (size_t i=0; i<size; i++)
            {
                genreName = constructWord(genresList, i);
                userFavGenres.push_back(genreName);
            }
            
            for (list<string>::iterator it = userFavGenres.begin(); it != userFavGenres.end(); it++)
            {
                getSongsByGenre(*it, playlistName);
            }
            break;
        }
    }
    
}

void Playlist::getSongsByGenre(const string& favGenre, const string& playlistName)
{
    ifstream file("Songs.txt");
    ofstream newFile(playlistName, ios::app);
    
    if (!file.is_open() || !newFile.is_open())
    {
        cout<<"Can't open file.\n";
        return;
    }
    
    size_t begin, end;
    string line, genre;
    
    while (getline(file, line))
    {
        begin = line.find("[") + 1;
        end = line.find("]");
        genre = line.substr(begin, end - begin);
        
        if (favGenre == genre)
        {
            newFile << line << "\n";
        }
    }
    
    file.close();
    newFile.close();
}

bool compare(pair<string, int>& s1, pair<string, int>& s2)
{
    return s1.second > s2.second;
}

void Playlist::generatePlaylist(const string& username, int capacity, int minRating, const string& name)
{
    generateSongs(username, name);
    
    ifstream file(name);
    
    if (!file.is_open())
    {
        cout<<"Can't open file.\n";
        return;
    }
     
    string line, songName;
    size_t dash;
    vector<pair<string, int>> songs;
    int choice, year;
    
    cout<<"Song's release year. Choose one: \n"<<"1.Before year - \n"<<"2.From year - \n"<<"3.After year - \n"
        <<"Enter your choice: ";
    cin>> choice;
    cout<<"Enter year: ";
    cin>> year;
    
    while (getline(file, line))
    {
        dash = line.find(" - ");
        songName = line.substr(0, dash);
            
         switch (choice)
         {
             case (1):
                 if(song.getSongRating(songName) >= minRating && song.getSongYear(songName) < year)
                 {
                     songs.push_back(make_pair(line, song.getSongRating(songName)));
                 }
                 break;
                 
             case (2):
                 if(song.getSongRating(songName) >= minRating && song.getSongYear(songName) == year)
                 {
                     songs.push_back(make_pair(line, song.getSongRating(songName)));
                 }
                 break;
                 
             case (3):
                 if(song.getSongRating(songName) >= minRating && song.getSongYear(songName) > year)
                 {
                     songs.push_back(make_pair(line, song.getSongRating(songName)));
                 }
                 break;
                 
             default:
                 break;
         }
    }
    sort(songs.begin(), songs.end(), compare);
    
    songs.resize(capacity);
    
    ofstream playlistFile(name, ios::trunc);
    
    for (vector<pair<string, int>>::iterator it = songs.begin(); it != songs.end(); it++)
    {
        playlistFile << it->first <<"\n";
    }
 
    cout<<"-Playlist generated.-\n"<<endl;
}

void Playlist::addSong()
{
    string fileName, songName, name, line;
    size_t dash;
    
    cout<<"Name of the playlist: ";
    cin>> fileName;
    cin.ignore();
    cout<<"Name of the song you want to add: ";
    getline(cin, name);
    
    ifstream songFile("Songs.txt");
    ofstream playlistFile(fileName, ios::app);
    
    if (!songFile.is_open() || !playlistFile.is_open())
    {
        cout<<"Can't open file.\n";
        return;
    }
    
    while (getline(songFile, line))
    {
        dash = line.find(" - ");
        songName = line.substr(0, dash);
        
        if (name == songName)
        {
            playlistFile << line << "\n";
            cout<<"Song added.\n";
            break;
        }
    }
    
    songFile.close();
    playlistFile.close();
}

void Playlist::openPlaylist()
{
    string playlistName, line;
    
    cin.ignore();
    cout<<"Enter the name of the playlist you want to open: ";
    getline(cin, playlistName);
    cout<<endl;
    
    ifstream file(playlistName);
    
    if (!file.is_open())
    {
        cout<<"Can't open file.\n";
        return;
    }
    
    while (getline(file, line))
    {
        cout<< line <<"\n";
    }
    
    file.close();
}




