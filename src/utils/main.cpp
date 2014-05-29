#include "gtest\gtest.h"
#include "file_utils.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(FileUtils,lnk)
{
    EXPECT_TRUE(sr::CreateLnkFile(L"c:\\1.lnk", L"c:\\2.exe") == TRUE);
    TCHAR szDstPath[MAX_PATH + 1];
    EXPECT_TRUE(sr::GetPathFromLnkFile(L"c:\\1.lnk", szDstPath, MAX_PATH) == TRUE);
    EXPECT_TRUE(0== _wcsicmp(szDstPath, L"c:\\2.exe"));
}

TEST(FileUtils,folder)
{
    EXPECT_TRUE(sr::DeleteFolder(L"c:\\siren test") == TRUE);
    EXPECT_TRUE(sr::CopyFolder(L"c:\\1", L"c:\\2") == TRUE);
}