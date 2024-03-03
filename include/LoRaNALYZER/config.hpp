#pragma once

#include <string>

#include <spdlog/spdlog.h>

#include "ism_band.hpp"

namespace analyzer
{

class config
{
public:
  static auto create(ism_band band) -> config*;
  static auto get(config& config, std::string parameter) -> std::string;
  static auto destroy(config& config) -> void;

private:
  config(std::uint64_t frq_start, std::uint64_t frq_end);
  ~config();

  std::uint64_t m_start_frq;
  std::uint64_t m_end_frq;
};

}  // namespace analyzer
