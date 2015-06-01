/**
 * @file
 * @brief 随机数,随机串等相关函数
 * @version
 * @remarks
 * @date 2014-05-06
 * @bug
 */


#ifndef _RAND_UTILS_H_
#define _RAND_UTILS_H_

namespace sr
{
    ///> 区间,Open开区间, Close闭区间
    enum Interval {OpenClose, CloseOpen, OpenOpen, CloseClose};

    /**
     * @brief 生成指定范围的随机整数
     * @param[in] min 生成的最小值
     * @param[in] max 生成的最大值
     * @param[in] 区间类型
     * @return 返回指定范围的随机数
     * @attention 调用之前,请配合使用srand函数
     */
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

    /**
     * @brief 生成区间在(0,1)的小数
     * @return 返回一个在区间(0,1)内的随机小数
     */
    double RandDecimal()
    {
        return (rand() / double(RAND_MAX));
    }

    /**
     * @brief 生成随机字符串
     * @param[in] arrRange 指定生成的字符串中各个字符的范围
     * @param[in] nLen 指定生成的随机字符串长度
     * @param[out] sOut 用于存储生成的随机字符串
     * @note 如arrRange="ABCDEF", 则生成的随机字符串将是这几个字母的随机组合.
     */
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
