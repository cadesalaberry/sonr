#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <tins/tins.h>
#include <iostream>
#include <thread>
#include <set>

#include "sonr.hpp"

using namespace Tins;

relay_server m_relay_server;

void start_ws_server(int threadid) {
    long tid;
    tid = (long) threadid;
    std::cout << "Server running on port: " << 9002 << std::endl;
    
    m_relay_server.run(9002);

    std::cout << "Server exited." << 9002 << std::endl;
    
    pthread_exit(NULL);
}


bool callback(const PDU &pdu) {

    // The packet probably looks like this:
    //
    // EthernetII / IP / UDP / RawPDU
    //
    // So we retrieve the RawPDU layer, and construct a 
    // DNS PDU using its contents.
    DNS dns = pdu.rfind_pdu<RawPDU>().to<DNS>();
    
    // Retrieve the queries and print the domain name:
    for(const auto &query : dns.queries()) {
        // Spotted two types: (1:A) & (28:AAAA)
        if (query.type() == 1) {
            std::string s("{'n':'");
            s += query.dname();
            s += "'}";
            std::cout << s << std::endl;
            m_relay_server.send_message(s);
        }
    }

    return true;
}

int main(int argc, char *argv[]) {

    if(argc != 2) {
        std::cout << "Usage: " << *argv << " <interface>" << std::endl;
        return 1;
    }

    // Takes care of killing the thread on exit:
    std::thread t(start_ws_server, 0);
    t.detach();
    assert(!t.joinable());
    

    // Sniff on the provided interface in promiscuos mode
    Sniffer sniffer(argv[1], Sniffer::PROMISC);
    
    // Only capture udp packets sent to port 53
    sniffer.set_filter("udp and dst port 53");

    // Start the capture
    std::cout << "Sniffer starting..." << std::endl;
    sniffer.sniff_loop(callback);
    
}
