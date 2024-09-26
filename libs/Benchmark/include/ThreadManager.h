#pragma once

#include <vector>
#include <thread>
#include <chrono>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "SMTPSampler.h"
#include "Controller.h"

class ThreadManager {
public:
    ThreadManager(uint16_t num_threads, std::chrono::duration<double> ramp_up_period,
                  uint16_t loop_count, Controller& controller)
        : m_num_threads(num_threads), m_ramp_up_period(ramp_up_period),
          m_loop_count(loop_count), m_controller(controller) {}

    void Start() {

        // Initialize the io_context and ssl_context
        boost::asio::io_context io_context;
        boost::asio::ssl::context ssl_context(boost::asio::ssl::context::tls_client);
        ssl_context.set_verify_mode(boost::asio::ssl::verify_none);

        std::thread worker([&io_context]() {
            boost::asio::io_context::work work(io_context);
            io_context.run();
        });


        auto delay = m_ramp_up_period / m_num_threads;

        for (uint16_t i = 0; i < m_loop_count; i++) 
        {
            for (uint16_t i = 0; i < m_num_threads; ++i) 
            {
                m_threads.emplace_back(&ThreadManager::run, this, i, io_context, ssl_context);
                std::this_thread::sleep_for(delay);
            }

            for (auto& thread : m_threads) {
                thread.join();
            }
        }

        if (!io_context.stopped())
            io_context.stop();

        if (worker.joinable())
            worker.join();
    }

private:
    void run(uint32_t thread_id, boost::asio::io_context& io_context,
                boost::asio::ssl::context& ssl_context) {
        
        SMTPSampler sampler(thread_id, io_context, ssl_context);

        
        // Loop or run based on controller logic
        // for (int i = 0; i < num_emails_per_thread_; ++i) {
        //     sampler.sendEmail();
        //     m_controller.checkTestLogic(); // Allow controller to intervene if needed
        // }
    }

    uint16_t m_num_threads;
    std::chrono::duration<double> m_ramp_up_period;
    uint16_t m_loop_count;
    std::vector<std::thread> m_threads;
    Controller& m_controller;
};
