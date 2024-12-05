#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include <vector>
#include <string>
#include "pricely_impl.h"  // For Product, DiscountRule, Competitor, Customer classes
using namespace pricely;

// Function declarations
std::vector<Product> load_products(const std::string &filename);
std::vector<DiscountRule> load_discounts(const std::string &filename);
std::vector<Competitor> load_competitors(const std::string &filename, const std::vector<Product> &products);
std::vector<Customer> load_customers(const std::string &filename);

#endif // CSV_LOADER_H
