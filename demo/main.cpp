#include <header.hpp>

[[noreturn]]void accept_thread(){
    ip::tcp::acceptor acceptor{ctx, ip::tcp::endpoint{ip::tcp::v4(), 8001}};
    while (true){
        auto client = std::make_shared<talk_to_client>();
        acceptor.accept(client->sock());
        boost::recursive_mutex::scoped_lock {mutex};
        clients.push_back(client);
    }
}



int main() {
  example();
}