// OrderBook implementation
#include "order_book.hpp"
#include <iostream>

OrderBook::OrderBook() {}

std::vector<Trade> OrderBook::addOrder(Order order) {
    std::vector<Trade> trades = matchOrder(order);

    if (order.quantity > 0 && order.type == OrderType::LIMIT) {
        if (order.isBuy) {
            bids[order.price].push_back(order);
        } else {
            asks[order.price].push_back(order);
        }
    }
    return trades;
}

bool OrderBook::cancelOrder(uint64_t orderId) {
    for (auto side : { &bids, &asks }) {
        for (auto& [price, orders] : *side) {
            for (auto it = orders.begin(); it != orders.end(); ++it) {
                if (it->orderId == orderId) {
                    orders.erase(it);
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<Trade> OrderBook::matchOrder(Order& incomingOrder) {
    std::vector<Trade> trades;
    auto& side = incomingOrder.isBuy ? asks : bids;

    for (auto it = side.begin(); it != side.end();) {
        bool priceMatch = incomingOrder.isBuy ? (incomingOrder.price >= it->first) : (incomingOrder.price <= it->first);

        if ((incomingOrder.type == OrderType::MARKET || priceMatch) && incomingOrder.quantity > 0) {
            auto& ordersAtLevel = it->second;

            for (auto orderIt = ordersAtLevel.begin(); orderIt != ordersAtLevel.end() && incomingOrder.quantity > 0;) {
                uint32_t matchQty = std::min(incomingOrder.quantity, orderIt->quantity);

                trades.emplace_back(nextTradeId++, 
                                    incomingOrder.isBuy ? incomingOrder.orderId : orderIt->orderId,
                                    incomingOrder.isBuy ? orderIt->orderId : incomingOrder.orderId,
                                    orderIt->price,
                                    matchQty);

                incomingOrder.quantity -= matchQty;
                orderIt->quantity -= matchQty;

                if (orderIt->quantity == 0) {
                    orderIt = ordersAtLevel.erase(orderIt);
                } else {
                    ++orderIt;
                }
            }

            if (ordersAtLevel.empty()) {
                it = side.erase(it);
            } else {
                ++it;
            }
        } else {
            break;
        }
    }

    return trades;
}

void OrderBook::printOrderBook() const {
    std::cout << "--- Order Book ---\n";
    std::cout << "Bids:\n";
    for (auto it = bids.rbegin(); it != bids.rend(); ++it) {
        for (const auto& o : it->second) {
            std::cout << "Buy " << o.quantity << " @ " << o.price << "\n";
        }
    }
    std::cout << "Asks:\n";
    for (auto it = asks.begin(); it != asks.end(); ++it) {
        for (const auto& o : it->second) {
            std::cout << "Sell " << o.quantity << " @ " << o.price << "\n";
        }
    }
}
