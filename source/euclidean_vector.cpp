// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>
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
		std::copy(orig.magnitudes_.get(), orig.magnitudes_.get() + orig.dimension_, magnitudes_.get());
	}

	// Move Constructor
	euclidean_vector::euclidean_vector(euclidean_vector&& orig) noexcept
	: dimension_{std::exchange(orig.dimension_, 0)}
	, magnitudes_{std::exchange(orig.magnitudes_, nullptr)} {}

	// ---- MEMBER FUNCTIONS ---- //
	auto euclidean_vector::dimensions() const -> int {
		return gsl_lite::narrow_cast<int>(dimension_);
	}

	auto operator<<(std::ostream& os, euclidean_vector const& vec) -> std::ostream& {
		if (vec.dimensions() == 0) {
			return os << "[]";
		}

		os << "[";
		for (auto idx = static_cast<size_t>(0); idx < vec.dimension_; idx++) {
			os << *(vec.magnitudes_.get() + idx);
			if (idx < vec.dimension_ - 1) {
				os << " ";
			}
		}
		os << "]";

		return os;
	}

} // namespace comp6771
