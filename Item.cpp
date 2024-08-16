/***********************************************************************
// Final project Milestone 1
// Module: Item
// File: Item.cpp
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name: Jianzhong Ding            Date: Nov 19, 2023            Reason
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
//#include<sstream>
#include <cstring>
#include<iomanip>
#include <string>
#include "Item.h"
#include"Utils.h"

namespace sdds{
	//create a query called linear that returns the linear flag of the Item
	bool Item::linear() const {
		return m_isLinear;
	}

	//constructor
	Item::Item() {
		m_Price=0.0;
		m_QtyOnHand=0;
		m_QtyNeeded=0;
		m_Desc=nullptr;
		m_isLinear = false;
		m_State = false;
		m_SKU = 0;
	}

	//Rule of Three -> destructor
	Item::~Item() {
		m_Price = 0;
		m_QtyOnHand = 0;
		m_QtyNeeded = 0;
		m_SKU = 0;
		m_isLinear = false;
		m_State = false;
		delete[] m_Desc;//经测试 换成delete m_Desc;也可以正常运行，但不确定有无内存泄漏
		m_Desc = nullptr;		
	}

	
	//Rule of Three -> Copy Assignment Operator 
	Item& Item::operator=(const Item& src) {
		if (this != &src && src) {
			 m_Price = src.m_Price;
			 m_QtyOnHand = src.m_QtyOnHand;
			 m_QtyNeeded = src.m_QtyNeeded;
			delete[] m_Desc;
			 m_Desc = new char[strlen(src.m_Desc)+1];
			 strcpy(m_Desc, src.m_Desc);
			 m_isLinear = src.m_isLinear;
			 m_SKU = src.m_SKU;
			 m_State = src.m_State;
		}
		return *this;
	
	}


	Item::Item(const Item& item)
	{

		if (item)
		{
			m_Price = item.m_Price;
			m_QtyOnHand = item.m_QtyOnHand;
			m_QtyNeeded = item.m_QtyNeeded;
			m_SKU = item.m_SKU;
			m_isLinear = item.m_isLinear;
			m_State = item.m_State;

			m_Desc = new char[strlen(item.m_Desc) + 1];
			strcpy(m_Desc, item.m_Desc);
		}
		else
		{
			m_Desc = nullptr;
		}

	}

	

	//the qtyNeeded method returns the needed-quantity attribute
	int Item::qtyNeeded()const {
		return m_QtyNeeded;	
	}

	//the qty method returns the on-hand quantity attribute
	int Item::qty()const {
		return m_QtyOnHand;
	}

	//the double conversion operator overload returns the price
	Item::operator double() const{
		return m_Price;	
	}

	//the boolean conversion operator overload returns the state of the object being good.
	Item::operator bool()const {
		if (m_Desc && m_Price>=0 && m_QtyOnHand>=0 && m_QtyNeeded>=0 && m_State) return true;
		else return false;
	}

	//the operator-= reduces the on-hand quantity by the received value
	int Item::operator-=(int qty) {
		m_QtyOnHand -= qty;	
		return m_QtyOnHand;
	}

	//the operator+= increases the on-hand quantity by the received value
	int Item::operator+=(int qty) {
		m_QtyOnHand += qty;
		return m_QtyOnHand;
	}

	//the linear modifier sets the linear flag attribute to true or false.
	void Item::linear(bool isLinear) {
		m_isLinear = isLinear;
	}

	//public modifier
	//create a modifier called clear that does not accept any argument and 
	//sets the state of the Item object back to good, by resetting the state attribute.
	void Item::clear() {
		m_State.clear();
	}

	/*
	virtual operator== iProduct overrides
	the integer comparison returns true if the SKU attribute matches the received value
	
	*/
	bool Item::operator==(int sku)const {
		return sku == m_SKU;
	}

	//the constant character pointer comparison searches in the description of the Item for the appearance of the received Cstring.
	//If a match was found it returns true.
	//	If any of the descriptions(The Items or the received value) are null or the match is not found, it will return false.
	bool Item::operator==(const char* description)const {
		if (m_Desc && description) return strstr(m_Desc, description);
		else return false;
	}

	std::ofstream& Item::save(std::ofstream& ofstr)const {
		if (*this)
		{
			ofstr << m_SKU << '\t' << m_Desc <<'\t'<< m_QtyOnHand << '\t' << m_QtyNeeded << '\t';
			ofstr.setf(std::ios::fixed);
			ofstr.precision(2);
			ofstr << m_Price;
			ofstr.unsetf(std::ios::fixed);
		}
		return ofstr;
	}

	

	std::ifstream& Item::load(std::ifstream& ifstr) {
		delete[] m_Desc;
		m_Desc = nullptr;
		
		char temp[1000];

		ifstr >> m_SKU;
		ifstr.ignore();

		ifstr.getline(temp, 1000, '\t');
		m_Desc = new char[strlen(temp) + 1];
		strcpy(m_Desc, temp);

		ifstr >> m_QtyOnHand >> m_QtyNeeded >> m_Price;
		ifstr.ignore();
		if (ifstr.fail()) {
			m_State = "Input file stream read failed!";
			return ifstr;
		}

		return ifstr;
	}
	
	

	std::ostream& Item::display(std::ostream& ostr) const
	{
		if (m_isLinear == true)
		{
			ostr << m_SKU << " | ";
			char des[36];

			strncpy(des, m_Desc, 35);
			des[35] = '\0';
			ostr << std::left << std::setw(35) << des;
			ostr << " | ";
			ostr << std::right << std::setw(4) << m_QtyOnHand << " | " << std::right << std::setw(4)
				<< m_QtyNeeded << " | " << std::right << std::setw(7) << m_Price << " |";
		}
		else
		{
			ostr << "AMA Item:" << std::endl;
			ostr << m_SKU << ": " << m_Desc << std::endl;
			ostr << "Quantity Needed: " << m_QtyNeeded << std::endl;
			ostr << "Quantity Available: " << m_QtyOnHand << std::endl;
			ostr.setf(std::ios::fixed);
			ostr.precision(2);
			ostr << "Unit Price: $" << m_Price << std::endl;
			ostr.setf(std::ios::fixed);
			ostr.precision(2);
			ostr << "Needed Purchase Fund: $";
			ostr << m_Price * (m_QtyNeeded - m_QtyOnHand) << std::endl;
		}
		return ostr;
	}




	int Item::readSku(std::istream& istr)
	{
		
		m_SKU = ut.getint(40000, 99999, "SKU: ");
		
		return m_SKU;
	}

	std::istream& Item::read(std::istream& istr)
	{
		
		std::cout << "AMA Item:" << std::endl;
		std::cout << "SKU: " << m_SKU <<std::endl;

		std::cout << "Description: ";
		istr.ignore();
		char temp[2000];
		istr.getline(temp, 2000);
		delete[] m_Desc;
		m_Desc = new char[strlen(temp) + 1];
		strcpy(m_Desc, temp);

		
		m_QtyNeeded = ut.getint(1, 9999, "Quantity Needed: ");

		
		//m_QtyOnHand = ut.getint(0, 22, "Quantity On Hand: ");
		m_QtyOnHand = ut.getint(0, 500, "Quantity On Hand: "); //updated for MS5-2

		

		std::cout << "Unit Price: $";
		while (true) {
			istr >> m_Price;
			
				if (istr.fail())
				{
					std::cout << "Invalid number, retry: ";
					istr.clear();
					istr.ignore(1000, '\n');
					continue;
				}

				else if (m_Price < 0 || m_Price > 9999.0)
				{
					std::cout << "Value out of range [0.00<=val<=9999.00]: ";
					continue;
				}
				else break;
			};

			
			if (!istr) {
				m_State = "Console entry failed!";
			}
			
			return istr;
		

	}
	
	//newly added for MS5-1
	const char* Item:: getDesc() const {
		return m_Desc;
	}
	
	//Newly added for MS-2
	void Item::setSku(int sku) {
		m_SKU = sku;
	}

	int Item::getSku()const {
		return m_SKU;
	}









}