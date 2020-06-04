#include "ServerHandler.h"

bool checkInput(const std::string &str) {

  if (str.empty())
    return false;
  int start_pos = 0;
  if (str[0] == '-')
    start_pos = 1;

  return std::all_of(str.begin() + start_pos, str.end(), ::isdigit);
}

void Connection::handle_read(std::shared_ptr<Counter> &counter,
                             const boost::system::error_code &error,
                             size_t bytes_transferred) {

  if (error && error != boost::asio::error::eof) {
    std::cerr << "Error: " << error.message() << "\n";
    return;
  }

  if (error && error == boost::asio::error::eof) {
    return;
  }

  std::string messageP{buffers_begin(message_.data()),
                       buffers_begin(message_.data()) + bytes_transferred -
                           kDelimeter.size()};
  message_.consume(bytes_transferred);

  if (!checkInput(messageP)) {
    boost::asio::async_write(
        socket_, boost::asio::buffer("Incorrect input, ignoring it"),
        boost::bind(&Connection::start, shared_from_this(), counter));
    return;
  }

  std::string message = counter->count(std::stoi(messageP));
  boost::asio::async_write(
      socket_, boost::asio::buffer(message),
      boost::bind(&Connection::start, shared_from_this(), counter));
}

void Connection::start(std::shared_ptr<Counter> &counter) {

  boost::asio::async_read_until(
      socket_, message_, kDelimeter,
      boost::bind(&Connection::handle_read, shared_from_this(), counter,
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
}