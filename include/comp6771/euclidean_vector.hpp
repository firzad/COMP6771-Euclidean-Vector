#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <compare>
#include <functional>
#include <list>
#include <memory>
#include <ostream>
#include <range/v3/algorithm.hpp>
#include <range/v3/iterator.hpp>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what) noexcept
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		// --- CONSTRUCTORS --- //
		// Default Constructor
		euclidean_vector()
		: euclidean_vector(1, 0.0){};
		// Single-argument Constructor
		explicit euclidean_vector(int const i)
		: euclidean_vector(i, 0.0){};
		// Constructor: Dimension and Magnitude
		euclidean_vector(int, double);
		// Constructor: Iterators
		euclidean_vector(std::vector<double>::const_iterator, std::vector<double>::const_iterator);
		// Constructor: Initializer-list
		euclidean_vector(std::initializer_list<double>);
		// Copy Constructor
		euclidean_vector(euclidean_vector const&);
		// Move Constructor
		euclidean_vector(euclidean_vector&&) noexcept;

		// --- DESTRUCTOR --- //
		~euclidean_vector() = default;

		// --- MEMEBER FUNCTIONS --- //
		[[nodiscard]] auto dimensions() const -> int;

		// --- OPERATORS --- //

		// --- FRIEND FUNCTIONS --- //
		friend auto operator<<(std::ostream&, euclidean_vector const&) -> std::ostream&;

		// --- TYPE CONVERSIONS --- //

	private:
		size_t dimension_ = 0;

		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitudes_;

		// double normal_ = -1.0;
	};

} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
