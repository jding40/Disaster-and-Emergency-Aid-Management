#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <limits>
#include <string>
#include "Perishable.h"


namespace sdds{

	

	Perishable::Perishable():Item() {
		m_instruction = nullptr;
		m_expiry.formatted(true);
	};

	
	Perishable::~Perishable() {
		delete[] m_instruction;
		m_instruction = nullptr;
		m_expiry.formatted(false);
	}
	
	Perishable::Perishable(const Perishable& src): Item(src) {
		m_expiry = src.m_expiry;
		m_instruction = nullptr;
		if (src.m_instruction) {
			m_instruction = new char[strlen(src.m_instruction) + 1];
			strcpy(m_instruction, src.m_instruction);
		}
	
	}

	Perishable& Perishable::operator=(const Perishable& src) {
		
		if (this != &src) {
			
			Item::operator=(src);
			delete[]m_instruction;
			m_instruction = new char[strlen(src.m_instruction) + 1];
			strcpy(m_instruction, src.m_instruction);
			m_expiry = src.m_expiry;
		
		}
		return *this;
	
	}
	


	const Date& Perishable::expiry() const {
		return m_expiry;	
	}

	// passed unit test
	int Perishable::readSku(std::istream& istr) {
	
		m_SKU = ut.getint(10000, 39999, "SKU: ");

		return m_SKU;
	}

	//should be OK
	std::ofstream& Perishable::save(std::ofstream& ofstr)const {
	
		if (m_State)
		{
			Item::save(ofstr);
			ofstr << '\t';
			if (m_instruction && m_instruction[0]) ofstr << m_instruction << '\t'; 
			else ofstr << '\t';

			ofstr << m_expiry.unique_Date_Value(); 

		}
		return ofstr;
	
	}

	

	std::ifstream& Perishable::load(std::ifstream& ifstr)
	{
		Item::load(ifstr);
		
		char tempInstruction[1000];
		ifstr.getline(tempInstruction, 1000, '\t');
		delete[] m_instruction;
		m_instruction = nullptr;
		m_instruction = new char[strlen(tempInstruction) + 1];
		strcpy(m_instruction, tempInstruction);
		ifstr >> m_expiry;
		ifstr.ignore();
		if (ifstr.fail()) {
			m_State = "Input file stream read (perishable) failed!";
			return ifstr;
		}
		return ifstr;
	}
	

	



	std::ostream& Perishable::display(std::ostream& ostr)const {
		if (Item::m_SKU != 0) {
			if (!Item::operator bool()) {
				ostr << m_State;
			}
			else if (Item::linear()) {
				Item::display(ostr);

				if (m_instruction) {
					if (m_instruction[0]) {
						ostr << "*";
					}
					else {
						ostr << " ";
					}
				}
				else {
					ostr << " ";
				}


				ostr << m_expiry;
			}
			else {
				ostr << "Perishable ";
				Item::display(ostr);
				ostr << "Expiry date: ";
				ostr << m_expiry;
				if (m_instruction && m_instruction[0]) {
						ostr << "\nHandling Instructions: " << m_instruction;
				}
				ostr << std::endl;
			}
		}
		return ostr;
	}


	//should be OK
	std::istream& Perishable::read(std::istream& istr) {
		Item::read(istr);
		delete[] m_instruction;
		m_instruction = nullptr;
		m_instruction = new char[1000];
		std::cout << "Expiry date (YYMMDD): ";
		istr >> m_expiry;
		istr.ignore();
		std::cout << "Handling Instructions, ENTER to skip: ";
		if (istr.peek() != '\n') 
			istr.getline( m_instruction,1000);
		else {
			strcpy(m_instruction, "");
			istr.ignore();
		}

			if (istr.fail()) {
				m_State = "Perishable console date entry failed!";
			
			}
			m_State = true;
			return istr;
	}





}

