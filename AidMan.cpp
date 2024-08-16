#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
//#include <sstream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <string>
#include "Utils.h"
#include "Perishable.h"
#include "Item.h"
#include "Date.h"
#include "AidMan.h"


namespace sdds
{

    AidMan::AidMan()
    {
        m_filename = nullptr;
        m_mainMenu = 7;
        m_mainMenu = "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n";
        m_numItems = 0;
        m_iproductItem[0] = NULL;
    }

    AidMan::~AidMan()
    {
        save();
    }

    unsigned int AidMan::menu() const
    {
        Date date{};
        std::cout << "Aid Management System\n";
        std::cout << "Date: " << date << std::endl;
        std::cout << "Data file: ";
        m_filename? std::cout << m_filename << std::endl : std::cout << "No file" << std::endl;
        std::cout << "---------------------------------\n";

        return m_mainMenu.run();    //m_mainMenu为AidMan的成员变量，类型为menu，该函数返回值为unsigned int
    }


    void AidMan::run()
    {
        unsigned int choice = -1;
        do {
            choice = menu();                                            
            if (choice != 0 && m_filename == nullptr && choice != 7) {
                std::cout << "\n****New/Open Aid Database****\n";
                load();
            }
            else if (choice == 1) {
                std::cout << "\n****List Items****\n";
                int count = list();
                int recordNo = 0;
                if (count != 0) {
                    std::cout << "Enter row number to display details or <ENTER> to continue:" << std::endl;
                    std::cout << "> ";
                
                    std::cin.ignore();                                                                       //增加了一个ignore
                    if (std::cin.peek() != '\n') {
                        std::cin >> recordNo;
                    }


                    else {
                        std::cin.ignore();
                        std::cout << std::endl;
                    }

                }

                if (recordNo != 0) {
                    m_iproductItem[recordNo - 1]->linear(false);
                    std::cout << *m_iproductItem[recordNo - 1] << std::endl << std::endl;
                }
            }
            else if (choice == 2) {
                std::cout << "\n****Add Item****\n";
                addItem();
                std::cout << std::endl;
               
            }
            else if (choice == 3) {
                std::cout << "\n****Remove Item****\n";
                removeItem();
            }
            else if (choice == 4) {
                std::cout << "\n****Update Quantity****\n";
                updateQty();
               
            }
            else if (choice == 5) {
                std::cout << "\n****Sort****\n";
                sort();
                std::cout << "Sort completed!\n\n";
              
            }
            else if (choice == 6) {
                std::cout << "\n****Ship Items****\n";
                std::cout << "Shipping Order for " << shipItems() << " times saved!\n\n" ;
              
            }
            else if (choice == 7) {
                std::cout << "\n****New/Open Aid Database****\n";
                load();
            }
        } while (choice != 0);
        std::cout << "Exiting Program!\n";
    }


    void AidMan::save() {
        if (m_filename) {
            std::ofstream file(m_filename);
            if (file.is_open()) {
                for (int i = 0; i < m_numItems; i++) {
                    m_iproductItem[i]->linear(false);
                    m_iproductItem[i]->save(file);
                    file << std::endl;
                }
            }
            file.close();
        }

        for (int i = 0; i < m_numItems; i++) {
            delete m_iproductItem[i];
        }
        delete[] m_filename;
        m_numItems = 0;

    }

    

    bool AidMan::load() {
        save();
        std::string filename;

        std::cout << "Enter file name: ";
        std::cin >> filename;
        m_filename = new char[strlen(filename.c_str()) + 1];
        strcpy(m_filename, filename.c_str());
        std::ifstream file(m_filename);
        if (!file.is_open()) {
            int selection = 0;
            std::cout << "Failed to open " << m_filename << " for reading!" << std::endl
            << "Would you like to create a new data file?" << std::endl
            << "1- Yes!" << std::endl << "0- Exit\n>";
            std::cin >> selection;
            if (selection == 1) {
                std::ofstream fptr(m_filename);
                fptr.close();
            }
        }
        else {
            int i = 0;
            while (!file.eof()) {
                char ch{};
                ch = file.peek();
                iProduct* temp = nullptr;
                if (ch >= '1' && ch <='3') { 
                    temp = new Perishable();
                }
                else if (ch >= '4' && ch <= '9') {
                    temp = new Item();
                }
                else {
                }
                if (temp == nullptr) {
                    delete[] m_iproductItem[i];
                }
                else {
                    temp->load(file);
                    m_numItems++;
                    m_iproductItem[i] = temp;
                }
                i++;
            }
        }
        std::cout << m_numItems << " records loaded!" << "\n\n";                     //print the 18th line
        return m_numItems != 0;
    }

    
    int AidMan::list(const char* desc) {
        int count = 0;
        std::cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << std::endl;
        std::cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;
        if (!desc) {
            for (int i = 0; i < m_numItems; i++) {
                m_iproductItem[i]->linear(true);
                
                std::cout << std::right << std::setw(4) << i+1 << " | " << *m_iproductItem[i] << std::endl;
               
                count++;
            }
        }
        else {
            for (int i = 0; i < m_numItems; i++) {
                if (strstr(m_iproductItem[i]->getDesc(), desc)) {
                    m_iproductItem[i]->linear(true);
                    
                    std::cout << std::right << std::setw(4) << i + 1 << " | " << *m_iproductItem[i] << std::endl;
                    count++;

                }
            }
        }
        std::cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;


        if (count == 0) {
            std::cout << "The list is empty!\n\n";
        }
        return count;
    }

    // For ms5-2
    void AidMan::addItem() {
        if (m_numItems == sdds_max_num_items) {
            std::cout << "Database full!";
        }
        else {
            
            Menu addingMenu(2, "1- Perishable\n2- Non-Perishable\n-----------------\n");                            //updated for MS52
            int choice = 0;
            choice = addingMenu.run();
            if (choice != 0) {
                iProduct* newP = nullptr;
                if (choice == 1) {
                    newP = new Perishable();
                }
                else {
                    newP = new Item();
                }
                int sku = ut.getint(10000, 99999, "SKU: ");
                if (repeatedSKU(sku)) {
                    std::cout << "Sku: " << sku << " is already in the system, try updating quantity instead." << std::endl;
                    delete newP;
                }
                else {
                    newP->setSku(sku);
                    newP->read(std::cin);
                    m_iproductItem[m_numItems] = newP; //not checked the validation of the item
                    m_numItems++;

                }

            }
            else {
                std::cout << "Aborted" << std::endl;

            }
        }
    }

    // For ms5-2
    bool AidMan::repeatedSKU(int sku)const {
        bool existence = false;
        for (int i = 0; i < m_numItems && !existence; i++) {
            if (m_iproductItem[i]->getSku() == sku) {
                existence = true;
            }
        }
        return existence;
    }

 
    // For MS5-3
    void AidMan::remove(int index) {

        if (index == m_numItems - 1)
        {
        }
        else {
            delete m_iproductItem[index];
            m_iproductItem[index] = nullptr;

            for (int i = index; i < m_numItems; i++) {

                m_iproductItem[i] = m_iproductItem[i + 1];

            }

        }
        delete  m_iproductItem[m_numItems - 1];
        m_iproductItem[m_numItems - 1] = nullptr;
        m_numItems--;

    }

    // For MS5-3
    //find the index according to given SKU
    int AidMan::search(int sku)const {
        int index = -1;
        for (int i = 0; i < m_numItems && index == -1; i++) {
            if (m_iproductItem[i]->getSku() == sku) {
                index = i;
            }
        }
        return index;
    }

    // For MS5-3
    void AidMan::removeItem() {
        std::cout << "Item description: ";
        char temp[40];
        std::cin.ignore();
        scanf("%39[^\n]", temp);
        if(list(temp)==0) std::cout << "No matches found!" << std::endl;
        else{
            //std::cout << "Enter SKU: ";
            int sku = ut.getint("Enter SKU: ");
            int index=-1;
            if (search(sku) == -1) std::cout << "SKU not found!";
            else
            {
                std::cout << "Following item will be removed: " << std::endl;
                index = search(sku);
                m_iproductItem[index]->linear(false);
                m_iproductItem[index]->display(std::cout);
                std::cout << std::endl << "Are you sure?" << std::endl;

            }
            Menu removeMenu(1, "1- Yes!\n");                            //updated for MS52
        
            int choice = removeMenu.run();

            if (choice == 1)
            {
                remove(index);
                std::cout << "Item removed!" << std::endl << std::endl;
            }
            else {
                std::cout << "Aborted!" << std::endl;
            }
        
        }
    }

    void AidMan::updateQty() {
        std::cout << "Item description: ";
        std::cin.ignore();
        char temp[40];
        scanf("%39[^\n]", temp);
        
        if (list(temp) == 0) std::cout << "No matches found!" << std::endl;
       
        else {
            int sku = ut.getint("Enter SKU: ");
            std::cin.ignore();
            int index = -1;
            index = search(sku);
            if (index == -1) std::cout << "SKU not found!";
            else
            {
                Menu updateQtyMenu(2, "1- Add\n2- Reduce\n");
                int choice = updateQtyMenu.run();
                std::cin.ignore();
                

                if (choice == 1) {
                        if (m_iproductItem[index]->qty() == m_iproductItem[index]->qtyNeeded()) {
                            std::cout << "Quantity Needed already fulfilled!\n";
                            std::cin.ignore();
                    
                        }
                        else{
                        int qty = ut.getint(1, m_iproductItem[index]->qtyNeeded() - m_iproductItem[index]->qty(), "Quantity to add: ");
                        m_iproductItem[index]->operator+=(qty);
                        std::cout << qty << " items added!" << std::endl << std::endl;
                    }

                }
                else if (choice == 2) {
                        if (m_iproductItem[index]->qty() == 0) std::cout << "Quaintity on hand is zero!\n";
                        else {
                    
                        int qty = ut.getint(1, m_iproductItem[index]->qty(), "Quantity to reduce: ");
                        m_iproductItem[index]->operator-=(qty);
                        std::cout << qty << " items removed!" << std::endl << std::endl;
                    }
                }
                else  std::cout << "Aborted!" << std::endl << std::endl;

            }
           
        
        }

        
    
    
    }

    void AidMan::sort() {

        int i, j ;
        for (i = 0; i < m_numItems; i++) {
            for (j = i+1; j < m_numItems; j++) {
                if ((m_iproductItem[j]->qtyNeeded() - m_iproductItem[j]->qty()) > (m_iproductItem[i]->qtyNeeded() - m_iproductItem[i]->qty())) {
                    iProduct* temp = m_iproductItem[i];
                    m_iproductItem[i] = m_iproductItem[j];
                    m_iproductItem[j] = temp;                              
                }                        
            }              
        }
    }

    
    //std::ofstream& shipItems(std::ofstream&) {
    int AidMan::shipItems() {
    
        Date date{};
        std::ofstream ofstr("shippingOrder.txt");
        ofstr << "Shipping Order, Date: "<<date <<std::endl;
        ofstr << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry\n";
        ofstr << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
        int shipItemNo = 0;
        for (int i = 0; i < m_numItems; i++) {
            if (m_iproductItem[i]->qtyNeeded() == m_iproductItem[i]->qty()) {
                m_iproductItem[i]->linear(true);
                //ofstr << m_iproductItem[i]->save(ofstr);
                shipItemNo++;
                ofstr << std::setw(4) << std::right << shipItemNo << " | " << *m_iproductItem[i] << std::endl;;
                remove(i);
                              
            }
        }
        ofstr << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
        return shipItemNo;
    }
    




}
