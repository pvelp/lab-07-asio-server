// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_EXAMPLE_HPP_
#define INCLUDE_EXAMPLE_HPP_

#include <iostream>
#include "nlohmann/json.hpp"
#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/bind.hpp>
#include <string>

#define  MAX_MSG_LEN 1024

// декларация глобальных переменных (объявлены в talk_to_client.cpp)

extern boost::asio::io_context ctx;
extern boost::recursive_mutex mutex;

namespace ip = boost::asio::ip;


class talk_to_client{
private:
    ip::tcp::socket _sock;
    std::string _username;
    char _buff[1024];
    bool _changed_cl;
    boost::chrono::time_point<boost::chrono::high_resolution_clock> _last_ping;
public:
    talk_to_client() : _sock(ctx){};
    ip::tcp::socket& sock();
    [[nodiscard]]std::string username() const;
//    void sign_in();
    void stop();
    void read_request();
    void on_clients();
    void on_ping();
    void on_login(const std::string & msg);
    void write(const std::string& msg);
//    void answer_to_client();
    void set_changed_cl();
    [[nodiscard]]bool time_out() const;
    void process_request();
    void answer_to_client();
};

extern std::vector<std::shared_ptr<talk_to_client>> clients;


#endif // INCLUDE_EXAMPLE_HPP_
