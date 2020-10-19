#include <atomic>
#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

#include <gtest/gtest.h>
#include <zmq.hpp>

using namespace std::chrono_literals;

static int get_monitor_event( void* monitor, int* value, char** address )
{
  // First frame in message contains event number and value
  zmq_msg_t msg;
  zmq_msg_init( &msg );
  if ( zmq_msg_recv( &msg, monitor, 0 ) == -1 )
    return -1; // Interrupted, presumably
  assert( zmq_msg_more( &msg ) );

  uint8_t* data = (uint8_t*)zmq_msg_data( &msg );
  uint16_t event = *(uint16_t*)( data );
  if ( value )
    *value = *(uint32_t*)( data + 2 );

  // Second frame in message contains event address
  zmq_msg_init( &msg );
  if ( zmq_msg_recv( &msg, monitor, 0 ) == -1 )
    return -1; // Interrupted, presumably
  assert( !zmq_msg_more( &msg ) );

  if ( address )
  {
    uint8_t* data = (uint8_t*)zmq_msg_data( &msg );
    size_t size = zmq_msg_size( &msg );
    *address = (char*)malloc( size + 1 );
    memcpy( *address, data, size );
    ( *address )[size] = 0;
  }
  return event;
}

void close_blocking( zmq::socket_t& socket, zmq::context_t& context )
{
  int rc = zmq_socket_monitor( socket.handle(), "inproc://monitor", ZMQ_EVENT_ALL );
  assert( rc == 0 );

  zmq::socket_t monitor{ context, zmq::socket_type::pair };
  rc = zmq_connect( monitor.handle(), "inproc://monitor" );
  assert( rc == 0 );

  socket.close();

  bool loop{ true };
  while ( loop )
  {
    const int event = get_monitor_event( monitor.handle(), NULL, NULL );
    std::cout << event << " == ";
    switch ( event )
    {
    case -1:
      std::cout << "wating..." << std::endl;
      break;
    case ZMQ_EVENT_CLOSED:
      std::cout << "ZMQ_EVENT_CLOSED" << std::endl;
      loop = false;
      break;
    default:
      std::cout << "UNKNOWN" << std::endl;
    }
  }
}

TEST( ZMQ_blocking_close, first_test )
{
  zmq::context_t m_context{};

  {
    zmq::socket_t m_socket_1{ m_context, zmq::socket_type::pub };
    m_socket_1.bind( "tcp://127.0.0.1:5932" );

    const bool FAIL_TEST{ false };

    if ( FAIL_TEST )
    {
      m_socket_1.close();
    }
    else
    {
      close_blocking( m_socket_1, m_context );
    }
  }

  {

    zmq::socket_t m_socket_2{ m_context, zmq::socket_type::sub };
    m_socket_2.bind( "tcp://127.0.0.1:5932" );
  }
}

int main( int argc, char** argv )
{
  ::testing::InitGoogleTest( &argc, argv );

  return RUN_ALL_TESTS();
}