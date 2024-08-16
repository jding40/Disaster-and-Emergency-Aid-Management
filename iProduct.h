#ifndef SDDS_IPRODUCT_H
#define SDDS_IPRODUCT_H

#include <iostream>


namespace sdds{

	class iProduct {
	public:
		virtual ~iProduct() {};

		// to read the Stock-Keeping Unit from the console before
		// main data entry
		virtual int readSku(std::istream& istr) = 0;

		// to reduce the quantity on hand
		virtual int operator-=(int qty) = 0;

		// to increase the quantity on hand
		virtual int operator+=(int qty) = 0;

		// returns the price of the produce
		virtual operator double()const = 0;

		// returns if the iProduct is in a good state
		virtual operator bool()const = 0;

		// returns the number of products needed
		virtual int qtyNeeded()const = 0;

		// returns the quantity on hand
		virtual int qty()const = 0;

		// determines if the iProduct is displayed in a linear format or 
		// descriptive format
		virtual void linear(bool isLinear) = 0;

		// saves the iProduct into a file
		virtual std::ofstream& save(std::ofstream& ofstr)const = 0;

		// loads an iProduct from a file
		virtual std::ifstream& load(std::ifstream& ifstr) = 0;
		
		// displays the iProduct on the screen
		virtual std::ostream& display(std::ostream& ostr)const = 0;

		// reads the iProduct from the console
		virtual std::istream& read(std::istream& istr) = 0;

		// return true if the SKU is a match to the iProduct's SKU
		virtual bool operator==(int sku)const = 0;

		// returns true if the description is found in the iPorduct's description
		virtual bool operator==(const char* description)const = 0;

		//Insertion and extraction operator overloads.
		//Overload the Insertion and extraction operators for istream and ostream to call the display and the read methods of the iProduct.
		friend std::ostream& operator <<(std::ostream& os, const iProduct& iproduct);
		friend std::istream& operator >>(std::istream& is, iProduct& iproduct);

		//newly added for MS5-1
		virtual const char* getDesc()const = 0;

		//newly added for MS5-2
		virtual void setSku(int sku) = 0;
		virtual int getSku() const = 0;


	};

















}

#endif