//
//  Playlist.hpp
//  Music Library
//
//  Created by Veselina Tsatseva on 7.12.20.
//

#ifndef Playlist_hpp
#define Playlist_hpp

#include <stdio.h>
#include <list>
#include <vector>
#include "Song.hpp"


class Playlist
{
public:
    void getSongsByGenre(const string& favGenre, const string& playlistName);
    void generateSongs(const string& username, const string& playlistName);
    void generatePlaylist(const string& username, int capacity, int minRating, const string& name);
    void addSong();
    void openPlaylist();
    
private:
    string name;
    int capacity;
    int minRating;
    int year;
    Song song;
};

#endif /* Playlist_hpp */
