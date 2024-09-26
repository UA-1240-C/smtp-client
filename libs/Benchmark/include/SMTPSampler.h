#pragma once

#include <chrono>
#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "SmartSocket.h"
#include "SmtpClient.h"
#include "MailMessage.h"
#include "MailMessageBuilder.h"

#include "Listener.h"
#include "Sampler.h"
#include "Utils.h"

class SMTPSampler final : public Sampler 
{
public:
    SMTPSampler() 
    : m_io_context(), m_ssl_context(boost::asio::ssl::context::tls_client)
    {}

    ~SMTPSampler() override
    {
        if (!m_io_context.stopped())
            m_io_context.stop();

        if (m_worker.joinable())
            m_worker.join();
    };

    bool Setup() override 
    {
        try
        {
            m_ssl_context.set_verify_mode(boost::asio::ssl::verify_none);
            m_worker = std::thread(
                [&m_io_context = this->m_io_context]() {
                    boost::asio::io_context::work work(m_io_context);
                    m_io_context.run();
            });
            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    void ExecuteInstance(uint32_t m_thread_id) override 
    {
        Timer timer_global;
        
        std::unique_ptr<ISXSC::SmtpClient> smtp_client = std::make_unique<ISXSC::SmtpClient>(m_io_context, m_ssl_context);
        bool is_successful = true;

        TimerResults timer_results;

        try
        {   
            Timer timer_ehlo;
            smtp_client->AsyncConnect("127.0.0.1", 2525).get();
            timer_results.ehlo_duration = timer_ehlo.GetDuration();

            Timer timer_auth;
            smtp_client->AsyncAuthenticate("user@gmail.com", "password").get();
            timer_results.auth_duration = timer_auth.GetDuration();

            std::string subject = "C++ benchmark subject " + CurrentTimeToString();

            ISXMM::MailMessageBuilder mail_builder;
            mail_builder.set_from("user@gmail.com")
                .add_to("user@gmail.com")
                .set_subject(subject)
                .set_body("C++ benchmark body");

            Timer timer_send_mail;
            smtp_client->AsyncSendMail(mail_builder.Build()).get();
            timer_results.send_mail_duration = timer_send_mail.GetDuration();

            delete smtp_client.release();
        } catch (const std::exception& e)
        {
            std::cout << "Exception caught\n";
            is_successful = false;
        }
        delete smtp_client.release();

        Listener::getInstance().logResult(m_thread_id, timer_global.GetDuration(), timer_results, is_successful);  // true = success
    }

private:
    boost::asio::io_context m_io_context;
    boost::asio::ssl::context m_ssl_context;
    std::thread m_worker;


};
