#include <gtest/gtest.h>
#include "MailAttachment.h"
#include <filesystem>

TEST(MailAttachmentTest, GetPath) {
    std::filesystem::path test_path = "/path/to/attachment.txt";
    ISXSC::MailAttachment attachment(test_path);
    
    EXPECT_EQ(attachment.get_path(), test_path);
}

TEST(MailAttachmentTest, GetName) {
    std::filesystem::path test_path = "/path/to/attachment.txt";
    ISXSC::MailAttachment attachment(test_path);
    
    EXPECT_EQ(attachment.get_name(), "attachment.txt");
}

TEST(MailAttachmentTest, GetNameNoExtension) {
    std::filesystem::path test_path = "/path/to/attachment";
    ISXSC::MailAttachment attachment(test_path);
    
    EXPECT_EQ(attachment.get_name(), "attachment");
}

TEST(MailAttachmentTest, GetNameWithSpecialCharacters) {
    std::filesystem::path test_path = "/path/to/@ttachment!.txt";
    ISXSC::MailAttachment attachment(test_path);
    
    EXPECT_EQ(attachment.get_name(), "@ttachment!.txt");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}