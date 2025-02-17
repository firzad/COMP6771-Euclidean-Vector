#include <iostream>

#include "comp6771/euclidean_vector.hpp"

auto main() -> int {
	auto const a = comp6771::euclidean_vector(3, 9.0);
	auto b = comp6771::euclidean_vector(1); // a Euclidean Vector in 1 dimension, with default
	                                        // magnitude 0.0.
	auto c = comp6771::euclidean_vector(2, 4.0); // a Euclidean Vector in 2 dimensions with
	                                             // magnitude 4.0 in both dimensions

	auto l = std::vector<double>{5.0, 6.5, 7.0};
	auto d = comp6771::euclidean_vector(l.begin(), l.end()); // a Euclidean Vector in 3 dimensions
	                                                         // constructed from a vector of
	                                                         // magnitudes
	auto e = comp6771::euclidean_vector(0);

	auto f = comp6771::euclidean_vector{2, 4.0, 6.0, 8.0};

	std::cout << a.at(0) << "\n";

	std::cout << a << "\n";
	std::cout << b << "\n";
	std::cout << c << "\n";
	std::cout << d << "\n";
	std::cout << e << "\n";
	std::cout << f << "\n";

	auto const i = comp6771::euclidean_vector{1, 2, 3};
	std::cout << comp6771::euclidean_norm(i) << "\n";
	std::cout << comp6771::unit(i) << "\n";

	return 1;
}