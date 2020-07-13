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
		[[nodiscard]] auto at(int) const -> double;
		auto at(int) -> double&;

		// --- OPERATORS --- //

		auto clear() -> void;
		auto swap(euclidean_vector& other) -> void;
		// Copy Assignment
		auto operator=(euclidean_vector const&) -> euclidean_vector&;
		// Move Assignment
		auto operator=(euclidean_vector&&) noexcept -> euclidean_vector&;
		// Subscript
		auto operator[](int i) const -> double;
		auto operator[](int i) -> double&;
		// Unary Plus
		auto operator+() const -> euclidean_vector;
		// Negation
		auto operator-() const -> euclidean_vector;
		// Compound Addition
		auto operator+=(euclidean_vector const&) -> euclidean_vector&;
		// Compound Subtraction
		auto operator-=(euclidean_vector const&) -> euclidean_vector&;
		// Compound  Multiplication
		auto operator*=(double) -> euclidean_vector&;
		// Compound  Division
		auto operator/=(double) -> euclidean_vector&;

		// --- FRIEND FUNCTIONS --- //

		friend auto operator<<(std::ostream&, euclidean_vector const&) -> std::ostream&;
		friend auto operator==(euclidean_vector const&, euclidean_vector const&) -> bool;
		friend auto operator!=(euclidean_vector const&, euclidean_vector const&) -> bool;
		friend auto operator+(euclidean_vector const&, euclidean_vector const&) -> euclidean_vector;
		friend auto operator-(euclidean_vector const&, euclidean_vector const&) -> euclidean_vector;
		friend auto operator*(euclidean_vector const&, double) -> euclidean_vector;
		friend auto operator*(double, euclidean_vector const&) -> euclidean_vector;
		friend auto operator/(euclidean_vector const&, double) -> euclidean_vector;

		// --- TYPE CONVERSIONS --- //

		// Vector Conversion
		explicit operator std::vector<double>() const;
		// List Conversion
		explicit operator std::list<double>() const;

	private:
		size_t dimension_ = 0;

		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitudes_;
	};

	auto euclidean_norm(euclidean_vector const&) -> double;
	auto dot(euclidean_vector const&, euclidean_vector const&) -> double;
	auto unit(euclidean_vector const&) -> euclidean_vector;

} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
