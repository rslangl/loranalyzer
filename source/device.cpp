
#include <LoRaNALYZER/device.hpp>

using analyzer::config;
using analyzer::device;

auto device::create(config& config) -> device*
{
  auto buffer = fmt::memory_buffer();
  fmt::format_to(std::back_inserter(buffer), "Debug information:\n");

  std::vector<std::string> str_list {};

  // SoapySDR::Stream* rx_stream;
  SoapySDR::KwargsList devres = SoapySDR::Device::enumerate();
  SoapySDR::Kwargs::iterator itr;

  // enumerate m_devices
  /* for (const auto& [idx, device] : std::views::enumerate(devres)) { */
  for (int idx = 0; idx < devres.size(); ++idx) {
    fmt::format_to(std::back_inserter(buffer), "Found m_device #{}:\n", idx);

    /* for (const auto& [kv] : device) { */
    for (itr = devres[idx].begin(); itr != devres[idx].end(); ++itr) {
      fmt::format_to(
          /* buffer, "\t{} = {}\n", kv.first.c_str(), kv.second.c_str()); */
          std::back_inserter(buffer),
          "\t{} = {}\n",
          itr->first.c_str(),
          itr->second.c_str());
    }
    spdlog::debug(fmt::to_string(buffer));
  }

  // create m_device instance
  SoapySDR::Kwargs args = devres[0];

  auto* device = new class device(devres[0]);

  if (device == nullptr) {
    spdlog::error("Failed to instantiate device\n");
    return nullptr;
  }
  spdlog::info("Instantiated device\n");

  // tuner settings
  /* auto sample_rate = analyzer::config::get(&config, "sample_rate"); */
  /* auto frq_start = analyzer::config::get(&config, "frq_start");
   * //::frq::start; */
  /* auto frq_end = analyzer::config::get(&config, "frq_end");  //::frq::end; */
  auto frq_start = std::uint64_t {static_cast<uint64_t>(862e6)};
  auto frq_end = std::uint64_t {static_cast<uint64_t>(875e6)};
  auto sample_rate = std::uint64_t {static_cast<uint64_t>(10e6)};

  device->m_device->setSampleRate(
      SOAPY_SDR_RX, 0, sample_rate);  // std::stoull(sample_rate));  // 10e6
  device->m_device->setFrequency(
      SOAPY_SDR_RX, 0, frq_start);  // std::stoull(frq_start));  // 433e6

  spdlog::info(
      "Configured tuner frequency band {} Hz to {} Hz", frq_start, frq_end);

  // setup a stream
  device->m_rx_stream =
      device->m_device->setupStream(SOAPY_SDR_RX, SOAPY_SDR_CF32);

  if (device->m_rx_stream == nullptr) {
    spdlog::error("Failed to setup RX stream\n");
    /* destroy(device); */
    device->~device();
    return nullptr;
  }
  spdlog::info("Initialized RX stream\n");

  device->m_device->activateStream(device->m_rx_stream, 0, 0, 0);

  // create sample buffer
  device->m_buf = new std::complex<float>();

  return device;
}

auto device::run(device& device) -> void
{
  std::stop_source stop_source {};
  std::stop_token stop_token = stop_source.get_token();

  /* std::jthread runner( */
  /*     [&device](std::stop_token stop_token) */
  /*     { */
  /*       while (!stop_token.stop_requested()) { */
  /*       } */
  /*     }); */
  /**/
  spdlog::info("Device running...");
}

/* auto device::terminate(device& device) -> void */
/* { */
/*   // stop execution */
/* } */

auto device::destroy(device& device) -> void
{
  device.~device();
}

device::device(SoapySDR::Kwargs& args)
    : m_device {SoapySDR::Device::make(args)}
{
}

/* device::̃~device() */
/* { */
/*   fftw_destroy_plan(this->m_fftexecplan); */
/*   fftw_free(this->m_fft_in); */
/*   fftw_free(this->m_fft_out); */
/**/
/*   this->m_device->deactivateStream(this->m_rx_stream, 0, 0); */
/*   this->m_device->closeStream(this->m_rx_stream); */
/*   SoapySDR::Device::unmake(m_device); */
/* } */
