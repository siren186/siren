/**
 * @file
 * @brief ×Ö·û´®²Ù×÷Ïà¹Øº¯Êý
 * @version
 * @remarks
 * 
 * @date 2014-05-06
 * @see http://www.codeproject.com/Articles/1114/STL-Split-String
 * @see http://www.sytarena.com/cjswz/20130527/829.html
 * @bug
 */


#ifndef __STR_UTILS_H__
#define __STR_UTILS_H__

#include <vector>
#include <string>
#include <wchar.h>

namespace sr
{
    /**
     * @brief ÇÐ¸î×Ö·û´®
     * @param[in] sInput ´ýÇÐ¸î×Ö·û´®
     * @param[in] chSplitChar ÓÃÓÚÇÐ¸îµÄ×Ö·û
     * @param[out] vecOutput ÇÐ¸îºóµÄÆ¬¶Î¼¯
     */
    void SplitStringA(const std::string& sInput,  const char chSplitChar, std::vector<std::string>& vecOutput)
    {
        vecOutput.clear();
        std::string::size_type loc_start = sInput.find_first_not_of(chSplitChar);
        std::string::size_type loc_stop = loc_start;
        while(loc_stop != std::string::npos)
        {
            loc_stop = sInput.find_first_of(chSplitChar, loc_start);
            if (loc_stop != std::string::npos)
                vecOutput.push_back(sInput.substr(loc_start, loc_stop - loc_start));
            else
                vecOutput.push_back(sInput.substr(loc_start));
            loc_start = sInput.find_first_not_of(chSplitChar, loc_stop);
            loc_stop = loc_start;
        }
    }

    /**
     * @see SplitStringA
     */
    void SplitStringW(const std::wstring& input, const wchar_t splitChar, std::vector<std::wstring>& output)
    {
        output.clear();
        std::wstring::size_type loc_start = input.find_first_not_of(splitChar);
        std::wstring::size_type loc_stop = loc_start;
        while(loc_stop != std::wstring::npos)
        {
            loc_stop = input.find_first_of(splitChar, loc_start);
            if (loc_stop != std::wstring::npos)
                output.push_back(input.substr(loc_start, loc_stop - loc_start));
            else
                output.push_back(input.substr(loc_start));
            loc_start = input.find_first_not_of(splitChar, loc_stop);
            loc_stop = loc_start;
        }
    }

    /**
     */
    int SplitStringA(const std::string& input,  const std::string& delimiter,  std::vector<std::string>& output, bool includeEmpties)
    {
        output.clear();
        int iPos = 0;
        int newPos = -1;
        int sizeS2 = (int)delimiter.size();
        int isize = (int)input.size();

        if ( ( isize == 0 ) || ( sizeS2 == 0 ) )
            return 0;

        std::vector<int> positions;

        newPos = (int)input.find(delimiter, 0);

        if( newPos < 0 )
        { 
            return 0; 
        }

        int numFound = 0;

        while( newPos >= iPos )
        {
            numFound++;
            positions.push_back(newPos);
            iPos = newPos;
            newPos = (int)input.find(delimiter, iPos+sizeS2);
        }

        if( numFound == 0 )
            return 0;

        int offset = 0;
        for( int i=0; i<=(int)positions.size(); ++i )
        {
            std::string s("");
            if( i == 0 ) 
            { 
                s = input.substr( i, positions[i] ); 
            }
            else
            {
                offset = positions[i-1] + sizeS2;
            }
            if( offset < isize )
            {
                if( i == positions.size() )
                {
                    s = input.substr(offset);
                }
                else if( i > 0 )
                {
                    s = input.substr( positions[i-1] + sizeS2, 
                        positions[i] - positions[i-1] - sizeS2 );
                }
            }
            if( includeEmpties || ( s.size() > 0 ) )
            {
                output.push_back(s);
            }
        }
        return numFound;
    }

    int SplitStringW(const std::wstring& input, const std::wstring& delimiter, std::vector<std::wstring>& output, bool includeEmpties)
    {
        output.clear();
        int iPos = 0;
        int newPos = -1;
        int sizeS2 = (int)delimiter.size();
        int isize = (int)input.size();

        if ( ( isize == 0 ) || ( sizeS2 == 0 ) )
            return 0;

        std::vector<int> positions;

        newPos = (int)input.find(delimiter, 0);

        if( newPos < 0 )
        { 
            return 0; 
        }

        int numFound = 0;

        while( newPos >= iPos )
        {
            numFound++;
            positions.push_back(newPos);
            iPos = newPos;
            newPos = (int)input.find(delimiter, iPos+sizeS2);
        }

        if( numFound == 0 )
            return 0;

        int offset = 0;
        for( int i=0; i<=(int)positions.size(); ++i )
        {
            std::wstring s(L"");
            if( i == 0 ) 
            { 
                s = input.substr( i, positions[i] ); 
            }
            else
            {
                offset = positions[i-1] + sizeS2;
            }
            if( offset < isize )
            {
                if( i == positions.size() )
                {
                    s = input.substr(offset);
                }
                else if( i > 0 )
                {
                    s = input.substr( positions[i-1] + sizeS2, 
                        positions[i] - positions[i-1] - sizeS2 );
                }
            }
            if( includeEmpties || ( s.size() > 0 ) )
            {
                output.push_back(s);
            }
        }
        return numFound;
    }
} ///> end of namespace sr

#endif ///> __STR_UTILS_H__