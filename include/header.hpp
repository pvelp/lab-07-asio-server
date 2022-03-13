// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_EXAMPLE_HPP_
#define INCLUDE_EXAMPLE_HPP_

#include <iostream>
#include "nlohmann/json.hpp"
#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/exceptions.hpp>
#include <string>

boost::asio::io_context ctx;
boost::recursive_mutex mutex;

namespace ip = boost::asio::ip;


class talk_to_client{
private:
    ip::tcp::socket _sock;
    std::string _username;
    boost::chrono::time_point<boost::chrono::high_resolution_clock> last_ping;
public:
    talk_to_client() : _sock(ctx){};
    ip::tcp::socket& sock();
    [[nodiscard]]std::string username() const;
    // void sign_in();
    // void stop();
    // void read_request();
    //on_clients();
    //on_ping();
    //

};

std::vector<std::shared_ptr<talk_to_client>> clients;



auto example() -> void;

#endif // INCLUDE_EXAMPLE_HPP_
