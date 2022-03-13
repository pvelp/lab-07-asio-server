// Copyright 2021 Your Name <your_email>

#include <stdexcept>

#include <header.hpp>

ip::tcp::socket& talk_to_client::sock(){
    return _sock;
}

[[nodiscard]]std::string talk_to_client::username() const{
    return _username;
}


auto example() -> void {
  throw std::runtime_error("not implemented");
}
