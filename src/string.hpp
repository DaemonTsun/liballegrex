#pragma once

/* string.hpp
 *
 * string utility header
 * str(...)     converts parameters to one string
 * wstr(...)    converts parameters to one wstring
 * bstr<C>(...) converts parameters to one basic_string<C>
 *
 * begins_with(s, prefix)       returns true if prefix is a prefix of s
 * ends_with(s, suffix)         returns true if suffix is a suffix of s
 * repl<Replacement, C...>(s)   replaces all occurances of characters C... in string s with Replacement
 */

#include <sstream>
#include <algorithm>
#include <cctype>
#include <cwctype>

namespace internal
{
    template<typename T>
    using stream_string = std::basic_string<typename T::char_type, typename T::traits_type, typename T::allocator_type>;

    template<typename StringStreamT, typename T>
    stream_string<StringStreamT> _str(StringStreamT &_ss, T &&t)
    {
        _ss << t;
        return _ss.str();
    }

    template<typename StringStreamT, typename T, typename... Ts>
    stream_string<StringStreamT> _str(StringStreamT &_ss, T &&t, Ts &&...ts)
    {
        _ss << t;
        return _str(_ss, std::forward<Ts>(ts)...);
    }
}

template<typename CharT, typename T>
std::basic_string<CharT> bstr(T &&t)
{
    using namespace internal;
    std::basic_stringstream<CharT> _ss;
    _ss << t;
    return _ss.str();
}

template<typename CharT, typename T, typename... Ts>
std::basic_string<CharT> bstr(T &&t, Ts &&...ts)
{
    using namespace internal;
    std::basic_stringstream<CharT> _ss;
    return _str(_ss, std::forward<T>(t), std::forward<Ts>(ts)...);
}

template<typename T>
std::string str(T &&t)
{
    return bstr<std::string::value_type>(std::forward<T>(t));
}

template<typename T, typename... Ts>
std::string str(T &&t, Ts &&...ts)
{
    return bstr<std::string::value_type>(std::forward<T>(t), std::forward<Ts>(ts)...);
}

template<typename T>
std::wstring wstr(T &&t)
{
    return bstr<std::wstring::value_type>(std::forward<T>(t));
}

template<typename T, typename... Ts>
std::wstring wstr(T &&t, Ts &&...ts)
{
    return bstr<std::wstring::value_type>(std::forward<T>(t), std::forward<Ts>(ts)...);
}

// trim from start (in place)
// https://stackoverflow.com/a/217605
inline void ltrim(std::basic_string<char> &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch)
    {
        return !std::isspace(ch);
    }));
}

inline void wltrim(std::basic_string<wchar_t> &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](wint_t ch)
    {
        return !std::iswspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::basic_string<char> &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch)
    {
        return !std::isspace(ch);
    }).base(), s.end());
}

inline void wrtrim(std::basic_string<wchar_t> &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](wint_t ch)
    {
        return !std::iswspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
inline void trim(std::basic_string<char> &s)
{
    ltrim(s);
    rtrim(s);
}

inline void wtrim(std::basic_string<wchar_t> &s)
{
    wltrim(s);
    wrtrim(s);
}

template<typename CharT>
bool begins_with(const std::basic_string<CharT> &value, const std::basic_string<CharT> &prefix)
{
    if (prefix.size() > value.size())
        return false;
    
    return std::equal(prefix.begin(), prefix.end(), value.begin());
}

template<typename CharT>
bool ends_with(const std::basic_string<CharT> &value, const std::basic_string<CharT> &suffix)
{
    if (suffix.size() > value.size())
        return false;
    
    return std::equal(suffix.rbegin(), suffix.rend(), value.rbegin());
}

namespace internal
{
    template<typename CharT, CharT R>
    std::basic_string<CharT> &_repl(std::basic_string<CharT> &s,
                                    typename std::basic_string<CharT>::size_type i)
    {
        return s;
    }

    template<typename CharT, CharT R, CharT Rep, CharT... Reps>
    std::basic_string<CharT> &_repl(std::basic_string<CharT> &s,
                                    typename std::basic_string<CharT>::size_type i)
    {
        auto &c = s[i];

        if (c == Rep)
            c = R;

        return _repl<CharT, R, Reps...>(s, i);
    }
}

template<typename CharT, CharT R, CharT... Reps>
std::basic_string<CharT> &brepl(std::basic_string<CharT> &s)
{
    using str_t = std::basic_string<CharT>;
    using size_type = typename str_t::size_type;

    for (size_type i = 0; i < s.size(); ++i)
        internal::_repl<CharT, R, Reps...>(s, i);

    return s;
}

template<char R, char... Reps>
std::basic_string<char> &repl(std::basic_string<char> &s)
{
    return brepl<char, R, Reps...>(s);
}

template<wchar_t R, wchar_t... Reps>
std::basic_string<wchar_t> &wrepl(std::basic_string<wchar_t> &s)
{
    return brepl<wchar_t, R, Reps...>(s);
}
