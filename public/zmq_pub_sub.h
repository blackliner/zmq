#pragma once

#include <string>
#include <zmq.hpp>

//const std::string zmq_type{"inproc://abc"}; // TODO only works with the exact same context
const std::string zmq_type{"ipc:///tmp/exchange"};

template <typename MessageT>
class PublisherT
{
public:
    PublisherT(std::string topic) : m_topic(topic) {}

    void bind()
    {
        //m_socket.bind("tcp://127.0.0.1:5932");
        //m_socket.bind(zmq_type + m_topic);
        m_socket.bind(zmq_type);
    }

    bool publish(const MessageT &value)
    {
        zmq::message_t message{sizeof(MessageT)};
        memcpy(message.data(), &value, sizeof(MessageT));
        auto send_result = m_socket.send(message, zmq::send_flags::dontwait);

        if (send_result)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

private:
    zmq::context_t m_context{};
    zmq::socket_t m_socket{m_context, zmq::socket_type::pub};

    const std::string m_topic;
};

template <typename MessageT>
class SubscriberT
{
public:
    SubscriberT(std::string topic) : m_topic(topic) {}

    void connect()
    {
        m_socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
        // m_socket.setsockopt(ZMQ_RCVTIMEO, 10);
        //m_socket.connect("tcp://127.0.0.1:5932");
        //m_socket.connect(zmq_type + m_topic);
        m_socket.connect(zmq_type);
    }

    MessageT receive(bool wait = false)
    {
        MessageT output;

        zmq::message_t message;
        if (wait)
        {
            auto receive_result = m_socket.recv(message);
        }
        else
        {
            auto receive_result = m_socket.recv(message, zmq::recv_flags::dontwait);
        }

        memcpy(&output, message.data(), message.size());

        return output;
    }

private:
    zmq::context_t m_context{};
    zmq::socket_t m_socket{m_context, zmq::socket_type::sub};

    const std::string m_topic;
};