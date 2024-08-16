#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include "Menu.h"
#include "iProduct.h"

namespace sdds
{
	const int sdds_max_num_items = 100;
	class AidMan
	{
		char* m_filename;
		Menu m_mainMenu;
		iProduct* m_iproductItem[sdds_max_num_items]{};
		int m_numItems;
	public:
		AidMan();
		~AidMan();
		unsigned int menu()const;
		void run();
		//ms 51
		void save();
		void deallocate();
		bool load();
		int list(const char* sub_desc = nullptr);

		//ms5-2
		bool repeatedSKU(int sku)const;
		void addItem();

		//ms5-3
		void remove(int index);
		void removeItem();
		int search(int sku) const;

		//ms5-4
		void updateQty();

		//ms5-5
		void sort();

		//ms5-6
		int shipItems();
	};
}
#endif