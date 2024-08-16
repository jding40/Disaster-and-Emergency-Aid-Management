#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H

namespace sdds {

    class Status {
        char* m_stateDesc{};
        int m_stateCode;
    public:
        Status(const char* description = nullptr);
        Status(const Status& stat);
        Status& operator =(const char* description);
        Status& operator =(int code);
        operator int() const;
        operator const char* () const;
        operator bool() const;
        Status& clear();
        std::ostream& print(std::ostream& ostr) const;
        ~Status();



    };
    std::ostream& operator<<(std::ostream& os, const Status& stat);

}


#endif