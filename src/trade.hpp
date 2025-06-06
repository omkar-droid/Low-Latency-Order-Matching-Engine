// Trade class

#pragma once
#include <cstdint>

struct Trade {
    uint64_t tradeId;     // Unique ID for the trade
    uint64_t buyOrderId;  // Which buy order matched
    uint64_t sellOrderId; // Which sell order matched
    double price;         // Price at which trade happened
    uint32_t quantity;    // Quantity traded

    Trade(uint64_t tid, uint64_t buyId, uint64_t sellId, double p, uint32_t qty)
        : tradeId(tid), buyOrderId(buyId), sellOrderId(sellId), price(p), quantity(qty) {}
};
