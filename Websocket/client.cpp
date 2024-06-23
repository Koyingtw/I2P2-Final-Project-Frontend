#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <Websocket/client.hpp>
#include <sstream>

typedef websocketpp::client<websocketpp::config::asio_client> client;

WebSocketClient::WebSocketClient() : running(true) {
    // 初始化 Asio
    m_client.init_asio();
    m_client.set_max_message_size(65536);

    // 設置消息處理器
    m_client.set_message_handler(bind(&WebSocketClient::on_message, this, std::placeholders::_1, std::placeholders::_2));
}

void WebSocketClient::run(const std::string& uri) {
    websocketpp::lib::error_code ec;

    // 創建連接
    client::connection_ptr con = m_client.get_connection(uri, ec);
    if (ec) {
        std::cout << "Could not create connection because: " << ec.message() << std::endl;
        return;
    }

    // 設置開放處理器
    con->set_open_handler([this](websocketpp::connection_hdl hdl) {
        m_hdl = hdl;
        std::cout << "Connection opened" << std::endl;
        // 發送初始消息
        send_message("Hello, server!");
    });

    // 設置關閉處理器
    con->set_close_handler([this](websocketpp::connection_hdl hdl) {
        std::cout << "Connection closed" << std::endl;
        running = false;
    });

    // 設置失敗處理器
    con->set_fail_handler([this](websocketpp::connection_hdl hdl) {
        std::cout << "Connection failed" << std::endl;
        running = false;
    });

    // 設置連接
    m_client.connect(con);

    // 在另一個線程中運行 Asio 事件循環
    std::thread asio_thread([this]() {
        m_client.run();
    });

    // 等待 Asio 事件循環結束
    asio_thread.join();
}

void WebSocketClient::send_message(const std::string message) {
    std::cout << "Sending message: " << message << std::endl;
    try {
        websocketpp::lib::error_code ec;
        m_client.send(m_hdl, message, websocketpp::frame::opcode::text, ec);
        if (ec) {
            std::cerr << "Error sending message: " << ec.message() << std::endl;
        }
    } catch (const websocketpp::exception& e) {
        std::cerr << "Exception caught while sending message: " << e.what() << std::endl;
    }
}

void WebSocketClient::on_message(websocketpp::connection_hdl hdl, client::message_ptr msg) {
    std::string message = msg->get_payload();
    std::cout << "Received message: " << message << std::endl;
}