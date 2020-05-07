#include "wstring.hpp"

// constructor
wstring::wstring(const ull size, const wchar_t *c) {
    m_size = size;
    m_capasity = m_size + capasity_offset;
    m_data = new wchar_t[m_capasity];
    strncpy(m_data, c, m_size);
}

wstring::wstring(const wchar_t *c) {
    m_size = strlen(c);
    m_capasity = m_size + capasity_offset;
    m_data = new wchar_t[m_capasity];
    strncpy(m_data, c, m_size);
}

wstring::wstring(const wstring &s){
    m_capasity = s.m_capasity;
    m_size = s.m_size;
    m_data = new wchar_t[m_capasity];
    strncpy(m_data, (const wchar_t *)s.m_data, m_size);
}

// operator
wstring wstring::operator += (const wchar_t *c){
    unsigned int len = strlen(c);
    ull new_size = this->m_size + len;
    if(new_size > m_capasity){
        while(this->m_capasity < new_size)
            this->m_capasity *= 2;
        wchar_t *new_m_data = new wchar_t[this->m_capasity + 1];
        strncpy(new_m_data, this->m_data, this->m_size);
        delete this->m_data;
        this->m_data = new_m_data;
    }
    m_size = new_size;
    strcat(this->m_data, c);
    return *this;
}

wstring wstring::operator +(const wchar_t *c){
    wstring str(*this);
    str+= c;
    return str;
}

// function
wchar_t * wstring::data() { return m_data; }

ull wstring::size() { return m_size; }

bool wstring::empty() { return m_size == 0 ? true : false; }
