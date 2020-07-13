#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

TEST_CASE("Operators") {
	auto const vec1 = comp6771::euclidean_vector{1, 2, 3, 4, 5}; // Const Obj
	auto vec2 = comp6771::euclidean_vector{10, 20, 30, 40, 50}; // Non Const Obj
	auto const zero_vec = comp6771::euclidean_vector(5);

	SECTION("Equal ==") {
		// Check with a const obj
		auto test_vec = comp6771::euclidean_vector{1, 2, 3, 4, 5};
		CHECK(test_vec.dimensions() == vec1.dimensions());
		CHECK(vec1[0] == test_vec[0]);
		CHECK(vec1[1] == test_vec[1]);
		CHECK(vec1[2] == test_vec[2]);
		CHECK(vec1[3] == test_vec[3]);
		CHECK(vec1[4] == test_vec[4]);

		// Check with a const obj
		CHECK(vec1 == test_vec);
		CHECK(test_vec.dimensions() == vec2.dimensions());
		test_vec[0] = vec2[0];
		test_vec[1] = vec2[1];
		test_vec[2] = vec2[2];
		test_vec[3] = vec2[3];
		test_vec[4] = vec2[4];

		CHECK(vec2 == test_vec);
	}

	SECTION("Not Equal !=") {
		// Check with a const obj
		auto test_vec1 = comp6771::euclidean_vector{5, 4, 3, 2, 1};
		CHECK(test_vec1.dimensions() == vec1.dimensions());
		CHECK(vec1[0] != test_vec1[0]);
		CHECK(vec1[1] != test_vec1[1]);
		CHECK(vec1[2] == test_vec1[2]);
		CHECK(vec1[3] != test_vec1[3]);
		CHECK(vec1[4] != test_vec1[4]);

		CHECK(vec1 != test_vec1);

		// Check with a const obj
		CHECK(test_vec1.dimensions() == vec2.dimensions());
		CHECK(vec2 != test_vec1);

		// Different Dimensions
		auto const test_vec2 = comp6771::euclidean_vector{1, 2};
		CHECK(test_vec2.dimensions() != vec2.dimensions());
		CHECK(test_vec2 != vec2);
	}

	SECTION("Addition +") {
		auto const test_vec = vec1 + vec2;
		CHECK(vec1.dimensions() == vec2.dimensions());
		CHECK(test_vec.dimensions() == vec1.dimensions());
		CHECK(test_vec[0] == vec1[0] + vec2[0]);
		CHECK(test_vec[1] == vec1[1] + vec2[1]);
		CHECK(test_vec[2] == vec1[2] + vec2[2]);
		CHECK(test_vec[3] == vec1[3] + vec2[3]);
		CHECK(test_vec[4] == vec1[4] + vec2[4]);

		CHECK(test_vec == vec1 + vec2);

		CHECK(zero_vec.dimensions() == test_vec.dimensions());
		auto const test_vec2 = test_vec + zero_vec;
		CHECK(test_vec == test_vec2);
	}

	SECTION("Subtraction -") {
		auto const test_vec = vec1 - vec2;
		CHECK(vec1.dimensions() == vec2.dimensions());
		CHECK(test_vec.dimensions() == vec1.dimensions());
		CHECK(test_vec[0] == vec1[0] - vec2[0]);
		CHECK(test_vec[1] == vec1[1] - vec2[1]);
		CHECK(test_vec[2] == vec1[2] - vec2[2]);
		CHECK(test_vec[3] == vec1[3] - vec2[3]);
		CHECK(test_vec[4] == vec1[4] - vec2[4]);

		CHECK(test_vec == vec1 - vec2);

		CHECK(zero_vec.dimensions() == test_vec.dimensions());
		auto const test_vec2 = test_vec - zero_vec;
		CHECK(test_vec2 == test_vec);
		auto const test_vec3 = zero_vec - test_vec;
		CHECK(test_vec3 == -test_vec);
	}

	SECTION("Multiplication *") {
		auto const scalar = 10;

		// a = b * #
		auto const result1 = vec1 * scalar;
		CHECK(result1.dimensions() == vec1.dimensions());
		CHECK(result1[0] == vec1[0] * scalar);
		CHECK(result1[1] == vec1[1] * scalar);
		CHECK(result1[2] == vec1[2] * scalar);
		CHECK(result1[3] == vec1[3] * scalar);
		CHECK(result1[4] == vec1[4] * scalar);

		CHECK(result1 == vec2);
		CHECK(result1.dimensions() == vec2.dimensions());

		// a = # * b
		auto const result2 = scalar * vec1;
		CHECK(result2.dimensions() == vec1.dimensions());
		CHECK(result2[0] == scalar * vec1[0]);
		CHECK(result2[1] == scalar * vec1[1]);
		CHECK(result2[2] == scalar * vec1[2]);
		CHECK(result2[3] == scalar * vec1[3]);
		CHECK(result2[4] == scalar * vec1[4]);

		CHECK(result1 == result2);
	}

	SECTION("Division /") {
		auto const scalar = 10;

		// a = b / #
		auto const result1 = vec1 / scalar;
		CHECK(result1.dimensions() == vec1.dimensions());
		CHECK(result1[0] == Approx(vec1[0] / scalar));
		CHECK(result1[1] == Approx(vec1[1] / scalar));
		CHECK(result1[2] == Approx(vec1[2] / scalar));
		CHECK(result1[3] == Approx(vec1[3] / scalar));
		CHECK(result1[4] == Approx(vec1[4] / scalar));
	}

	SECTION("Output Stream <<") {
		SECTION("Dimension 0") {
			// Dimension: 0     Magnitudes: _
			auto const test_vec = comp6771::euclidean_vector(0);
			CHECK(test_vec.dimensions() == 0);
			CHECK(fmt::format("{}", test_vec) == "[]");
		}
		SECTION("Dimension 1") {
			// Dimension: 1     Magnitudes: 1
			auto const test_vec = comp6771::euclidean_vector(1, 1);
			CHECK(test_vec.dimensions() == 1);
			CHECK(fmt::format("{}", test_vec) == "[1]");
		}
		SECTION("Dimension > 1") {
			// Dimension: 2     Magnitudes: 1 2
			auto const test_vec = comp6771::euclidean_vector{1, 2};
			CHECK(test_vec.dimensions() == 2);
			CHECK(fmt::format("{}", test_vec) == "[1 2]");
		}
		SECTION("Magnitude > 1") {
			// Dimension: 5     Magnitudes: 10 20 30 40 50
			// vec2 => {10, 20, 30, 40, 50}
			CHECK(vec2.dimensions() == 5);
			CHECK(fmt::format("{}", vec2) == "[10 20 30 40 50]");
		}
	}
}