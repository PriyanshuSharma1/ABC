#include <iostream>
#include "pricely_impl.h"
#include "csv_loader.h" // Include the CSV loader header
#include "builder/builder_context.h"
#include "blocks/c_code_generator.h"
#include <vector>
#include <string>
#include <algorithm> // For std::find_if

using builder::dyn_var;
using pricely::Product;
using pricely::DiscountRule;
using pricely::Competitor;
using pricely::Customer;

// Function to calculate dynamic pricing based on discounts, competitors, and customer data
static void calculate_dynamic_price() {
    // Load products, discounts, competitors, and customers from CSV files
    std::vector<Product> products = load_products("data/products.csv");
    if (products.empty()) {
        std::cerr << "Error: Failed to load products." << std::endl;
        return;
    }

    std::vector<DiscountRule> discounts = load_discounts("data/discounts.csv");
    if (discounts.empty()) {
        std::cerr << "Error: Failed to load discount rules." << std::endl;
        return;
    }

    std::vector<Competitor> competitors = load_competitors("data/competitors.csv", products);
    if (competitors.empty()) {
        std::cerr << "Warning: No competitor data available." << std::endl;
    }

    std::vector<Customer> customers = load_customers("data/customers.csv");
    if (customers.empty()) {
        std::cerr << "Warning: No customer data available." << std::endl;
    }

    // Apply discounts to products if applicable, in parallel
    #pragma omp parallel for schedule(dynamic)
    for (size_t i = 0; i < products.size(); ++i) {
    for (const auto &discount : discounts) {
        if (discount.is_applicable(products[i].category)) {
            products[i].apply_discount(dyn_var<int>(discount.value));
        }
    }
}


    // Adjust product prices based on competitor offers, in parallel
    #pragma omp parallel for schedule(dynamic)
    for (size_t i = 0; i < competitors.size(); ++i) {
        auto product = std::find_if(products.begin(), products.end(),
                                    [&](const Product &p) { return p.productID == competitors[i].product.productID; });
        if (product != products.end() && competitors[i].offerred_price < product->currentPrice) {
            #pragma omp critical // Ensure thread-safe update
            {
                product->currentPrice = competitors[i].offerred_price - 20; // Adjust price slightly below competitor
            }
        }
    }

    // Apply additional discounts for loyal customers, in parallel
    #pragma omp parallel for schedule(dynamic)
    for (size_t i = 0; i < customers.size(); ++i) {
        if (customers[i].loyalty_points > 100) {
            #pragma omp critical // Ensure thread-safe discount application
            {
                for (auto &product : products) {
                    product.currentPrice *= 0.95; // Apply 5% discount for loyal customers
                }
            }
        }
    }

    // Output the final product prices
    for (const auto &product : products) {
        std::cout << "Product: " << product.name << ", Final Price: " << dyn_var<int>(product.currentPrice) << std::endl;
    }
}

int main(int argc, char *argv[]) {
    builder::builder_context context;
    std::cout << "Starting dynamic pricing calculation..." << std::endl;

    try {
        // Extract the AST for `calculate_dynamic_price` function and generate C code
        auto ast = context.extract_function_ast(calculate_dynamic_price, "calculate_dynamic_price");
        block::c_code_generator::generate_code(ast, std::cout, 0);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}