#include "Table.h"
#include <iostream>

namespace table {

    int Table::find(const int &key) const {
        const Element *arr_elem = m_table;

        for (int i = 0; i < m_curr_size; i++) {
            if (arr_elem[i].m_busy && arr_elem[i].m_key == key) { return i; }
        }
        return -1;
    }

    Element Table::findElem(const int &key) const {
        const Element *arr_elem = m_table;

        for (int i = 0; i < m_curr_size; i++) {
            if (arr_elem[i].m_busy && arr_elem[i].m_key == key) { return arr_elem[i]; }
        }
        const Element empty_elem(0, "");
        return empty_elem;
    }

    Table &Table::operator+=(const Element &elem) {
        if (find(elem.m_key) != -1) { throw std::logic_error("invalid key"); }

        if (m_curr_size == ELEM_MAX) {
            if (garbageCollector() == -1) { throw std::logic_error("table overflow"); }
        }

        m_table[m_curr_size] = elem;
        m_curr_size += 1;
        return *this;
    }

    Table &Table::operator-=(const int& key)   {
        int index = find(key);

        if (index == -1) { throw std::logic_error("invalid key"); }
        m_table[index].m_busy = false;
        return *this;
    }

    int Table::garbageCollector() {
        int size = 0;
        for (int i = 0; i < m_curr_size; i++) {
            if (m_table[i].m_busy) {
                if (i != size) { m_table[size] = m_table[i]; }
                size += 1;
            }
        }
        for (int i = size; i < m_curr_size; i++) { m_table[i].m_busy = false; }
        m_curr_size = size;

        return m_curr_size == ELEM_MAX ? -1 : 1;
    }

    std::istream& operator >>(std::istream& i, Table& table) {
        int key;
        if (Tools::getNum(key) == -1) { throw std::logic_error("invalid key"); }

        char info[INF_MAX];
        i.ignore();
        i.getline(info, INF_MAX);

        Element new_elem{key, info};
        table+=new_elem;
        return i;
    }

    std::ostream& operator <<(std::ostream& o, const Element& elem) {
        o << "----------------------------------------------------" << std::endl;
        o << "|      " << elem.m_key << "     ";
        o << "|    " << elem.m_busy << "     ";
        o << "|         " << elem.m_info << "        |" << std::endl;
        o << "----------------------------------------------------" << std::endl;
        return o;
    }

    std::ostream& operator <<(std::ostream& o, Table& table){
        int curr = table.garbageCollector();

        for (int i = 0; i < table.m_curr_size; i++) {
            o << "|  " << i << "  ";
            o << "|      " << table.m_table[i].m_key << "     ";
            o << "|    " << table.m_table[i].m_busy << "     ";
            o << "|         " << table.m_table[i].m_info << "        |" << std::endl;
            o << "----------------------------------------------------" << std::endl;
        }
        return o;
    }

    auto Table::operator[](const int& key) const -> const char (&)[INF_MAX] {
        int index = find(key);
        if (index == -1) { throw std::logic_error("invalid key"); }
        else { return m_table[index].m_info; }
    }

    auto Table::operator[](const int& key) -> char (&)[INF_MAX] {
        int index = find(key);
        if (index == -1){ throw std::logic_error("invalid key"); }
        else { return m_table[index].m_info; }
    }
}