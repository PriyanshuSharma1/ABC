#ifndef PRICELY_OPERATORS_H
#define PRICELY_OPERATORS_H

#include "pricely_types.h"

namespace pricely {

template <typename T>
struct is_acceptable_type {
    static const bool value = false;
};

// Specialization for Product
template <>
struct is_acceptable_type<Product> {
    static const bool value = true;
    using output_type = Product;

    static const Product& cast(const Product& v) {
        return v; // No transformation required
    }
};

// Specialization for DiscountRule
template <>
struct is_acceptable_type<DiscountRule> {
    static const bool value = true;
    using output_type = DiscountRule;

    static const DiscountRule& cast(const DiscountRule& v) {
        return v; // No transformation required
    }
};

// Specialization for integers (used for discount percentages, etc.)
template <>
struct is_acceptable_type<int> {
    static const bool value = true;
    using output_type = int;

    static int cast(const int& v) {
        return v; // Simple direct cast
    }
};

// Specialization for floats (used for prices and calculations)
template <>
struct is_acceptable_type<float> {
    static const bool value = true;
    using output_type = float;

    static float cast(const float& v) {
        return v; 
    }
};

template <typename T1, typename T2>
typename std::enable_if<is_acceptable_type<T2>::value, T1>::type operator + (const T1& v1, const T2& v2) {
    return T1(is_acceptable_type<T1>::cast(v1) + is_acceptable_type<T2>::cast(v2)); 
}


template <typename T1, typename T2>
typename std::enable_if<is_acceptable_type<T2>::value, T1>::type operator * (const T1& v1, const T2& v2) {
    return T1(is_acceptable_type<T1>::cast(v1) * is_acceptable_type<T2>::cast(v2)); 
}

// Function to apply discounts to a product
Product apply_discount(const Product& product, const DiscountRule& discount) {
    Product modifiedProduct = product;
    if (discount.discountType == "percentage") {
        modifiedProduct.currentPrice = product.basePrice * (1 - discount.value / 100.0);
    } else {
        modifiedProduct.currentPrice = product.basePrice - discount.value;
    }
    return modifiedProduct;
}

}

#endif 
