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
// Name: Jianzhong Ding            Date: Nov 8, 2023            Reason
***********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Date.h"
#include "Utils.h"
#include <iomanip>
using namespace std;


namespace sdds {

    bool Date::validate() {
        bool validYmd = false;
        int currentYear;
        ut.getSystemDate(&currentYear);
        m_status.clear();
        if (m_year< currentYear || m_year > MAXIMUM_YEAR_VALUE) {
            m_status = "Invalid year in date";
            m_status = 1;
        }
        else if (m_month < 1 || m_month> 12) {
            m_status = "Invalid month in date";
            m_status = 2;
        }
        else if (m_day<1 || m_day > ut.daysOfMon(m_month, m_year)) {
            m_status = "Invalid day in date";
            m_status = 3;
        }
        else if (m_validation == true)
        {
            m_status = 0;
            m_status = "Invalid date value";
        }
        else {
            validYmd = true;

        }

        return validYmd;
    }

    const Status& Date::state()const {
        return m_status;

    }

    int Date::unique_Date_Value() const {
  
        return (m_year - 2000) * 10000 + m_month * 100 + m_day;
    }

    //Construction
    Date::Date() {
        m_Formatted = true;
        m_validation = false;
        int currentYear;
        ut.getSystemDate(&currentYear, &m_month, &m_day);
        m_year = currentYear;
    }

    //construction
    Date::Date(int year, int month, int day)
    {
        m_validation = false;
        m_Formatted = true;
        m_year = year;
        m_month = month;
        m_day = day;
        validate();

    }

    Date::operator bool() const {
        return m_status;
    }


    Date& Date::formatted(bool slash)
    {
        if (slash == false)
        {
            m_Formatted = false;
        }

        return *this;
    }

    bool Date::operator==(const Date& right) const
    {
        return this->unique_Date_Value() == right.unique_Date_Value();
    }
    bool Date::operator!=(const Date& right) const
    {
        return this->unique_Date_Value() != right.unique_Date_Value();
    }
    bool Date::operator>=(const Date& right) const
    {
        return this->unique_Date_Value() >= right.unique_Date_Value();
    }
    bool Date::operator<=(const Date& right) const
    {
        return this->unique_Date_Value() <= right.unique_Date_Value();
    }
    bool Date::operator<(const Date& right) const
    {
        return this->unique_Date_Value() < right.unique_Date_Value();
    }
    bool Date::operator>(const Date& right) const
    {
        return this->unique_Date_Value() > right.unique_Date_Value();
    }

    bool notint(bool chara)
    {
        return chara == true;
    }

    std::istream& Date::read(istream& istr)
    {
        int inputNum;
        int d1;
        int d2;
        int m1;
        int m2;
        int y1;
        int y2;
        istr >> inputNum;
        if (istr)
        {
            if (inputNum <= 9999)
            {
                d2 = inputNum % 10;
                d1 = inputNum / 10 % 10;
                m2 = inputNum / 100 % 10;
                m1 = inputNum / 1000 % 10;             
                
                m_month = (m1 * 10) + m2;                         
                m_day = (d1 * 10) + d2;
                
                ut.getSystemDate(&m_year);
            }
            else if (inputNum >= 100000 && inputNum <= 999999)
            {
                d2 = inputNum % 10;
                d1 = inputNum / 10 % 10;
                m2 = inputNum / 100 % 10;
                m1 = inputNum / 1000 % 10;
                y2 = inputNum / 10000 % 10;
                y1 = inputNum / 100000 % 10;

                m_year = 2000 + ((y1 * 10) + y2);
                m_month = (m1 * 10) + m2;
                m_day = (d1 * 10) + d2;
            }
               
            

        }
        else
        {
            m_validation = true;
        }

        if (!validate())
        {

            istr.setstate(std::ios::badbit);
        }
        return istr;
    }



    std::ostream& Date::print(std::ostream& ostr) const
    {
        if (m_Formatted == true)
        {
            
            ostr << m_year;
            ostr << '/';
            ostr.fill('0');
            ostr.width(2);
            ostr << m_month;
            ostr << '/';
            ostr.width(2);
            ostr << m_day;
            ostr.fill(' ');

            //ostr << m_year << '/' << ostr.fill('0') << ostr.width(2) << m_month << '/' << ostr.width(2) << m_day << ostr.fill(' '); 
            //ostr << m_year << '/' << std::setfill('0') << std::setw(2) << m_month << '/' << std::setw(2) << m_day;



        }
        else if (m_Formatted == false)
        {
            int year = m_year - 2000;
            ostr << year;
            ostr.fill('0');
            ostr.width(2);
            ostr << m_month;
            ostr.width(2);
            ostr << m_day;
            ostr.fill(' ');
        }
        return ostr;
    }

    std::ostream& operator<<(std::ostream& ostr, const Date& tem)
    {
        return tem.print(ostr);
    }

    std::istream& operator>>(std::istream& istr, Date& tem)
    {
        return tem.read(istr);
    }



}
