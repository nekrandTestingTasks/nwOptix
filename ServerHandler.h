#include <ctime>
#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>

#include "Counter.h"

using boost::asio::ip::tcp;

class Connection : public boost::enable_shared_from_this<Connection> {
public:
  using pointer = boost::shared_ptr<Connection>;

  static pointer create(boost::asio::io_service &io_service) {
    return pointer(new Connection(io_service));
  }

  tcp::socket &socket() { return socket_; }

  void start(Counter &counter);

private:
  Connection(boost::asio::io_service &io_service) : socket_(io_service) {}

  void handle_write(const boost::system::error_code & /*error*/,
                    size_t /*bytes_transferred*/) {}

  void handle_read(Counter &counter, const boost::system::error_code &error,
                   size_t bytes_transferred);

  tcp::socket socket_;
  boost::asio::streambuf message_;
};

class Server {
public:
  Server(boost::asio::io_service &io_service, int port, int duration)
      : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
        counter(duration) {
    start_accept();
  }

private:
  void start_accept() {
    Connection::pointer new_connection =
        Connection::create(acceptor_.get_io_service());

    acceptor_.async_accept(new_connection->socket(),
                           boost::bind(&Server::handle_accept, this,
                                       new_connection,
                                       boost::asio::placeholders::error));
  }

  void handle_accept(Connection::pointer new_connection,
                     const boost::system::error_code &error) {
    if (!error) {
      new_connection->start(counter);
      start_accept();
    }
  }

  tcp::acceptor acceptor_;
  Counter counter;
};