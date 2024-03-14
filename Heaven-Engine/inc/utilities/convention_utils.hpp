#pragma once

#ifndef CONVENTION_UTILS_HPP
#define CONVENTION_UTILS_HPP

#include <string>
#include <iostream>

static std::string checkName(std::string str){

    // checking if string contains special character
    for(int i=0;i<str.length();i++)
    {
        if ((str[i]>=48 && str[i]<=57)||(str[i]>=65 && str[i]<=90)||(str[i]>=97 && str[i]<=122))
            continue;
        else
            std::cout << "ERROR: No special characters when setting or getting a sound buffer! STR: \"" << str << "\""<< std::endl;
            exit(-1); // when a special character is found then stop the program
    }

    // make all characters to lower case
    for(int j=0;j<str.length();j++){
        str[j]=tolower(str[j]);
    }
    
    return str;
}

#endif