#include <iostream>
#include "pricely_impl.h"
#include "csv_loader.h" // Include the CSV loader header
#include "builder/builder_context.h"
#include "blocks/c_code_generator.h"
#include <vector>
#include <string>

  // Include OpenMP header

using builder::dyn_var;
using pricely::Product;
using pricely::DiscountRule;
using pricely::Competitor;
using pricely::Customer;

// Function to calculate dynamic pricing based on discounts, competitors, and customer data
static void calculate_dynamic_price() {
    // Load products, discounts, competitors, and customers from CSV files
    std::vector<Product> products = load_products("data/products.csv");
    std::vector<DiscountRule> discounts = load_discounts("data/discounts.csv");
    std::vector<Competitor> competitors = load_competitors("data/competitors.csv", products);
    std::vector<Customer> customers = load_customers("data/customers.csv");

    // Apply discounts to products if applicable, in parallel
    #pragma omp parallel for
    for (size_t i = 0; i < discounts.size(); ++i) {
        for (size_t j = 0; j < products.size(); ++j) {
            if (discounts[i].is_applicable("Electronics")) { // Adjust category as needed
                products[j].apply_discount(dyn_var<int>(discounts[i].value));
            }
        }
    }

    // Adjust product prices based on competitor offers, in parallel
    #pragma omp parallel for
    for (size_t i = 0; i < competitors.size(); ++i) {
        auto product = std::find_if(products.begin(), products.end(),
                                    [&](const Product &p) { return p.productID == competitors[i].product.productID; });
        if (product != products.end() && competitors[i].offerred_price < product->currentPrice) {
            product->currentPrice = competitors[i].offerred_price - 20; // Adjust price slightly below competitor
        }
    }

    // Apply additional discounts for loyal customers, in parallel
    #pragma omp parallel for
    for (size_t i = 0; i < customers.size(); ++i) {
        if (customers[i].loyalty_points > 100) {
            for (size_t j = 0; j < products.size(); ++j) {
                products[j].currentPrice *= 0.95; // Apply 5% discount for loyal customers
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

    // Extract the AST for `calculate_dynamic_price` function and generate C code
    auto ast = context.extract_function_ast(calculate_dynamic_price, "calculate_dynamic_price");
    block::c_code_generator::generate_code(ast, std::cout, 0);

    return 0;
}
