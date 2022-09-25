//
//  User.cpp
//  Music Library
//
//  Created by Veselina Tsatseva on 7.12.20.
//

#include "User.hpp"

const string cinTerminator = "end";

User::User() { }

void User::createAccount()
{
    ofstream file("UserAccounts.txt", ios::app);
    
    if (!file.is_open())
    {
        cout<<"Can't open file.\n";
        return;
    }
    
    string genre;
    
    cout<< "Username: ";
    cin>> username;
    cout<< "Password: ";
    cin>> password;
    cin.ignore();
    cout<< "Name: ";
    getline(cin, name);
    cout<< "Birth Date: ";
    cin>> day;
    cout<<"/";
    cin>> month;
    cout<<"/";
    cin>> year;
    cout<<"Favourite genres (enter 'end' when done): ";
    while ((cin >> genre) && genre != cinTerminator)
    {
       favGenres.push_back(genre);
    }
  
    file <<"\n"<<username <<" "<< password <<" "<< name <<" "<< day <<"/"<< month <<"/"<< year << " [";
    for (int i=0; i < favGenres.size(); i++)
    {
        file << favGenres.at(i)<< " ";
    }
    file << "]";
    
    file.close();
    
    cout << "Account created!\n";
}

void User::logIn()
{
    ifstream file("UserAccounts.txt");
    
    if (!file.is_open())
    {
        cout<<"Can't open file.\n";
        return;
    }
    
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    
    string word;
    while(file >> word)
    {
        if (word == username)
        {
            ws(file);
            size_t size = password.length();
            char* buffer = new char [size];
            
            file.read(buffer, size);
            buffer[size] = '\0';
            
            if (buffer == password)
            {
                userMenu();
                break;
            }
            else
            {
                cout<<"Incorrect username or password.\n";
                break;
            }
        }
    }
    
    file.close();
}


void User::userMenu()
{
    int choice;
    
    cout<<"\n--- Account menu ---\n";
    cout<<"1.Change data.\n"<<"2.Generate playlist.\n"<<"3.Add song to a playlist.\n"
        <<"4.Open playlist.\n"<<"Enter your choice: ";
    cin>> choice;
    
    switch (choice)
    {
        case (1):
            changeMenu();
            break;
            
        case (2):
            playlistMenu();
            break;
            
        case (3):
            playlist.addSong();
            break;
            
        case (4):
            playlist.openPlaylist();
            break;
            
            
        default:
            break;
    }
}

void User::changeMenu()
{
    int choice;
    string newData, genre;
    
    cout<<"\n1.Change username.\n"<<"2.Change password.\n"<<"3.Change name.\n"<<"4.Add favorite genre.\n"
        <<"5.Remove favorite genre.\n"<<"Enter your choice: ";
    cin>> choice;
    
    switch (choice)
    {
        case (1):
            cout<< "Enter your current username: ";
            cin>> username;
            cout<< "Enter new username: ";
            cin>> newData;
            changeData("UserAccounts.txt", newData, username);
            break;
            
        case (2):
            cout<< "Enter your current password: ";
            cin>> password;
            cout<< "Enter new password: ";
            cin>> newData;
            changeData("UserAccounts.txt", newData, password);
            break;
            
        case (3):
            cout<<"Enter your current name: ";
            cin>> name;
            cout<< "Enter new name: ";
            cin>> newData;
            changeData("UserAccounts.txt", newData, name);
            break;
            
        case (4):
            cout<< "Enter your username: ";
            cin>> username;
            cout<< "Enter the genre you want to add: ";
            cin>> genre;
            addGenre("UserAccounts.txt", genre, username);
            break;
            
        case (5):
            cout<< "Enter your username: ";
            cin>> username;
            cout<< "Enter the genre you want to remove: ";
            cin>> genre;
            removeGenre("UserAccounts.txt", genre, username);
            break;
            
        default:
            break;
    }
}

void User::changeData(const string& fileName, string newData, string data)
{
    ifstream file(fileName);
    ofstream tempFile("Temp.txt");
    
    if (!file.is_open() || !tempFile.is_open())
    {
        cout<<"Can't open file.\n";
        return;
    }
    
    string word;
   
    while (file >> word)
    {
        if (word != data)
        {
            tempFile << word << " ";
        }
        if (word == data)
        {
            tempFile << newData << " ";
        }
        if (word == "]")
        {
            tempFile << "\n";
        }
    }
    
    tempFile.close();
    file.close();
    
    const char* removedName = fileName.c_str();
    remove(removedName);
    rename("Temp.txt", removedName);
    
    cout<<"-Data saved.-\n";
}

void User::addGenre(const string& fileName, const string& genre, const string& username)
{
    ifstream file(fileName);
    ofstream tempFile("Temp.txt");
    
    if (!file.is_open() || !tempFile.is_open())
    {
        cout<<"Can't open file.\n";
        return;
    }
    
    string line, userName;
    size_t spacePos, size;
    
    while (getline(file, line))
    {
        spacePos = line.find(" ");
        userName = line.substr(0, spacePos);
        
        if(userName == username)
        {
            size = line.size();
            for (int i = 0; i < size; i++)
            {
                if (line[i] != '[')
                {
                    tempFile << line[i];
                }
                if (line[i] == '[')
                {
                    tempFile << "[" << genre << " ";
                }
                if (line[i] == ']')
                {
                    tempFile << "\n";
                }
            }
        }
        else
        {
            tempFile << line <<"\n";
        }
    }
    
    tempFile.close();
    file.close();
    
    const char* removedName = fileName.c_str();
    remove(removedName);
    rename("Temp.txt", removedName);
    
    cout<<"-Data saved.-\n";
}

const string constructword(const string& line, size_t& i)
{
    if (line[i] == ' ' || line[i] == '[' || line[i] == ']')
    {
        i++;
    }
    
    string word;
    while (isalpha(line[i]) || isdigit(line[i]) || line[i] == '/')
    {
        word += line[i++];
    }
    
    return word;
}

void User::removeGenre(const string& fileName, const string& genre, const string& username)
{
    ifstream file(fileName);
    ofstream tempFile("Temp.txt");
    
    if (!file.is_open() || !tempFile.is_open())
    {
        cout<<"Can't open file.\n";
        return;
    }
    
    string line, userName, word;
    size_t spacePos, size;
    
    while (getline(file, line))
    {
        spacePos = line.find(" ");
        userName = line.substr(0, spacePos);
        
        if(userName == username)
        {
            size = line.size();
            for (size_t i=0; i<size; i++)
            {
                word = constructword(line, i);
                
                if (word != genre)
                {
                    tempFile << word << " ";
                }
                if (word == genre)
                {
                    tempFile << "[";
                }
                if (line[i] == ']')
                {
                    tempFile << "]" <<"\n";
                }
            }
        }
        else
        {
            tempFile << line <<"\n";
        }
    }
    
    tempFile.close();
    file.close();
    
    const char* removedName = fileName.c_str();
    remove(removedName);
    rename("Temp.txt", removedName);
    
    cout<<"-Data saved.-\n";
}

void User::playlistMenu()
{
    int numberOfSongs, minRating;
    string playlistName;
    
    cout<<"Enter your username again: ";
    cin>> username;
    cout<<"\n--- Playlist criteria ---\n";
    cout<<"How many songs do you want in your playlist? : ";
    cin>> numberOfSongs;
    cout<<"Minimum rating of the songs: ";
    cin>> minRating;
    cin.ignore();
    cout<<"Name of the playlist: ";
    getline(cin, playlistName);
    
    playlist.generatePlaylist(username, numberOfSongs, minRating, playlistName);
}


