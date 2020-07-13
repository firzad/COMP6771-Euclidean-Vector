#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

TEST_CASE("Constructors") {
	SECTION("Dimension and Magnitude") {
		auto const a1 = comp6771::euclidean_vector(3, 9.0);
		CHECK(fmt::format("{}", a1) == "[9 9 9]");
		CHECK(a1.dimensions() == 3);

		// a Euclidean Vector in 2 dimensions with
		// magnitude 4.0 in both dimensions
		auto const a2 = comp6771::euclidean_vector(2, 4.0);
		CHECK(a2[0] == 4.0);
		CHECK(a2[1] == 4.0);
		CHECK(a2.dimensions() == 2);
	}

	SECTION("Single Argument Constructor") {
		// a Euclidean Vector in 1 dimension, with default
		// magnitude 0.0.
		auto const b = comp6771::euclidean_vector(1);
		CHECK(fmt::format("{}", b) == "[0]");
		CHECK(b.dimensions() == 1);
		CHECK(b[0] == 0);
	}

	SECTION("Vector Iterators") {
		// a Euclidean Vector in 3 dimensions constructed from a vector of magnitudes
		auto const dvec = std::vector<double>{5.0, 6.5, 7.0};
		auto const c = comp6771::euclidean_vector(dvec.begin(), dvec.end());
		CHECK(fmt::format("{}", c) == "[5 6.5 7]");
		CHECK(c.dimensions() == 3);
		CHECK(c[0] == 5);
		CHECK(c[1] == 6.5);
		CHECK(c[2] == 7);
	}
	SECTION("Zero Vector") {
		auto const d = comp6771::euclidean_vector(0);
		CHECK(d.dimensions() == 0);
	}

	SECTION("Initializer List") {
		auto const e = comp6771::euclidean_vector{2, 4.0, 6.0, 8.0};
		CHECK(fmt::format("{}", e) == "[2 4 6 8]");
		CHECK(e.dimensions() == 4);
		CHECK(e[0] == 2);
		CHECK(e[1] == 4);
		CHECK(e[2] == 6);
		CHECK(e[3] == 8);
	}

	SECTION("COPY and MOVE Constructors") {
		auto root = comp6771::euclidean_vector{1, 2, 3, 4, 5};
		auto const root_copy = comp6771::euclidean_vector(root);

		SECTION("Copy Constructor") {
			CHECK(root.dimensions() == root_copy.dimensions());
			CHECK(root == root_copy);
			CHECK(root[0] == root_copy[0]);
			CHECK(root[1] == root_copy[1]);
			CHECK(root[2] == root_copy[2]);
			CHECK(root[3] == root_copy[3]);
			CHECK(root[4] == root_copy[4]);
		}

		SECTION("Move Constructor") {
			auto const root_move = comp6771::euclidean_vector(std::move(root));
			CHECK(root_copy.dimensions() == root_move.dimensions());
			CHECK(root_copy == root_move);
			CHECK(root_copy[0] == root_move[0]);
			CHECK(root_copy[1] == root_move[1]);
			CHECK(root_copy[2] == root_move[2]);
			CHECK(root_copy[3] == root_move[3]);
			CHECK(root_copy[4] == root_move[4]);

			// Linting disabled to show that the moved object will have dimension 0.
			// NOLINTNEXTLINE(bugprone-use-after-move)
			CHECK(root.dimensions() == 0);
		}
	}
}