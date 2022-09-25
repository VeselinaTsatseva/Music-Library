//
//  User.hpp
//  Music Library
//
//  Created by Veselina Tsatseva on 7.12.20.
//

#ifndef User_hpp
#define User_hpp

#include <stdio.h>
#include "Playlist.hpp"
#include <iostream>
using namespace std;

class User
{
public:
    User();
    
    void createAccount();
    void logIn();
    void userMenu();
    void changeMenu();
    void playlistMenu();
    void changeData(const string& fileName, string newData, string data);
    void addGenre(const string& fileName, const string& genre, const string& username);
    void removeGenre(const string& fileName, const string& genre, const string& username);
    
private:
    string username;
    string password;
    string name;
    int day;
    int month;
    int year;
    vector<string> favGenres;
    Playlist playlist;
};

#endif /* User_hpp */
