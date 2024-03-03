#pragma once

namespace analyzer
{

class client
{
public:
  static auto create() -> client*;
  static auto destroy(client* client) -> void;

private:
  client();
  ~client();
};

}  // namespace analyzer
