#include <iostream>
#include "MailMessageBuilder.h"
#include "MailMessageFormatter.h"

int main()
{
    ISXMM::MailMessageBuilder builder;
    auto message  = builder.SetFrom("romanbychko84@gmail.com", "Roman Buchko")
        .AddTo("irabychko84@GMAIL.COM", "Buchko Ira")
        .AddTo("123@gmail.com", "123")
        .SetSubject("Testing...")
        .SetBody("Hello, World. This is a test message. Regards, Roman Buchko.")
        .AddAttachment("123.txt")
        .Build();
    
    std::cout<< ISXMM::MailMessageFormatter::MailHeaders(message);
    std::cout<< ISXMM::MailMessageFormatter::MailBody(message);
    std::cout<< ISXMM::MailMessageFormatter::MailAttachmentHeaders(message.attachments.at(0));
    // file base64 goes here
    std::cout << ISXMM::MailMessageFormatter::boundary;
    // std::cout<< ISXSC::MailMessageFormatter::MailAttachmentHeaders(message.attachments.at(0));
    // more files ...
    // std::cout << "--" + ISXSC::MailMessageFormatter::boundary;
    // .
}
