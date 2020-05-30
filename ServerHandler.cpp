#include "ServerHandler.h"

bool checkInput(const std::string &str) {
  if (str.size() < 3)
    return false;
  int start_pos = 0;
  if (str[0] == '-')
    start_pos = 1;

  return std::all_of(str.begin() + start_pos, str.end() - 2, ::isdigit);
}

void Connection::handle_read(std::shared_ptr<Counter> &counter,
                             const boost::system::error_code &error,
                             size_t bytes_transferred) {

  std::cerr << "Handle Read of connection\n";

  if (error && error != boost::asio::error::eof) {
    std::cerr << "Error: " << error.message() << "\n";
    return;
  }

  if (error && error == boost::asio::error::eof) {
    return;
  }

  std::string messageP;
  {
    std::stringstream ss;
    ss << &message_;
    ss.flush();
    messageP = ss.str();
  }

  if (!checkInput(messageP)) {
    boost::asio::async_write(
        socket_, boost::asio::buffer("Incorrect input, ignoring it" + messageP),
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
      socket_, message_, "\r\n",
      boost::bind(&Connection::handle_read, shared_from_this(), counter,
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
}