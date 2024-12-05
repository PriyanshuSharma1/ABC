#include <iostream>
#include "pricely_impl.h"
#include "builder/builder_context.h"
#include "blocks/c_code_generator.h"

using namespace pricely;
using builder::builder_context;

int main() {
    // Initialize the builder context
    builder_context context;

    // Use the builder context to properly initialize and assign `dyn_var` fields
    try {
        // Initialize Product with dynamic variables within context scope
        Product product("P001", "Smartphone", 500.0f, 450.0f);
        product.basePrice = 500.0f;
        product.currentPrice = 450.0f;

        // Initialize DiscountRule within context scope
        DiscountRule discount("Holiday Sale", "percentage", 10, {"Electronics"}, "December");

        // Print Product details to check values
        std::cout << "Product ID: " << product.productID << "\n";
        std::cout << "Product Name: " << product.name << "\n";
        std::cout << "Base Price: " << static_cast<float>(product.basePrice) << "\n";
        std::cout << "Current Price after Discount: " << static_cast<float>(product.currentPrice) << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }

    return 0;
}
