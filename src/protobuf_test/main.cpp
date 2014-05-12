///> 创建.proto文件,用protoc.exe生成对应的.h和.cpp文件,例如:
///> protoc  -I=.\   --cpp_out=.\   sr.ProtoTest.proto

#include <string>
#include "sr.ProtoTest.pb.h"

int main(int argc, char **argv)
{
    sr::ProtoTest info1;
    info1.set_id(32);
    info1.set_name("siren", 20);
    info1.set_email("siren186@163.com", 50);

    ///> 序列化到string
    std::string strBuf;
    info1.SerializeToString(&strBuf);

    ///> 反序列化
    sr::ProtoTest info2;
    info2.ParseFromString(strBuf);

    return 0;
}