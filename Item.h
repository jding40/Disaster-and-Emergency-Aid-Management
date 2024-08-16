/***********************************************************************
// Final project Milestone 1
// Module: Item
// File: Item.h
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name: Jianzhong Ding            Date: Nov 19, 2023            Reason
***********************************************************************/
// ÐÂÔöº¯Êý const char* getDesc() const;

#pragma once
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include "iProduct.h"
#include "Status.h"
namespace sdds {

	class Item: public iProduct {
		double m_Price;
		int m_QtyOnHand;
		int m_QtyNeeded;
		char* m_Desc;
		bool m_isLinear;

	protected:
		Status m_State;
		int m_SKU;
		bool linear() const;

	public:
		Item();

		//Rule of Three
		~Item();
		Item(const Item& src);
		Item& operator=(const Item& src);

		// virtual public query iProduct overrides
		int qtyNeeded()const;
		int qty()const;
		operator double() const;
		operator bool() const;
		
		//virtual public modifier iProduct overrides
		int operator-=(int qty);
		int operator+=(int qty);
		void linear(bool isLinear);

		//public modifier
		void clear();

		//virtual operator== iProduct overrides
		bool operator==(int sku)const;
		bool operator==(const char* description)const;

		//virtual Input / Output method iProduct overrides
		std::ofstream& save(std::ofstream& ofstr)const;
		std::ifstream& load(std::ifstream& ifstr);
		std::ostream& display(std::ostream& ostr)const;
		virtual int readSku(std::istream& istr);
		std::istream& read(std::istream& istr);



		//Newly added for MS5-1
		const char* getDesc() const;

		//Newly added fro MS5-2
		void setSku(int sku);
		int getSku() const;

	};























}


#endif
