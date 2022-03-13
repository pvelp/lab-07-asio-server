//
// Created by pvelp on 3/14/22.
//

#ifndef LAB07_ASIO_SERVER_LOGGING_HPP
#define LAB07_ASIO_SERVER_LOGGING_HPP
#include <nlohmann/json.hpp>
#include <iostream>
#include <boost/log/exceptions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
//#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/core.hpp>

namespace sinks = boost::log::sinks;
namespace logs = boost::log;
namespace keywords = boost::log::keywords;

void set_logs(size_t val);
void init(size_t size);

#endif  // LAB07_ASIO_SERVER_LOGGING_HPP


