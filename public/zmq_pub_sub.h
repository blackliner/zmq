#pragma once

#include <experimental/optional>
#include <string>

#include <zmq.hpp>

//const std::string zmq_type{"inproc://abc"}; // TODO only works with the exact same context
const std::string zmq_type{"ipc:///tmp/exchange"};
constexpr bool pub_binds{true};

template <typename MessageT>
class PublisherT
{
public:
    PublisherT(std::string topic) : m_topic(topic)
    {
        if (pub_binds)
        {
            m_socket.bind(zmq_type);
        }
        else
        {
            m_socket.connect(zmq_type);
        }
    }

    bool publish(const MessageT &value)
    {
        zmq::message_t message{sizeof(MessageT)};
        memcpy(message.data(), &value, sizeof(MessageT));
        auto send_result = m_socket.send(message, zmq::send_flags::dontwait);

        return send_result.has_value();
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
    SubscriberT(std::string topic) : m_topic(topic)
    {
        m_socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
        // m_socket.setsockopt(ZMQ_RCVTIMEO, 10);
        //m_socket.connect("tcp://127.0.0.1:5932");
        //m_socket.connect(zmq_type + m_topic);
        if (!pub_binds)
        {
            m_socket.bind(zmq_type);
        }
        else
        {
            m_socket.connect(zmq_type);
        }
    }

    std::experimental::optional<MessageT> receive()
    {
        zmq::message_t message;

        //auto recv_result = m_socket.recv(message, wait ? zmq::recv_flags::none : zmq::recv_flags::dontwait);
        auto recv_result = m_socket.recv(message, zmq::recv_flags::dontwait);

        if (recv_result)
        {
            MessageT output;

            memcpy(&output, message.data(), message.size());

            return std::experimental::optional<MessageT>{output};
        }
        else
        {
            return {};
        }
    }

private:
    zmq::context_t m_context{};
    zmq::socket_t m_socket{m_context, zmq::socket_type::sub};

    const std::string m_topic;
};