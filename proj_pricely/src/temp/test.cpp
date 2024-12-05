// Include the headers
#include "blocks/c_code_generator.h"
#include "builder/static_var.h"
#include "builder/dyn_var.h"
#include <iostream>

// Include the BuildIt types
using builder::dyn_var;
using builder::static_var;



// The power function to stage
dyn_var<int> power(dyn_var<int> base, static_var<int> exponent) {
    dyn_var<int> res = 1, x = base;
    while (exponent > 1) {
        if (exponent % 2 == 1)
            res = res * x;
        x = x * x;
        exponent = exponent / 2;
    }
    return res * x;
}

// The main driver function 
int main(int argc, char* argv[]) {
    // Declare the context object
    builder::builder_context context;
    
    // Generate the AST for the next stage
    // The exponent can also be a command line argument, constant for simplicity
    auto ast = context.extract_function_ast(power, "power_15", 15);
    
    // Generate the headers for the next stage
    std::cout << "#include <stdio.h>" << std::endl;
    block::c_code_generator::generate_code(ast, std::cout, 0);
    
    
    // Print the main function for the next stage manually
    // Can also be generated using BuildIt, but we will skip for simplicity
    std::cout << "int main(int argc, char* argv[]) {\n    printf(\"2 ^ 15 = %d\\n\", power_15(2));\n    return 0;\n}" << std::endl;
    
    return 0;
}
