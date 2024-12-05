#include <iostream>
#include "pricely_impl.h"
#include "csv_loader.h" // Include the CSV loader header
#include "builder/builder_context.h"
#include "blocks/c_code_generator.h"
#include <vector>
#include <string>

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

    // Apply discounts to products if applicable
    for (const auto &discount : discounts) {
        for (auto &product : products) {
            if (discount.is_applicable("Electronics")) { // Adjust category as needed
                product.apply_discount(dyn_var<int>(discount.value));
            }
        }
    }

    // Adjust product prices based on competitor offers
    for (const auto &competitor : competitors) {
        auto product = std::find_if(products.begin(), products.end(),
                                    [&](const Product &p) { return p.productID == competitor.product.productID; });
        if (product != products.end() && competitor.offerred_price < product->currentPrice) {
            product->currentPrice = competitor.offerred_price - 20;
        }
    }

    // Apply additional discounts for loyal customers
    for (const auto &customer : customers) {
        if (customer.loyalty_points > 100) {
            for (auto &product : products) {
                product.currentPrice *= 0.95;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    builder::builder_context context;
    std::cout << "Starting dynamic pricing calculation..." << std::endl;

    auto ast = context.extract_function_ast(calculate_dynamic_price, "calculate_dynamic_price");
    block::c_code_generator::generate_code(ast, std::cout, 0);

    return 0;
}
