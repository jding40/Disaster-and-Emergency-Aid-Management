#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include <iostream>
#include "Status.h"
#define CURRENT_YEAR 2023
#define MAXIMUM_YEAR_VALUE 2030



namespace sdds {

	class Date {
		int m_year;
		int m_month;
		int m_day;
		Status m_status;
		bool m_Formatted;
		bool m_validation;

		bool validate();
		

	public:
		int unique_Date_Value() const;
		Date();
		const Status& status();
		Date(int year, int month, int day);
		operator bool() const;
		const Status& state()const;//
		Date& formatted(bool slash);
		bool operator==(const Date& right) const;
		bool operator!=(const Date& right) const;
		bool operator>=(const Date& right) const;
		bool operator<=(const Date& right) const;
		bool operator<(const Date& right) const;
		bool operator>(const Date& right) const;
		std::ostream& print(std::ostream& os) const;
		std::istream& read(std::istream& istr);



	};

	std::ostream& operator<<(std::ostream& os, const Date& dat);
	std::istream& operator>>(std::istream& is, Date& dat);

}


#endif