#include <iostream>
#include "product.h"
#include "builder/builder_context.h"
#include "blocks/c_code_generator.h"

using builder::dyn_var;
using builder::static_var;

// Apply a discount on the product and return the updated price
dyn_var<float> applyDiscount(dyn_var<Product> p, int discount_percent) {
    p.currentPrice = p.currentPrice - (discount_percent / 100.0f) * p.currentPrice;
    return p.currentPrice;
}

int main(int argc, char* argv[]) {
    builder::builder_context context;

    // Extract function AST for the discount application with builder context
    auto ast = context.extract_function_ast(
        [](dyn_var<Product> p) {
            p.productID = "A01";       // Regular string assignment
            p.name = "Santoor";        // Regular string assignment
            p.basePrice = 100.0f;
            p.currentPrice = 120.0f;
            return applyDiscount(p, 5);
        },
        "apply_discount"
    );

    // Generate C code for the AST
    std::cout << "#include <stdio.h>" << std::endl;
    block::c_code_generator::generate_code(ast, std::cout, 0);

    return 0;
}
