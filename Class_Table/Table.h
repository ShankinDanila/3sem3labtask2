// I decided to make a table without duplicate keys
#pragma once
#include <iostream>
#include <cstring>


namespace table{
    const int INF_MAX = 10;
    const int ELEM_MAX = 15;

    struct Element {
        bool m_busy;
        int m_key;
        char m_info[INF_MAX];
        Element(): m_busy(false), m_key(0) { std::strcpy(m_info, ""); }
        Element(int key_init, const char* info_init): m_key(key_init), m_busy(true) {
            if (strlen(info_init) >= ELEM_MAX){
                throw std::logic_error("string overflow");
            }
            std::strcpy(m_info, info_init);
        }
        friend std::ostream& operator <<(std::ostream&, const Element&);
    };

    class Table {
    private:
        Element m_table[ELEM_MAX];
        int m_curr_size;
    public:
        //constructors/////////////////////////////
        Table(): m_curr_size(0){};
        Table(const Element* arr_elem, int size_init): m_curr_size(size_init){
            for (int i = 0; i < ELEM_MAX; i++){
                m_table[i] = arr_elem[i];
            }
        }

        //setters/////////////////////////////////
        Table& operator +=(const Element& elem);
        Table& operator -=(const int& key);
        int garbageCollector();

        //work with streams//////////////////////
        friend std::istream& operator >>(std::istream&, Table&);
        friend std::ostream& operator <<(std::ostream&, Table&);

        //getters////////////////////////////////
        int find(const int& key) const;
        Element findElem(const int& key) const;
        const Element* getArray() const { return m_table; }
        int getCurrSize() const { return m_curr_size; }
        auto operator [](const int& key) -> char(&)[INF_MAX];
        auto operator [](const int& key) const -> const char(&)[INF_MAX];
    };
}

namespace Tools {
    template <typename T>
    int getNum(T &elem) {
        std::cin >> elem;
        if (std::cin.fail()){
            return 0;
        }
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
            return -1;
        }
        return 1;
    }
}
