#pragma once

#include <cstdint>
#include <ranges>
#include <stop_token>
#include <thread>

#include <SoapySDR/Device.hpp>
#include <SoapySDR/Formats.hpp>
#include <SoapySDR/Types.hpp>
#include <fftw3.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include "LoRaNALYZER/LoRaNALYZER_export.hpp"
#include "config.hpp"

namespace analyzer
{

class device
{
public:
  static auto create(config& config) -> device*;
  static auto run(device& device) -> void;
  /* static auto terminate(device& device) -> void; */
  static auto destroy(device& device) -> void;

private:
  explicit device(SoapySDR::Kwargs& args);
  ~device()
  {
    fftw_destroy_plan(this->m_fftexecplan);
    fftw_free(this->m_fft_in);
    fftw_free(this->m_fft_out);

    this->m_device->deactivateStream(this->m_rx_stream, 0, 0);
    this->m_device->closeStream(this->m_rx_stream);
    SoapySDR::Device::unmake(m_device);
  }

  // device
  SoapySDR::Device* m_device;
  SoapySDR::Stream* m_rx_stream;

  // sample buffer
  std::complex<float>* m_buf;

  fftw_complex* m_fft_in;
  fftw_complex* m_fft_out;
  fftw_plan m_fftexecplan;
};

}  // namespace analyzer
