// Copyright 2021 Your Name <your_email>

#include <stdexcept>
#include <header.hpp>

boost::asio::io_context ctx;
boost::recursive_mutex mutex;
std::vector<std::shared_ptr<talk_to_client>> clients;


ip::tcp::socket& talk_to_client::sock(){
    return _sock;
}

std::string talk_to_client::username() const{
    return _username;
}

void talk_to_client::write(const std::string& msg){
  _sock.write_some(boost::asio::buffer(msg));
}

void talk_to_client::set_changed_cl() {
  _changed_cl = true;
}

bool talk_to_client::time_out() const {
  auto now = boost::chrono::high_resolution_clock::now();
  auto duration = boost::chrono::duration_cast<boost::chrono::milliseconds>
      (now - _last_ping);
  return duration.count() > 50000;
}

std::string parse_username(const std::string &msg){
  std::string username = "";
  for (unsigned i = 0; i < msg.size(); ++i){
    if ((msg[i] != ' ') && (msg[i] != ':') && (msg[i] != '='))
      username += msg[i];
  }
  return username;
}

void talk_to_client::stop() {
  boost::system::error_code error;
  _sock.close(error);
}

void talk_to_client::on_login(const std::string & msg) {
  _username = parse_username(msg);
  write("login_ok\n");
  set_changed_cl();
}

void talk_to_client::on_ping() {
  std::string data = _changed_cl ? "client_list_changed\n" : "ping ok\n";
}

void talk_to_client::on_clients() {
  std::string msg;
  boost::lock_guard<boost::recursive_mutex> lock(mutex);
  for (auto& client : clients){
    msg += client->username() + "\n";
  }

  write("clients: " + msg + "\n");
  _changed_cl = false;
}

void talk_to_client::read_request() {
  if (_sock.available()){
    _sock.read_some(boost::asio::buffer(_buff, MAX_MSG_LEN));
  }
}

std::string parse_request(char buff[MAX_MSG_LEN]) {
  unsigned real_size = 0;
  std::string msg = "";
  for (unsigned i = 0; i < MAX_MSG_LEN; ++i) {
    if (buff[i] == '\n') {
      real_size = i;
      break;
    }
  }
  if (real_size) {
    for (unsigned i = 0; i < real_size; ++i) {
      msg += buff[i];
    }
  }
  return msg;
}


void talk_to_client::process_request(){
  _last_ping = boost::chrono::high_resolution_clock::now();
  std::string msg = parse_request(_buff);
  if (!msg.empty()){
    if (msg.find("login") == 0){
      on_login(msg);
    } else if (msg.find("ping")){
      on_ping();
    } else if (msg.find("client_list")){
      on_clients();
    } else{
      std::cerr << "incorrect message" << msg << std::endl;
    }
  }
}


void talk_to_client::answer_to_client(){
  try{
    read_request();
    process_request();
  }
  catch (boost::system::system_error&){
    stop();
  }
  if(time_out()){
    stop();
  }
}