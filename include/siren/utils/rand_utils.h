/**
 * @file
 * @brief �����,���������غ���
 * @version
 * @remarks
 * @date 2014-05-06
 * @bug
 */


#ifndef _RAND_UTILS_H_
#define _RAND_UTILS_H_

namespace sr
{
    ///> ����,Open������, Close������
    enum Interval {OpenClose, CloseOpen, OpenOpen, CloseClose};

    /**
     * @brief ����ָ����Χ���������
     * @param[in] min ���ɵ���Сֵ
     * @param[in] max ���ɵ����ֵ
     * @param[in] ��������
     * @return ����ָ����Χ�������
     * @attention ����֮ǰ,�����ʹ��srand����
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
     * @brief ����������(0,1)��С��
     * @return ����һ��������(0,1)�ڵ����С��
     */
    double RandDecimal()
    {
        return (rand() / double(RAND_MAX));
    }

    /**
     * @brief ��������ַ���
     * @param[in] arrRange ָ�����ɵ��ַ����и����ַ��ķ�Χ
     * @param[in] nLen ָ�����ɵ�����ַ�������
     * @param[out] sOut ���ڴ洢���ɵ�����ַ���
     * @note ��arrRange="ABCDEF", �����ɵ�����ַ��������⼸����ĸ��������.
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
