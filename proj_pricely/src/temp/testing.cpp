#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "pricely_impl.h"
#include "builder/builder_context.h"
#include "blocks/c_code_generator.h"

using namespace pricely;
using builder::builder_context;

// Function to read products from CSV file
std::vector<Product> read_products_from_file(const std::string& filename) {
    std::vector<Product> products;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return products;
    }

    std::string line;
    bool header = true;
    while (std::getline(file, line)) {
        if (header) {  // Skip the header line
            header = false;
            continue;
        }

        std::stringstream ss(line);
        std::string productID, name, basePriceStr, currentPriceStr;

        // Parse each value
        std::getline(ss, productID, ',');
        std::getline(ss, name, ',');
        std::getline(ss, basePriceStr, ',');
        std::getline(ss, currentPriceStr, ',');

        // Convert price strings to float
        float basePrice = std::stof(basePriceStr);
        float currentPrice = std::stof(currentPriceStr);

        // Create Product instance and add to the vector
        products.emplace_back(productID, name, basePrice, currentPrice);
    }

    file.close();
    return products;
}

int main() {
    // Activate builder context at the very beginning
    builder_context context;

    // Read product data from file and create instances
    std::vector<Product> products = read_products_from_file("products.csv");

    // Process each product
    for (auto& product : products) {
        std::cout << "Product ID: " << product.productID << "\n";
        std::cout << "Product Name: " << product.name << "\n";
        std::cout << "Base Price: " << static_cast<float>(product.basePrice) << "\n";
        std::cout << "Current Price: " << static_cast<float>(product.currentPrice) << "\n";

        // Apply discount to the product
        product.apply_discount(10);  // Apply a 10% discount
        std::cout << "Current Price after Discount: " << static_cast<float>(product.currentPrice) << "\n";
    }

    return 0;
}
