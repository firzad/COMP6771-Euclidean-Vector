#include <iostream>

#include "comp6771/euclidean_vector.hpp"

auto main() -> int {
	auto const a1 = comp6771::euclidean_vector(3, 9.0);
	auto a = comp6771::euclidean_vector(1); // a Euclidean Vector in 1 dimension, with default
	                                        // magnitude 0.0.
	auto b = comp6771::euclidean_vector(2, 4.0); // a Euclidean Vector in 2 dimensions with
	                                             // magnitude 4.0 in both dimensions

	auto l = std::vector<double>{5.0, 6.5, 7.0};
	auto c = comp6771::euclidean_vector(l.begin(), l.end()); // a Euclidean Vector in 3 dimensions
	                                                         // constructed from a vector of
	                                                         // magnitudes
	auto d = comp6771::euclidean_vector(0);

	std::cout << d;

	return 1;
}