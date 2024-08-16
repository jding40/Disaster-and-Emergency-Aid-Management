#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include "Item.h"
#include "Date.h"
#include "Utils.h"

namespace sdds {
	class Perishable : public Item {
		Date m_expiry;
		char* m_instruction;
	public:
		//Default constructor: A Perishable object is created using the default constructor that creates an empty perishable item.
		Perishable();

		//rule of three->destructor
		~Perishable();

		//rule of three->copy constructor
		Perishable(const Perishable&);

		//rule of three->assignment operator
		Perishable& operator=(const Perishable&);

		//Query->Create a constant query called expiry that returns a constant reference of the expiry date.
		const Date& expiry() const;

		//Virtual overrides -> readSKU override
		int readSku(std::istream& istr);

		//Virtual overrides -> save override
		std::ofstream& save(std::ofstream& ofstr)const;

		//Virtual overrides -> load override
		//从输入文件流中读取 Perishable 对象的信息。
		std::ifstream& load(std::ifstream& ifstr);

		//Virtual overrides -> display override
		std::ostream& display(std::ostream& ostr)const;

		//Virtual overrides -> read override
		std::istream& read(std::istream& istr);









	};











}
#endif