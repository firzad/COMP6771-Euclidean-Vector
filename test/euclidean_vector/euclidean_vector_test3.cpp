#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

TEST_CASE("Operations") {
	// Const Obj
	auto const vec1 = comp6771::euclidean_vector{1, 2, 3, 4, 5};
	// Non-Const Obj
	auto vec2 = comp6771::euclidean_vector{10, 20, 30, 40, 50};

	CHECK(vec1.dimensions() == vec2.dimensions());

	auto const zero_vector = comp6771::euclidean_vector(5, 0);
	CHECK(vec1.dimensions() == zero_vector.dimensions());

	SECTION("Copy Assignment") {
		// Linting disabled to check copy assignment function
		// NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
		auto vec1_copy = vec1;
		CHECK(vec1 == vec1_copy);

		vec1_copy[1] = 0;
		CHECK(vec1 != vec1_copy);
		CHECK(vec1[1] == 2);
		CHECK(vec1_copy[1] == 0);
	}

	SECTION("Move Assignment") {
		// Linting disabled to check copy assignment function
		// NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
		auto vec1_copy = vec1;
		CHECK(vec1 == vec1_copy);

		auto vec1_move = std::move(vec1_copy);

		CHECK(vec1 == vec1_move);
		// Linting disabled to show that the moved object will have dimension 0.
		// NOLINTNEXTLINE(bugprone-use-after-move)
		CHECK(vec1_copy.dimensions() == 0);
	}

	SECTION("Subscript Operator") {
		// Subscript operation on a non const obj
		SECTION("Non Const Obj") {
			auto vec_test = vec1;
			CHECK(fmt::format("{}", vec_test) == "[1 2 3 4 5]");
			CHECK(vec_test[0] == 1);
			CHECK(vec_test[2] == 3);

			vec_test[0] = 5;
			CHECK(vec_test[0] == 5);
			CHECK(fmt::format("{}", vec_test) == "[5 2 3 4 5]");
		}
		// Subscript operation on a const obj
		SECTION("Const Obj") {
			CHECK(fmt::format("{}", vec1) == "[1 2 3 4 5]");

			CHECK(vec1[0] == 1);
			CHECK(vec1[4] == 5);
		}
	}

	SECTION("Unary +") {
		// Unary + operation on a const obj
		SECTION("Const Obj") {
			auto vec1_test = +vec1;
			CHECK(vec1 == vec1_test);

			vec1_test[0] = 0;
			CHECK(vec1 != vec1_test);
			CHECK(vec1[0] == 1);
		}
		// Unary + operation on a Non-const obj
		SECTION("Non Const Obj") {
			auto vec2_test = +vec2;
			CHECK(vec2 == vec2_test);

			vec2_test[0] = 0;
			CHECK(vec2 != vec2_test);
			CHECK(vec2[0] == 10);
		}
		// Unary + operation on Zero Vector
		SECTION("Non Const Obj") {
			auto vec3_test = +zero_vector;
			CHECK(vec3_test == vec3_test);

			vec3_test[0] = 0;
			vec3_test[1] = 0;
		}
	}

	SECTION("Negation") {
		SECTION("Const Obj") {
			auto const vec1_test = -vec1;
			CHECK(vec1_test[0] == -vec1[0]);
			CHECK(vec1_test[1] == -vec1[1]);
			CHECK(vec1_test[2] == -vec1[2]);
			CHECK(vec1_test[3] == -vec1[3]);
			CHECK(vec1_test[4] == -vec1[4]);
		}
		SECTION("Non Const Obj") {
			auto const vec2_test = -vec2;
			CHECK(vec2_test[0] == -vec2[0]);
			CHECK(vec2_test[1] == -vec2[1]);
			CHECK(vec2_test[2] == -vec2[2]);
			CHECK(vec2_test[3] == -vec2[3]);
			CHECK(vec2_test[4] == -vec2[4]);
		}
		SECTION("Zero Vector") {
			auto const vec3_test = -zero_vector;
			CHECK(vec3_test == zero_vector);
		}
	}

	SECTION("Compound Addition +=") {
		auto operand1 = vec1;
		operand1 += vec2;

		CHECK(operand1.dimensions() == vec2.dimensions());
		CHECK(operand1[0] == vec1[0] + vec2[0]);
		CHECK(operand1[1] == vec1[1] + vec2[1]);
		CHECK(operand1[2] == vec1[2] + vec2[2]);
		CHECK(operand1[3] == vec1[3] + vec2[3]);
		CHECK(operand1[4] == vec1[4] + vec2[4]);

		// Zero Vector
		auto operand1_copy = operand1;
		operand1 += zero_vector;
		CHECK(operand1 == operand1_copy);
	}

	SECTION("Compound Subtraction -=") {
		auto operand1 = vec1;
		operand1 -= vec2;

		CHECK(operand1.dimensions() == vec2.dimensions());
		CHECK(operand1[0] == vec1[0] - vec2[0]);
		CHECK(operand1[1] == vec1[1] - vec2[1]);
		CHECK(operand1[2] == vec1[2] - vec2[2]);
		CHECK(operand1[3] == vec1[3] - vec2[3]);
		CHECK(operand1[4] == vec1[4] - vec2[4]);

		// Zero Vector
		auto operand1_copy = operand1;
		operand1 -= zero_vector;
		CHECK(operand1 == operand1_copy);
	}

	SECTION("Compound Multiplication *=") {
		auto operand1 = vec1;
		auto const scalar = 10;
		operand1 *= scalar;

		CHECK(operand1.dimensions() == vec1.dimensions());
		CHECK(operand1[0] == vec1[0] * scalar);
		CHECK(operand1[1] == vec1[1] * scalar);
		CHECK(operand1[2] == vec1[2] * scalar);
		CHECK(operand1[3] == vec1[3] * scalar);
		CHECK(operand1[4] == vec1[4] * scalar);

		// Zero Vector
		CHECK(zero_vector * scalar == zero_vector);
	}

	SECTION("Compound Division /=") {
		auto operand1 = vec1;
		auto const scalar = 10;
		operand1 /= scalar;

		CHECK(operand1.dimensions() == vec1.dimensions());
		CHECK(operand1[0] == Approx(vec1[0] / scalar));
		CHECK(operand1[1] == Approx(vec1[1] / scalar));
		CHECK(operand1[2] == Approx(vec1[2] / scalar));
		CHECK(operand1[3] == Approx(vec1[3] / scalar));
		CHECK(operand1[4] == Approx(vec1[4] / scalar));

		// Zero Vector
		CHECK(zero_vector / scalar == zero_vector);
	}
}