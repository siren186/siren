/**
 * 死人
 * siren186@163.com
 * Date: 2014-05-06
 */

#ifndef _RAND_UTILS_H_
#define _RAND_UTILS_H_

namespace sr
{
    ///> 区间,Open开区间, Close闭区间
    enum Interval {OpenClose, CloseOpen, OpenOpen, CloseClose};

    int RandInt(int min, int max, Interval type)
    {
        int nReturn = 0;
        switch (type)
        {
        case OpenClose: ///> (a, b]
            nReturn = rand() % (max - min) + min + 1;
        	break;
        case CloseOpen: ///> [a, b)
            nReturn = rand() % (max - min) + min;
            break;
        case OpenOpen: ///> (a, b)
            nReturn = rand() % (max - min + 1) + min - 1;
            break;
        case CloseClose: ///> [a, b]
            nReturn = rand() % (max - min + 1) + min;
            break;
        default:
            nReturn = (min + max) / 2;
            break;
        }
        return nReturn;
    }

    double RandDecimal()
    {
        return (rand() / double(RAND_MAX)); ///> (0, 1)
    }

    void RandStr(const wchar_t arrRange[], const size_t nLen, std::wstring &sOut)
    {
        sOut.clear();

        if (!arrRange || nLen <= 0)
            return;

        std::wstring sTmp(arrRange);
        int n = 0;

        for (size_t i=0; i<nLen; ++i)
        {
            n = RandInt(0, (int)sTmp.length(), CloseOpen);
            sOut.push_back(sTmp[n]);
        }
    }
} ///> end of namespace sr

#endif ///> _RAND_UTILS_H_
