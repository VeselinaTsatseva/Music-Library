//
//  Song.hpp
//  Music Library
//
//  Created by Veselina Tsatseva on 7.12.20.
//

#ifndef Song_hpp
#define Song_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <map>
#include <iostream>
using namespace std;

class Song
{
public:
    Song();
   
    int getSongRating(string name);
    int getSongYear(string name);
    
private:
    string name;
    string artist;
    string genre;
    string album;
    int releaseYear;
    double rating;
};


#endif /* Song_hpp */
