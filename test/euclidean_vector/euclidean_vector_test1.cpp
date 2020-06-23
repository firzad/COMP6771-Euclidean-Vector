#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

TEST_CASE("basic test") {
	auto const a1 = comp6771::euclidean_vector(3, 3.0);

	CHECK(fmt::format("{}", a1 + a2 + a3) == "[9]");
}