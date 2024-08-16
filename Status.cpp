/***********************************************************************
// Final project Milestone 2
// Module: Menu and AidMan
// File: main.cpp
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name: Jianzhong Ding           Date: Nov 8th, 2023           Reason
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include"Status.h"
#include "Utils.h"
using namespace std;
namespace sdds {
    Status::Status(const char* description)
    {
        m_stateCode = 0;
        if (description != nullptr)
        {
            ut.alocpy(m_stateDesc, description);
        }
    }
    Status::Status(const Status& stat)
    {


        if (stat.m_stateDesc != nullptr)
        {
            ut.alocpy(m_stateDesc, stat.m_stateDesc);
            m_stateCode = stat.m_stateCode;
        }
        else
        {
            delete[] m_stateDesc;
            m_stateDesc = nullptr;
            m_stateCode = 0;
        }
    }
    Status& Status::operator =(const char* description)
    {
        if (description != nullptr)
        {
            ut.alocpy(m_stateDesc, description);
        }
        return *this;
    }
    Status& Status::operator =(int code)
    {
        m_stateCode = code;
        return *this;

    }
    Status::operator int() const
    {
        return m_stateCode;
    }
    Status::operator const char* () const
    {
        return m_stateDesc;
    }
    Status::operator bool() const
    {
        return m_stateDesc == nullptr;
    }
    Status& Status::clear()
    {
        if (m_stateDesc != nullptr)
        {
            delete[] m_stateDesc;
            m_stateDesc = nullptr;
            m_stateCode = 0;
        }
        return *this;
    }
    Status::~Status()
    {
        delete[] m_stateDesc;
    }

    std::ostream& operator << (std::ostream& ostr, const Status& src) {
        if (!src) {
            if (int(src) != 0)
                ostr << "ERR#" << int(src) << ": ";

            ostr << (const char*)(src);

        }

        return ostr;
    }



}