#ifndef SDDS_MENU_H
#define SDDS_MENU_H
namespace sdds {

	class Menu {
		
		
		unsigned int m_numOfChoice;
		char* m_Content{};

		public:
			
			
			Menu(const char* content);
			~Menu();
			//Menu(const Menu&) = delete; //  //remove this restriction due to MS5-1
			//Menu& operator=(const Menu&) = delete;  //remove this restriction due to MS5-1

			unsigned int run() const;

			//newly Added for MS5-1
			Menu& operator=(int menuOption);
			Menu(unsigned int numOfChoice = 0, const char* content = nullptr);
			Menu& operator=(const Menu& mu);



	};
















}

#endif