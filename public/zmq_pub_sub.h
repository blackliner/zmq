#pragma once

#include <string>
#include <zmq.hpp>

template <typename MessageT>
class PublisherT
{
public:
    PublisherT(std::string topic) : m_topic(topic) {}

    void bind()
    {
        m_socket.bind(zmq_type + m_topic);
    }

    void publish(const MessageT &value)
    {
        zmq::message_t message{sizeof(MessageT)};
        memcpy(message.data(), &value, sizeof(MessageT));
        m_socket.send(message);
    }

private:
    zmq::context_t m_context{};
    zmq::socket_t m_socket{m_context, zmq::socket_type::pub};

    const std::string zmq_type{"inproc://"};
    const std::string m_topic;
};

template <typename MessageT>
class SubscriberT
{
public:
    SubscriberT(std::string topic) : m_topic(topic) {}

    void connect()
    {
        m_socket.connect(zmq_type + m_topic);
        // set the socket options such that we receive all messages. we can set
        // filters here. this "filter" ("" and 0) subscribes to all messages.
        // m_socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    }

private:
    zmq::context_t m_context{};
    zmq::socket_t m_socket{m_context, zmq::socket_type::sub};

    const std::string zmq_type{"inproc://"};
    const std::string m_topic;
};