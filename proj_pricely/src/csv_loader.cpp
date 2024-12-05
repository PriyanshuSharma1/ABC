#include "../include/csv_loader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<Product> load_products(const std::string &filename) {
    std::vector<Product> products;
    std::ifstream file(filename);
    std::string line;
    

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string productID, name;
        float basePrice, currentPrice;

        if (std::getline(ss, productID, ',') && std::getline(ss, name, ',') &&
            ss >> basePrice && ss.ignore() && ss >> currentPrice) {
            products.emplace_back(productID, name, basePrice, currentPrice);
        }
    }

    return products;
}

std::vector<DiscountRule> load_discounts(const std::string &filename) {
    std::vector<DiscountRule> discounts;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string description, discountType, validityPeriod;
        int value;
        std::vector<std::string> categories;
        std::string category;

        if (std::getline(ss, description, ',') && std::getline(ss, discountType, ',') &&
            ss >> value && ss.ignore() && std::getline(ss, validityPeriod, ',')) {
            while (std::getline(ss, category, ',')) {
                categories.push_back(category);
            }
            discounts.emplace_back(description, discountType, value, categories, validityPeriod);
        }
    }

    return discounts;
}

std::vector<Competitor> load_competitors(const std::string &filename, const std::vector<Product> &products) {
    std::vector<Competitor> competitors;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string competitorID, productID;
        float offeredPrice;

        if (std::getline(ss, competitorID, ',') && std::getline(ss, productID, ',') &&
            ss >> offeredPrice) {
            auto product = std::find_if(products.begin(), products.end(),
                                        [&](const Product &p) { return p.productID == productID; });
            if (product != products.end()) {
                competitors.emplace_back(competitorID, *product, offeredPrice);
            }
        }
    }

    return competitors;
}

std::vector<Customer> load_customers(const std::string &filename) {
    std::vector<Customer> customers;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string customerID, name;
        float loyaltyPoints;

        if (std::getline(ss, customerID, ',') && std::getline(ss, name, ',') &&
            ss >> loyaltyPoints) {
            customers.emplace_back(customerID, name, loyaltyPoints);
        }
    }

    return customers;
}
