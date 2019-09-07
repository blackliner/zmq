
#include <string>

#include "gtest/gtest.h"

#include "zmq_pub_sub.h"

const std::string topic{"TEST"};

TEST(ZMQ_publisher, instanciate_with_topic)
{
  PublisherT<int> publisher{topic};

  EXPECT_TRUE(true);
}

TEST(ZMQ_publisher, bind)
{
  PublisherT<int> publisher{topic};

  EXPECT_NO_THROW(publisher.bind(););
}

TEST(ZMQ_publisher, publish)
{
  PublisherT<int> publisher{topic};

  EXPECT_NO_THROW(publisher.bind(););

  EXPECT_NO_THROW(publisher.publish(0););
}

TEST(ZMQ_subscriber, instanciate_with_topic)
{
  SubscriberT<int> subscriber{topic};

  EXPECT_TRUE(true);
}

TEST(ZMQ_subscriber, connect)
{
  SubscriberT<int> subscriber{topic};

  EXPECT_NO_THROW(subscriber.connect());
}

TEST(ZMQ_subscriber, receive)
{
  SubscriberT<int> subscriber{topic};

  EXPECT_NO_THROW(subscriber.connect());

  EXPECT_NO_THROW(subscriber.connect());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}