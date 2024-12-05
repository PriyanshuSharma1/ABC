#include <gtest/gtest.h>
#include "csv_loader.h"
#include "pricely_impl.h"

TEST(CSVLoaderTest, LoadProductsSuccess) {
    auto products = load_products("test_data/test_products.csv");
    ASSERT_FALSE(products.empty());
    EXPECT_EQ(products[0].name, "Sample Product");
    EXPECT_EQ(products[0].category, "Electronics");
}

TEST(CSVLoaderTest, LoadDiscountsSuccess) {
    auto discounts = load_discounts("test_data/test_discounts.csv");
    ASSERT_FALSE(discounts.empty());
    EXPECT_EQ(discounts[0].value, 10);
    EXPECT_TRUE(discounts[0].is_applicable("Electronics"));
}

TEST(CSVLoaderTest, LoadCompetitorsSuccess) {
    auto products = load_products("test_data/test_products.csv");
    auto competitors = load_competitors("test_data/test_competitors.csv", products);
    ASSERT_FALSE(competitors.empty());
    EXPECT_EQ(competitors[0].product.productID, products[0].productID);
    EXPECT_EQ(competitors[0].offerred_price, 90);
}

TEST(CSVLoaderTest, LoadCustomersSuccess) {
    auto customers = load_customers("test_data/test_customers.csv");
    ASSERT_FALSE(customers.empty());
    EXPECT_EQ(customers[0].loyalty_points, 120);
}

TEST(DynamicPriceTest, ApplyDiscounts) {
    Product product = {"1", "Sample Product", "Electronics", 100};
    DiscountRule discount = {"Electronics", 10};
    ASSERT_TRUE(discount.is_applicable(product.category));
    product.apply_discount(discount.value);
    EXPECT_EQ(product.currentPrice, 90);
}
