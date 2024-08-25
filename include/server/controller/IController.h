#pragma once

#include <memory>

namespace Controller {

class IController {
public:
  virtual bool handleRequest(TcpSocket socket, TCPRequest &request,
                             std::vector<unsigned char> &payload) = 0;
  virtual std::string getEndpoint() = 0;
  virtual ~IController() = default;
};
}; // namespace Controller