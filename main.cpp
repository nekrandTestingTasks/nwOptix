#include <boost/program_options.hpp>

#include "ServerHandler.h"

namespace po = boost::program_options;

void parseCommandLineOptions(int ac, char *av[], int &port, int &timeout) {
  const int kTimeoutDefault = 60;
  const int kPortDefault = 0;

  po::options_description desc("Allowed options");
  desc.add_options()("-d", po::value<int>(),
                     "timeout in sec")("-p", po::value<int>(), "port");

  po::variables_map vm;
  po::store(po::parse_command_line(ac, av, desc), vm);
  po::notify(vm);

  if (vm.count("-d")) {
    timeout = vm["-d"].as<int>();
  } else {
    timeout = kTimeoutDefault;
  }

  if (vm.count("-p")) {
    port = vm["-p"].as<int>();
  } else {
    port = kPortDefault;
  }
}

int main(int ac, char *av[]) {
  int port;
  int timeout;

  try {
    parseCommandLineOptions(ac, av, port, timeout);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 0;
  }

  try {
    boost::asio::io_service io_service;
    Server server(io_service, port, timeout);
    io_service.run();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}