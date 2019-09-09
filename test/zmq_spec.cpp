
#include <string>

#include "gtest/gtest.h"

#include "zmq_pub_sub.h"

class FixtureZMQ : public ::testing::Test
{
protected:
};

const std::string topic{"TEST"};

TEST(ZMQ_publisher, instanciate_with_topic)
{
  PublisherT<int> publisher{topic};

  EXPECT_TRUE(true);
}

TEST(ZMQ_publisher, publish)
{
  PublisherT<int> publisher{topic};

  EXPECT_TRUE(publisher.publish(0));
}

TEST(ZMQ_subscriber, instanciate_with_topic)
{
  SubscriberT<int> subscriber{topic};

  EXPECT_TRUE(true);
}

TEST(ZMQ_subscriber, receive)
{
  SubscriberT<int> subscriber{topic};

  EXPECT_NO_THROW(subscriber.receive());
}

TEST(ZMQ, send_and_receive)
{
  PublisherT<int> publisher{topic};
  SubscriberT<int> subscriber{topic};

  const int source_value{10};
  const int num_of_iter{10000};
  int num_of_pubs{};

  usleep(10);

  for (int i{}; i < num_of_iter; ++i)
  {
    if (publisher.publish(source_value))
    {
      ++num_of_pubs;
    }
  }

  //usleep(100000);

  int num_of_subs{};
  int num_of_correct_subs{};
  int receive_count{num_of_iter};
  while (receive_count > 0)
  {
    auto value = subscriber.receive();

    if (value)
    {
      ++num_of_subs;
      if (*value == source_value)
      {
        ++num_of_correct_subs;
      }
    }
    else
    {
      --receive_count;
    }
  }

  EXPECT_EQ(num_of_iter, num_of_pubs);
  EXPECT_EQ(num_of_iter, num_of_subs);
  EXPECT_EQ(num_of_iter, num_of_correct_subs);
}

TEST(ZMQ, no_comm_with_different_topics)
{
  EXPECT_FALSE(true);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}