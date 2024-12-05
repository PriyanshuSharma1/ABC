# Dynamic Pricing System

## Project Overview
The Dynamic Pricing System is designed to calculate product prices dynamically by considering various factors, including:

1. **Discounts**: Specific discounts applied to product categories.
2. **Competitors' Prices**: Adjusting prices based on competitor offerings.
3. **Customer Loyalty**: Additional discounts for loyal customers.

The system processes input data from CSV files containing products, discounts, competitors, and customer information. It performs calculations in parallel to improve performance and generates a final pricing report.

---

## Features

- **Dynamic Discount Application**: Discounts are applied to products based on predefined rules.
- **Competitor Price Adjustments**: Prices are adjusted to stay competitive.
- **Loyalty Discounts**: Special pricing for customers with high loyalty points.
- **Parallel Processing**: Uses OpenMP to optimize performance for large datasets.
- **Code Generation**: Extracts the Abstract Syntax Tree (AST) of the pricing function and generates C code.

---

## Limitations

1. **Limited Error Handling**:
   - Missing or corrupt CSV files cause the system to terminate early.
   - No detailed logs for debugging file format errors or missing fields.

2. **Simplistic Pricing Adjustments**:
   - Prices are adjusted linearly and lack support for complex discounting strategies.
   - Fixed competitor offset (`-20`) does not account for varied pricing strategies.

3. **No Real-Time Updates**:
   - The system processes data in batches from static CSV files, limiting its use in real-time pricing scenarios.

4. **Scalability Constraints**:
   - Performance depends on the number of threads available and the size of the dataset.
   - Single-node parallelism limits scalability for very large datasets.

5. **Testing Coverage**:
   - Manual testing is limited and lacks an automated testing framework.
   - Google Test (GTest) integration is optional but not fully implemented.

---

## Future Enhancements

1. **Improved Error Handling**:
   - Add detailed logging for data loading and processing errors.
   - Validate CSV formats and provide meaningful error messages.

2. **Advanced Pricing Algorithms**:
   - Implement machine learning models to predict optimal pricing strategies.
   - Support for tiered discounts, bundling, and seasonal pricing adjustments.

3. **Real-Time Pricing Engine**:
   - Integrate with APIs to fetch real-time competitor data and customer interactions.
   - Enable live updates to product prices.

4. **Scalability Improvements**:
   - Utilize distributed computing frameworks (e.g., MPI, Spark) for larger datasets.
   - Optimize memory usage for handling extensive product catalogs.

5. **Enhanced Testing**:
   - Integrate a robust testing framework like Google Test for automated unit and integration tests.
   - Add test cases for edge scenarios, such as empty datasets and invalid inputs.

6. **User Interface**:
   - Develop a web-based or command-line interface for managing products, discounts, and pricing reports.

---

## How to Run

### Prerequisites
- **C++ Compiler**: Requires `g++` with C++11 support.
- **Dependencies**: Ensure all required dependencies are in the `deps/` folder and built.
- **OpenMP**: Ensure OpenMP support is enabled in your compiler.

### Compilation
Use the provided `Makefile` to compile the project:

```bash
make
```

### Execution
Run the compiled executable:

```bash
./build/main
```

### Testing
Run manual or automated tests:

```bash
make test
./build/test_pricely
```

---

## Project Structure
```
proj_pricely/
├── build/                  # Build directory
├── data/                   # Input data (products, discounts, competitors, customers)
├── deps/                   # Dependencies (e.g., BuildIt)
├── include/                # Header files
├── src/                    # Source code
├── test/                   # Test files
├── test_data/              # Test CSV files
├── Makefile                # Build and test rules
└── README.md               # Project documentation
```

---

## Contributors
- **[Your Name Here]**

Feel free to contribute to the project by submitting pull requests or reporting issues!

