#ifndef PRICELY_TYPES_H
#define PRICELY_TYPES_H

#include "builder/dyn_var.h"
#include <string>

struct Product : public builder::custom_type<> {
    // Define type_name as required for custom types
    static const char* type_name;

    // Keep productID and name as regular std::string
    std::string productID;
    std::string name;

    // Use dyn_var only for members that require dynamic behavior
    builder::dyn_var<float> basePrice = builder::as_member("basePrice");
    builder::dyn_var<float> currentPrice = builder::as_member("currentPrice");
};

// Define the type_name for the generated code to reference this type
const char* Product::type_name = "Product";
struct DiscountRule : public builder::custom_type<> {
    // Define type_name as required for custom types
    static const char* type_name;

    // Keep productID and name as regular std::string
    std::string description;
    std::string discountType;
    std::string validityPeriod;


    // Use dyn_var only for members that require dynamic behavior
    builder::dyn_var<int> value = builder::as_member("value");
    builder::dyn_var<std::vector<std::string>> applicableCategories = builder::as_member("applicableCategories");

   
};
// Define the type_name for DiscountRule
const char* DiscountRule::type_name = "DiscountRule";

struct Competitor : public builder::custom_type<> {
    // Define type_name as required for custom types
    static const char* type_name;

    std::string competitor_ID;
    Product prod;
    // Use dyn_var only for members that require dynamic behavior
    builder::dyn_var<float> offerred_price = builder::as_member("offerred_price");
   
};
// Define the type_name for Competitor
const char* Competitor::type_name = "Competitor";

struct Customer : public builder::custom_type<> {
    // Define type_name as required for custom types
    static const char* type_name;

    std::string customer_ID;
    std::string name;
    // Use dyn_var only for members that require dynamic behavior
    builder::dyn_var<float> loyalty_points = builder::as_member("loyalty_points");
   
};
// Define the type_name for Competitor
const char* Customer::type_name = "Customer";

#endif // PRODUCT_H
