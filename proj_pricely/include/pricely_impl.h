#ifndef PRODUCT_IMPL_H
#define PRODUCT_IMPL_H

#include "builder/dyn_var.h"
#include "builder/static_var.h"
#include <string>
#include <vector>
#include <algorithm> // For std::find

namespace pricely {

    // Base Product class for storing and managing product information
struct Product {
    std::string productID;    // Product ID (constant at compile-time)
    std::string name;         // Product name (constant at compile-time)
    builder::dyn_var<float> basePrice;
    builder::dyn_var<float> currentPrice;
    std::string category;     // Product category for discount applicability


    // Constructor to initialize a Product with dynamic variables
    Product(const std::string &id, const std::string &prodName, float base_price, float current_price)
        : productID(id), name(prodName) {
        basePrice = base_price;
        currentPrice = current_price;
    }

    // Method to apply a discount
    void apply_discount(int discount_percent) {
        currentPrice = currentPrice - (currentPrice * discount_percent / 100.0f);
    }
};

// DiscountRule class for storing discount rules and their properties
struct DiscountRule {
    std::string description;  // Description of the discount rule
    std::string discountType; // Type of discount (e.g., "percentage")
    builder::dyn_var<int> value;
    std::vector<std::string> applicableCategories;
    std::string validityPeriod; // Discount validity period

    // Constructor to initialize a DiscountRule
    DiscountRule(const std::string &desc, const std::string &type, int val, 
                 const std::vector<std::string> &categories, const std::string &validity)
        : description(desc), discountType(type), applicableCategories(categories), validityPeriod(validity) {
        value = val;
    }

    // Method to check if the discount applies to a product
    bool is_applicable(const std::string &productCategory) const {
        return std::find(applicableCategories.begin(), applicableCategories.end(), productCategory) != applicableCategories.end();
    }
};

// Competitor class to handle competitor pricing data
struct Competitor {
    std::string competitor_ID;   // Unique identifier for the competitor
    Product product;             // Competitor's product
    builder::dyn_var<float> offerred_price;

    // Constructor to initialize a Competitor and their product offering
    Competitor(const std::string &id, const Product &prod, float price)
        : competitor_ID(id), product(prod) {
        offerred_price = price;
    }
};

// Customer class to handle customer data
struct Customer {
    std::string customer_ID;         // Unique identifier for the customer
    std::string name;                // Customer's name
    builder::dyn_var<float> loyalty_points;

    // Constructor to initialize a Customer with initial loyalty points
    Customer(const std::string &id, const std::string &custName, float points)
        : customer_ID(id), name(custName) {
        loyalty_points = points;
    }

    // Method to update loyalty points
    void add_loyalty_points(float points) {
        loyalty_points = loyalty_points + points;
    }
};

} // namespace pricely

#endif // PRODUCT_IMPL_H
