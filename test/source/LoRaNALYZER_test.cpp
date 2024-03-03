#include <string>

#include "LoRaNALYZER/LoRaNALYZER.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Name is LoRaNALYZER", "[library]")
{
  auto const exported = exported_class {};
  REQUIRE(std::string("LoRaNALYZER") == exported.name());
}
