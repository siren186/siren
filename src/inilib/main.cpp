#include "inilib.h"

int main(int argc, char **argv)
{
    ///> ÐÂ½¨xml
    INI::registry reg("c:\\1.ini");

    reg["section1"]["user"] = "siren1";
    reg["section1"]["email"] = "siren186@163.com";
    reg["section2"]["user"] = "siren2";
    reg["section2"]["date"] = "2014-05-12";

    reg.file_write();

    return 0;
}