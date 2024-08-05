#pragma once

#include "MailMessageFormatter.h"
#include "SmartSocket.h"
#include "File.h"
#include "Base64.h"

namespace ISXUtilities
{

    static bool AsyncSendFile(const string& file_path, ISXSmartSocket::SmartSocket& smart_socket, asio::yield_context& yield);

    bool AsyncSendAttachments(const ISXMM::MailMessage& message, ISXSmartSocket::SmartSocket& smart_socket, asio::yield_context& yield);

    bool AsyncSendMailHeaders(const ISXMM::MailMessage& message, ISXSmartSocket::SmartSocket& smart_socket, asio::yield_context& yield);

    bool AsyncSendMailBody(const ISXMM::MailMessage& message, ISXSmartSocket::SmartSocket& smart_socket, asio::yield_context& yield);


}