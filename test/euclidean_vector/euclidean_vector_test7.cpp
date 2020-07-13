#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

TEST_CASE("Utility Functions") {
	auto const vec1 = comp6771::euclidean_vector{1, 2, 3}; // Const Obj
	auto vec2 = comp6771::euclidean_vector{10, 20, 30, 40, 50}; // Non Const Obj
	auto const zero_vec = comp6771::euclidean_vector(5);

	SECTION("unit() Fn") {
		auto const vec1_unit = comp6771::unit(vec1);
		auto const vec1_norm = comp6771::euclidean_norm(vec1);
		CHECK(vec1.dimensions() == vec1_unit.dimensions());
		CHECK(vec1_unit == vec1 / vec1_norm);

		CHECK(vec1_unit[0] == Approx(vec1[0] / vec1_norm));
		CHECK(vec1_unit[1] == Approx(vec1[1] / vec1_norm));
		CHECK(vec1_unit[2] == Approx(vec1[2] / vec1_norm));

		CHECK(fmt::format("{}", vec1_unit) == "[0.267261 0.534522 0.801784]");
	}

	SECTION("euclidean_norm() Fn") {
		auto const vec1_norm = comp6771::euclidean_norm(vec1);
		CHECK(vec1_norm == Approx(sqrt(vec1[0] * vec1[0] + vec1[1] * vec1[1] + vec1[2] * vec1[2])));
		CHECK(vec1_norm == Approx(3.74166));
	}

	SECTION("dot() Fn") {
		auto const op1 = comp6771::euclidean_vector{1, 2};
		auto const op2 = comp6771::euclidean_vector{3, 4};

		auto const res1 = comp6771::dot(op1, op2);
		auto const res2 = comp6771::dot(op2, op1);

		CHECK(op1.dimensions() == op2.dimensions());
		CHECK(res1 == op1[0] * op2[0] + op1[1] * op2[1]);
		CHECK(res1 == 11); // [1 2] . [3 4] = 1 * 3 + 2 * 4 = 11
		CHECK(res1 == res2);

		// [10 20 30 40 50] * [0 0 0 0 0] = 0 + 0 + 0 + 0 + 0 = 0
		auto const zero_dot = comp6771::dot(vec2, zero_vec);
		CHECK(zero_dot == 0.0);
	}
}