#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

TEST_CASE("Memeber Functions") {
	auto const vec1 = comp6771::euclidean_vector{1, 2, 3, 4, 5};
	auto vec2 = comp6771::euclidean_vector{10, 20, 30, 40, 50};

	SECTION("at() Fn") {
		CHECK(vec1.at(0) == 1); // Const Obj
		CHECK(vec2.at(0) == 10); // Non Const Obj
	}

	SECTION("dimensions() Fn") {
		CHECK(vec1.dimensions() == 5); // Const Obj
		CHECK(vec2.dimensions() == 5); // Non Const Obj
	}
}