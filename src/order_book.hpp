// OrderBook header

#pragma once
#include "order.hpp"
#include "trade.hpp"
#include <map>
#include <list>
#include <vector>

class OrderBook {
public:
    OrderBook();

    std::vector<Trade> addOrder(Order order); // Add a new order and try to match
    bool cancelOrder(uint64_t orderId);        // Cancel an existing order
    void printOrderBook() const;               // For debugging

private:
    using OrderList = std::list<Order>;
    using PriceMap = std::map<double, OrderList>;

    PriceMap bids; // buy orders
    PriceMap asks; // sell orders
    uint64_t nextTradeId = 1;

    std::vector<Trade> matchOrder(Order& incomingOrder);
};
