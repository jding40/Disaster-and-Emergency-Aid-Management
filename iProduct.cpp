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

#include "iProduct.h"

namespace sdds {

	std::ostream& operator <<(std::ostream& ostr, const iProduct& iproduct) {
		iproduct.display(ostr);
		return ostr;
	}

	std::istream& operator >>(std::istream& istr, iProduct& iproduct) {
		iproduct.read(istr);
		return istr;
	}

}


