#pragma once

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "Sockets/TcpSocket.h"
#include <memory>
#include <vector>

namespace Controller {

class IController {
public:
  virtual bool handleRequest(TcpSocket socket, rapidjson::Document &request,
                             rapidjson::Document &payload) = 0;
  virtual ~IController() = default;
};
}; // namespace Controller