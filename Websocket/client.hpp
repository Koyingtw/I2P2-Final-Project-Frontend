#pragma once
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <iostream>
#include <string>
#include <thread>
#include <atomic>

typedef websocketpp::client<websocketpp::config::asio_client> client;

class WebSocketClient {
public:
    WebSocketClient();

    void run(const std::string& uri);
    void send_message(const std::string message);
    std::atomic<bool> running;
    client m_client;

private:

    void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg);

    websocketpp::connection_hdl m_hdl;
};
