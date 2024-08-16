/***********************************************************************
// Final project Milestone 1
// Module: Utils
// File: Utils.h
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name: Jianzhong Ding            Date: Nov 15, 2023            Reason
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <sstream>
#include "Menu.h"
#include "Utils.h"



namespace sdds {

	Menu::Menu(const char* content) {
		int num = -1;
		for (size_t i = 0; i < strlen(content); i++) {
			if (content[i] == '\t'|| content[i] == '\n') num++;
		}

        if (num > 15) { 
            m_numOfChoice = 0;
            m_Content = nullptr; }
        else {
            m_numOfChoice = num;
            m_Content = new char[strlen(content) + 1];
            strcpy(m_Content, content);
        }
	
	}



	Menu::~Menu() {
		delete[] m_Content;
		m_Content = nullptr;
	
	}
  
    /*
    //Project提交的版本
	unsigned int Menu::run() const {
	
            if (!m_Content) {
                std::cout << "Invalid Menu!" << std::endl;
                return 0;
            }

            while (true) {

                size_t optionNum = 1;
                std::istringstream stream(m_Content);
                std::string token;

                while (std::getline(stream, token, '\t')) {
                    std::cout << token;  //removed an endl for MS5-1
                    optionNum++;
                }

                //std::cout << "---------------------------------" << std::endl;// removed fro MS5-1
                std::cout << "0- Exit" << std::endl;

                unsigned int option;
                do {
                    std::cout << "> ";
                    std::cin >> option;

                    if (std::cin.fail()) {
                        std::cout << "Invalid Integer, retry: ";
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        std::cin >> option;
                    }
                    else if (option < 0 || option > m_numOfChoice) {
                        std::cout << "Value out of range [0<=val<=" << m_numOfChoice <<"]: "; //updated from MS1
                        std::cin >> option;
                    }
                } while (option < 0 || option > m_numOfChoice); // ԭΪoptionNum

                if (option == 0) {
                    return option;
                }

                return option;
            }


        }
       */

  
    //2024年1月3日更新版本
    unsigned int Menu::run() const {
        if (!m_Content) {
            std::cout << "Invalid Menu!\n";
            return 0;
        }

        std::istringstream stream(m_Content);
        std::string str;
        int numOfOption = 0;
        while (std::getline(stream, str, '\t')) {
            numOfOption++;
            std::cout << str;
        }

        //std::cout << "---------------------------------\n";
        std::cout << "0- Exit\n";

        unsigned int option = ut.getint(0, m_numOfChoice, "> ", "");

        return option;
    }
 
        

    //newly Added for MS5-1
    Menu& Menu::operator=(int menuOption) {
        if (menuOption != 0) {
            m_numOfChoice = menuOption;
        }
        return *this;
    }

    //newly added for MS5-1
    Menu::Menu(unsigned int numOfChoice, const char* content)
        : m_numOfChoice(numOfChoice), m_Content(nullptr) {
        if (content) {
            m_Content = new char[strlen(content) + 1];
            strcpy(m_Content, content);
        }
    }

    //newly added for MS5-1
    
    Menu& Menu::operator=(const Menu& src)
    {
        if (this != &src && src.m_Content != nullptr)
        {
            delete[] m_Content;
            this->m_Content = nullptr;
            this->m_Content = new char[strlen(src.m_Content) + 1];
            strcpy(this->m_Content, src.m_Content);
            this->m_numOfChoice = src.m_numOfChoice;
        }
        return *this;
    }
    



	
	}



