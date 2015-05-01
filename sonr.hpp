using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef websocketpp::server<websocketpp::config::asio> ws_server;

// pull out the type of messages sent by our config
typedef ws_server::message_ptr message_ptr;


class relay_server {
public:
    relay_server() {
        m_server.init_asio();
        
        std::cout << "Binding functions..." << std::endl;

        m_server.set_open_handler(bind(&relay_server::on_open,this,::_1));
        m_server.set_close_handler(bind(&relay_server::on_close,this,::_1));
        // m_server.set_message_handler(bind(&relay_server::on_message,this,::_1,::_2));
    }
    
    void on_open(connection_hdl hdl) {
        m_connections.insert(hdl);
    }
    
    void on_close(connection_hdl hdl) {
        m_connections.erase(hdl);
    }
    
    void on_message(connection_hdl hdl, ws_server::message_ptr msg) {
        for (auto it : m_connections) {
            m_server.send(it, msg);
        }
    }

    void send_message(std::string s) {
        
        for (auto it : m_connections) {
            m_server.send(
            	it,
            	s,
            	websocketpp::frame::opcode::text,
            	ec
            );

            if (ec) {
            	std::cout << "Error sending the message:" << s << std::endl;
            }
            
        }
    }

    void run(uint16_t port) {
        m_server.listen(port);
        m_server.start_accept();
        m_server.run();
    }
    
private:
    typedef std::set<connection_hdl,std::owner_less<connection_hdl>> con_list;

    ws_server m_server;
    con_list m_connections;
	websocketpp::lib::error_code ec;
};