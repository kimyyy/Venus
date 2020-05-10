#include "common.hpp"
#include "cstring.hpp"

class wstring {
    private:
        wchar_t *m_data;
        ull m_size;
        ull m_capasity;
        unsigned int capasity_offset = 30;

    public:
        // constructor
        wstring(const ull size, const wchar_t *c);
        wstring(const wchar_t *c);
        wstring(const wstring &s);

        //operator
        wstring operator += (const wchar_t *c);
        wstring operator +(const wchar_t *c);

        // function
        wchar_t *data();
        ull size();
        bool empty();
};
