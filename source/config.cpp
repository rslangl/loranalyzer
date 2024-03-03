#include <LoRaNALYZER/config.hpp>
#include <LoRaNALYZER/ism_band.hpp>

using analyzer::config;

auto config::create(ism_band band) -> config*
{
  config* cfg = nullptr;

  switch (band) {
    case ism_band::eur: {
      cfg = new config(862e6, 875e6);
      break;
    }
    case ism_band::amr: {
      cfg = new config(875e6, 960e6);
      break;
    }
    default:
      spdlog::error("Band not found or specified");
  }
  return cfg;
}

auto config::get(config& config, std::string parameter) -> std::string
{
  /* std::string cfg_val; */
  /* for (const auto& [k, v] : config->m_config) { */
  /*   if (k == parameter) { */
  /*     cfg_val = std::string {v}; */
  /*   } */
  /* } */
  /* return cfg_val; */
}

auto config::destroy(config& config) -> void
{
  config.~config();
}

config::config(std::uint64_t frq_start, std::uint64_t frq_end)
    : m_start_frq(frq_start)
    , m_end_frq(frq_end)
{
}
