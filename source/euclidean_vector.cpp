// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <fmt/format.h>
#include <iostream>
#include <list>
#include <numeric>
#include <span>
#include <utility>

#include "gsl-lite/gsl-lite.hpp"

#include "comp6771/euclidean_vector.hpp"

namespace comp6771 {

	// ---- HELPER FUNCTIONS ---- //
	// Helper function to set magnitudes to specified value
	auto set_value(std::span<double> const arr, double const val) -> void {
		ranges::fill(arr, val);
	}

	// ---- CONSTRUCTORS ---- //
	euclidean_vector::euclidean_vector(const int dim, const double val)
	: dimension_{gsl_lite::narrow_cast<size_t>(dim)} // NOLINTNEXTLINE(modernize-avoid-c-arrays)
	, magnitudes_{std::make_unique<double[]>(dimension_)} {
		set_value(std::span<double>(magnitudes_.get(), dimension_), val);
	};

	euclidean_vector::euclidean_vector(std::vector<double>::const_iterator begin,
	                                   std::vector<double>::const_iterator end)
	: dimension_{gsl_lite::narrow_cast<size_t>(ranges::distance(begin, end))}
	// NOLINTNEXTLINE(modernize-avoid-c-arrays)
	, magnitudes_{std::make_unique<double[]>(dimension_)} {
		ranges::copy(begin, end, magnitudes_.get());
	}

	// Constructor: Initializer-list
	euclidean_vector::euclidean_vector(std::initializer_list<double> magnitudes)
	: dimension_{magnitudes.size()} // NOLINTNEXTLINE(modernize-avoid-c-arrays)
	, magnitudes_{std::make_unique<double[]>(magnitudes.size())} {
		ranges::copy(magnitudes.begin(), magnitudes.end(), magnitudes_.get());
	}

	// Copy Constructor
	euclidean_vector::euclidean_vector(euclidean_vector const& orig)
	: dimension_{orig.dimension_} // NOLINTNEXTLINE(modernize-avoid-c-arrays)
	, magnitudes_{std::make_unique<double[]>(orig.dimension_)} {
		ranges::copy(orig.magnitudes_.get(),
		             orig.magnitudes_.get() + orig.dimension_,
		             magnitudes_.get());
	}

	// Move Constructor
	euclidean_vector::euclidean_vector(euclidean_vector&& orig) noexcept
	: dimension_{ranges::exchange(orig.dimension_, 0)}
	, magnitudes_{ranges::exchange(orig.magnitudes_, nullptr)} {}

	// ---- MEMBER FUNCTIONS ---- //
	auto euclidean_vector::dimensions() const -> int {
		return gsl_lite::narrow_cast<int>(dimension_);
	}

	auto euclidean_vector::at(int const idx) const -> double {
		if (idx < 0 or idx >= this->dimensions()) {
			auto const message =
			   fmt::format("Index {} is not valid for this euclidean_vector object", idx);
			throw euclidean_vector_error{message};
		}
		// return *(this->magnitudes_.get() + idx);
		return (*this)[idx];
	}

	auto euclidean_vector::at(int const idx) -> double& {
		if (idx < 0 or idx >= this->dimensions()) {
			auto const message =
			   fmt::format("Index {} is not valid for this euclidean_vector object", idx);
			throw euclidean_vector_error{message};
		}
		// return *(this->magnitudes_.get() + idx);
		return (*this)[idx];
	}

	auto euclidean_vector::clear() -> void {
		this->magnitudes_.reset();
		this->dimension_ = 0;
	}
	auto euclidean_vector::swap(euclidean_vector& other) -> void {
		ranges::swap(this->dimension_, other.dimension_);
		ranges::swap(this->magnitudes_, other.magnitudes_);
	}
	// Copy Assignment
	auto euclidean_vector::operator=(euclidean_vector const& orig) -> euclidean_vector& {
		euclidean_vector(orig).swap(*this);
		return *this;
	}
	// Move Assignment
	auto euclidean_vector::operator=(euclidean_vector&& orig) noexcept -> euclidean_vector& {
		ranges::swap(this->dimension_, orig.dimension_);
		ranges::swap(this->magnitudes_, orig.magnitudes_);
		orig.clear();

		return *this;
	}

	auto euclidean_vector::operator[](int i) const -> double {
		assert(i >= 0 and i < this->dimensions());

		return *(this->magnitudes_.get() + i);
	};
	auto euclidean_vector::operator[](int i) -> double& {
		assert(i >= 0 and i < this->dimensions());

		return *(this->magnitudes_.get() + i);
	};

	auto euclidean_vector::operator+() const -> euclidean_vector {
		return euclidean_vector(*this);
	}

	auto euclidean_vector::operator-() const -> euclidean_vector {
		return euclidean_vector(*this) * -1;
	}

	// Compound Addition
	auto euclidean_vector::operator+=(euclidean_vector const& other) -> euclidean_vector& {
		*this = *this + other;
		return *this;
	}
	// Compound Subtraction
	auto euclidean_vector::operator-=(euclidean_vector const& other) -> euclidean_vector& {
		*this = *this - other;
		return *this;
	}
	// Compound  Multiplication
	auto euclidean_vector::operator*=(double scalar) -> euclidean_vector& {
		*this = *this * scalar;
		return *this;
	}
	// Compound  Division
	auto euclidean_vector::operator/=(double scalar) -> euclidean_vector& {
		*this = *this / scalar;
		return *this;
	}
	// Convert to std::vector
	euclidean_vector::operator std::vector<double>() const {
		return std::vector<double>(this->magnitudes_.get(), this->magnitudes_.get() + this->dimension_);
	}
	// Convert to std::list
	euclidean_vector::operator std::list<double>() const {
		return std::list<double>(this->magnitudes_.get(), this->magnitudes_.get() + this->dimension_);
	}

	// ---- FRIENDS ---- //

	auto operator<<(std::ostream& os, euclidean_vector const& evec) -> std::ostream& {
		if (evec.dimensions() == 0) {
			return os << "[]";
		}

		os << "[";
		for (auto idx = 0; idx < evec.dimensions(); idx++) {
			os << evec[idx];
			if (idx < evec.dimensions() - 1) {
				os << " ";
			}
		}
		os << "]";

		return os;
	}

	auto operator==(euclidean_vector const& lhs, euclidean_vector const& rhs) -> bool {
		if (lhs.dimensions() != rhs.dimensions()) {
			return false;
		}
		for (auto idx = 0; idx < lhs.dimensions(); idx++) {
			if (lhs[idx] != rhs[idx]) {
				return false;
			}
		}
		return true;
	}

	auto operator!=(euclidean_vector const& lhs, euclidean_vector const& rhs) -> bool {
		return not(lhs == rhs);
	}
	auto operator+(euclidean_vector const& lhs, euclidean_vector const& rhs) -> euclidean_vector {
		if (lhs.dimensions() != rhs.dimensions()) {
			auto const message = fmt::format("Dimensions of LHS({}) and RHS({}) do not match",
			                                 lhs.dimensions(),
			                                 rhs.dimensions());
			throw euclidean_vector_error{message};
		}
		auto result = euclidean_vector(lhs.dimensions());
		for (auto idx = 0; idx < lhs.dimensions(); idx++) {
			result[idx] = lhs[idx] + rhs[idx];
		}

		return result;
	}

	auto operator-(euclidean_vector const& lhs, euclidean_vector const& rhs) -> euclidean_vector {
		if (lhs.dimensions() != rhs.dimensions()) {
			auto const message = fmt::format("Dimensions of LHS({}) and RHS({}) do not match",
			                                 lhs.dimensions(),
			                                 rhs.dimensions());
			throw euclidean_vector_error{message};
		}
		auto result = euclidean_vector(lhs.dimensions());
		for (auto idx = 0; idx < lhs.dimensions(); idx++) {
			result[idx] = lhs[idx] - rhs[idx];
		}

		return result;
	}

	auto operator*(euclidean_vector const& evec, double scalar) -> euclidean_vector {
		auto result = euclidean_vector(evec);
		for (auto idx = 0; idx < evec.dimensions(); idx++) {
			result[idx] *= scalar;
		}
		return result;
	}

	auto operator*(double scalar, euclidean_vector const& evec) -> euclidean_vector {
		return evec * scalar;
	}

	auto operator/(euclidean_vector const& evec, double scalar) -> euclidean_vector {
		if (scalar == 0) {
			throw euclidean_vector_error{"Invalid vector division by 0"};
		}

		return evec * (1 / scalar);
	}

	auto dot(const euclidean_vector& lhs, const euclidean_vector& rhs) -> double {
		if (lhs.dimensions() != rhs.dimensions()) {
			auto const message = fmt::format("Dimensions of LHS({}) and RHS({}) do not match",
			                                 lhs.dimensions(),
			                                 rhs.dimensions());
			throw euclidean_vector_error{message};
		}
		auto const lhs_vec = static_cast<std::list<double>>(lhs);
		auto const rhs_vec = static_cast<std::list<double>>(rhs);

		return std::inner_product(lhs_vec.begin(), lhs_vec.end(), rhs_vec.begin(), 0.0);
	}

	auto euclidean_norm(euclidean_vector const& evec) -> double {
		if (evec.dimensions() == 0) {
			throw euclidean_vector_error{"euclidean_vector with no dimensions does not have a norm"};
		}
		return sqrt(dot(evec, evec));
	}

	auto unit(euclidean_vector const& evec) -> euclidean_vector {
		if (evec.dimensions() == 0) {
			throw euclidean_vector_error{"euclidean_vector with no dimensions does not have a unit "
			                             "vector"};
		}
		auto const norm = euclidean_norm(evec);
		if (norm == 0) {
			throw euclidean_vector_error{"euclidean_vector with zero euclidean normal does not have a "
			                             "unit vector"};
		}

		return evec / norm;
	}

} // namespace comp6771
