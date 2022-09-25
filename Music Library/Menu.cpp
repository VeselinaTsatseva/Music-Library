//
//  Menu.cpp
//  Music Library
//
//  Created by Veselina Tsatseva on 13.01.21.
//

#include "Menu.hpp"


void Menu::menu()
{
    int choice;
    cout<<"---- Welcome! ----\n";
    cout<<"1.Log in.\n"<<"2.Create an account.\n"<<"Enter your choice: ";
    cin>>choice;

    switch (choice)
    {
        case (1): user.logIn();
            break;
            
        case (2): user.createAccount();
            break;
            
        default:
            cout<<"Wrong input.\n";
    }

    int choice2;
    cout<< "Do you want to return to the menu?\n";
    cout<< "Enter 1 for YES and 0 for NO : ";
    cin>>choice2;

    switch (choice2)
    {
        case (0): cout<<"Goodbye.\n";
            break;
            
        case (1): menu();
            break;
            
        default: cout<<"Wrong input.\n";
            break;
    }
}


