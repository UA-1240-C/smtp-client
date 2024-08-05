#include "SendUtilities.h"
#include "File.h"

namespace ISXUtilities
{

    bool AsyncSendFile(const string& file_path, ISXSmartSocket::SmartSocket& smart_socket, asio::yield_context& yield)
    {
        std::ifstream file;
        std::vector<char> buffer(CHUNK_SIZE);

        if (!OpenFile(file_path, file))
            return false;

        while (!file.eof())
        {
            file.read(buffer.data(), buffer.size());
            std::string encoded_buffer = ISXBase64::Base64Encode(std::string(buffer.begin(), buffer.begin() + file.gcount())) + "\r\n";
            smart_socket.AsyncWriteCoroutine(encoded_buffer, yield);
        };

        return true;
    };

    bool AsyncSendAttachments(const ISXMM::MailMessage& message, ISXSmartSocket::SmartSocket& smart_socket, asio::yield_context& yield)
    {
        for (auto& attachment : message.attachments)
        {
            smart_socket.AsyncWriteCoroutine("--" + ISXMM::MailMessageFormatter::boundary + "\r\n", yield);
            smart_socket.AsyncWriteCoroutine(ISXMM::MailMessageFormatter::MailAttachmentHeaders(attachment), yield);
            AsyncSendFile(attachment.get_path(), smart_socket, yield);
        };
        smart_socket.AsyncWriteCoroutine("--" + ISXMM::MailMessageFormatter::boundary + "--\r\n", yield);

        return true;
    };

    bool AsyncSendMailHeaders(const ISXMM::MailMessage& message, ISXSmartSocket::SmartSocket& smart_socket, asio::yield_context& yield)
    {
        smart_socket.AsyncWriteCoroutine(ISXMM::MailMessageFormatter::MailHeaders(message), yield);
        return true;
    };

    bool AsyncSendMailBody(const ISXMM::MailMessage& message, ISXSmartSocket::SmartSocket& smart_socket, asio::yield_context& yield)
    {
        smart_socket.AsyncWriteCoroutine(ISXMM::MailMessageFormatter::MailBody(message), yield);
        return true;
    };


}