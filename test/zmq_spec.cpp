
#include <string>

#include "gtest/gtest.h"

#include "zmq_pub_sub.h"

const std::string kTopicA{"TOPIC_A"};
const std::string kTopicB{"TOPIC_B"};

template <typename T>
void PreparePubSubPair(PublisherT<T> &pub, SubscriberT<T> &sub)
{
  while (!sub.receive())
  {
    pub.publish(1);
  }

  while (sub.receive())
  {
    usleep(1);
  }
}

class FixtureZMQ : public ::testing::Test
{
protected:
  FixtureZMQ()
  {
    PreparePubSubPair(publisher_a, subscriber_a);
    PreparePubSubPair(publisher_b, subscriber_b);
  }

  PublisherT<int> publisher_a{kTopicA};
  SubscriberT<int> subscriber_a{kTopicA};

  PublisherT<int> publisher_b{kTopicB};
  SubscriberT<int> subscriber_b{kTopicB};
};

TEST(ZMQ_publisher, instanciate_with_topic)
{
  PublisherT<int> publisher{""};

  EXPECT_TRUE(true);
}

TEST(ZMQ_publisher, publish)
{
  PublisherT<int> publisher{""};

  EXPECT_TRUE(publisher.publish(0));
}

TEST(ZMQ_subscriber, instanciate_with_topic)
{
  SubscriberT<int> subscriber{""};

  EXPECT_TRUE(true);
}

TEST(ZMQ_subscriber, receive)
{
  SubscriberT<int> subscriber{""};

  EXPECT_NO_THROW(subscriber.receive());
}

template <typename T>
int PublishN(PublisherT<T> &publisher, T value, int n)
{
  int num_of_pubs{};

  for (int i{}; i < n; ++i)
  {
    if (publisher.publish(value))
    {
      ++num_of_pubs;
    }
  }

  return num_of_pubs;
}

template <typename T>
int Receive(SubscriberT<T> &sub)
{
  int result{};

  while (!sub.receive())
  {
  }
  ++result;

  while (sub.receive())
  {
    //usleep(10);
    ++result;
  }

  return result;
}

TEST_F(FixtureZMQ, send_and_receive)
{
  const int source_value{10};
  const int num_of_iter{1};

  int num_of_pubs = PublishN(publisher_a, source_value, num_of_iter);

  int num_of_subs = Receive(subscriber_a);

  EXPECT_EQ(num_of_iter, num_of_pubs);
  EXPECT_EQ(num_of_iter, num_of_subs);
}

TEST_F(FixtureZMQ, no_comm_with_different_topics)
{
  const int source_value{10};
  const int num_of_iter{1};

  int num_of_pubs = PublishN(publisher_a, source_value, num_of_iter);

  int num_of_subs = Receive(subscriber_a);

  EXPECT_EQ(num_of_iter, num_of_pubs);
  EXPECT_EQ(num_of_iter, num_of_subs);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}