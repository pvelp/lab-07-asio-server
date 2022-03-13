#include <header.hpp>
#include "logging.hpp"

[[noreturn]]void accept_thread(){
    ip::tcp::acceptor acceptor{ctx, ip::tcp::endpoint{ip::tcp::v4(), 8001}};
    while (true){
        auto client = std::make_shared<talk_to_client>();
        acceptor.accept(client->sock());
//        boost::recursive_mutex::scoped_lock {mutex};
        boost::lock_guard<boost::recursive_mutex>lock(mutex);
        clients.push_back(client);
        BOOST_LOG_TRIVIAL(trace) << "Client has been added" << std::endl;
    }
}

[[noreturn]]void handle_clients_thread(){
  while (true){
    boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
    boost::lock_guard<boost::recursive_mutex>lock(mutex);
    for (auto& client : clients){
      client->answer_to_client();
      clients.erase(std::remove_if(clients.begin(), clients.end(),
                                   boost::bind(&talk_to_client::time_out, _1))
                        ,clients.end());
    }
  }
}


int main() {
  init(4);
  boost::thread thread1(accept_thread);
  boost::thread thread2(handle_clients_thread);
  thread1.join();
  thread2.join();
  return 0;
}