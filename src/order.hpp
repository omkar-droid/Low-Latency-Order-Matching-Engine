// Order class

#pragma once
#include <cstdint>

enum class OrderType { LIMIT, MARKET, IOC };

struct Order {
    uint64_t orderId;  // Unique ID for the order
    bool isBuy;        // true = Buy, false = Sell
    double price;      // Price (ignored for market orders)
    uint32_t quantity; // Quantity to buy/sell
    OrderType type;    // Type of the order

    Order(uint64_t id, bool side, double p, uint32_t qty, OrderType t)
        : orderId(id), isBuy(side), price(p), quantity(qty), type(t) {}
};
