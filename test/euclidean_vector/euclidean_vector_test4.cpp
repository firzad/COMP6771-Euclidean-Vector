
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <list>

#include "comp6771/euclidean_vector.hpp"
#include "gsl-lite/gsl-lite.hpp"

TEST_CASE("Type Convesion") {
	auto const vec1 = comp6771::euclidean_vector{1, 2, 3, 4, 5};
	auto vec2 = comp6771::euclidean_vector{10, 20, 30, 40, 50};

	// Conversion of EV to std::list
	SECTION("List") {
		// On Const Obj
		auto const vec1_list = static_cast<std::list<double>>(vec1);
		CHECK(vec1.dimensions() == gsl_lite::narrow_cast<int>(vec1_list.size()));

		auto const test_list1 = std::list<double>{1, 2, 3, 4, 5};
		CHECK(vec1_list == test_list1);

		// On Non-Constant Obj
		auto const vec2_list = static_cast<std::list<double>>(vec2);
		CHECK(vec2.dimensions() == gsl_lite::narrow_cast<int>(vec2_list.size()));

		auto const test_list2 = std::list<double>{10, 20, 30, 40, 50};
		CHECK(vec2_list == test_list2);
	}

	// Conversion of EV to std::vector
	SECTION("Vector") {
		// On Const Obj
		auto const vec1_vector = static_cast<std::vector<double>>(vec1);
		CHECK(vec1.dimensions() == gsl_lite::narrow_cast<int>(vec1_vector.size()));

		auto const test_vector1 = std::vector<double>{1, 2, 3, 4, 5};
		CHECK(vec1_vector == test_vector1);

		// On Non-Constant Obj
		auto const vec2_vector = static_cast<std::vector<double>>(vec2);
		CHECK(vec2.dimensions() == gsl_lite::narrow_cast<int>(vec2_vector.size()));

		auto const test_vector2 = std::vector<double>{10, 20, 30, 40, 50};
		CHECK(vec2_vector == test_vector2);
	}
}