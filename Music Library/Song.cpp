//
//  Song.cpp
//  Music Library
//
//  Created by Veselina Tsatseva on 7.12.20.
//

#include "Song.hpp"

Song::Song() { }

int Song::getSongRating(string name)   
{
    ifstream file("Songs.txt");
    
    if (!file.is_open())
    {
        cout<<"Can't open file.\n";
        return 0;
    }
    
    string line, songName, rating;
    size_t dash;
    
    while (getline(file, line))
    {
        dash = line.find(" - ");
        songName = line.substr(0, dash);
        
        if (name == songName)
        {
            rating = line.substr(line.size() - 1 , 1);
        }
    }
    return stoi(rating);
}

int Song::getSongYear(string name)
{
    ifstream file("Songs.txt");
    
    if (!file.is_open())
    {
        cout<<"Can't open file.\n";
        return 0;
    }
    
    string line, songName, year;
    size_t dash, begin;
    
    while (getline(file, line))
    {
        dash = line.find(" - ");
        songName = line.substr(0, dash);
        begin = line.find("[") - 6;
        
        if (name == songName)
        {
            year = line.substr(begin, 4);
        }
    }
    return stoi(year);
}



