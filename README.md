# 🚚 Warehouse-to-Store Spare Parts Distribution System

This project simulates a **supply chain management system** for distributing spare parts from multiple warehouses to stores. It uses **graph algorithms** to ensure efficient logistics, minimize costs, and manage inventory dynamically.

---

## 🧠 Key Features

- 🗺️ **Shortest Path Calculation** using **Dijkstra's Algorithm** for optimal delivery routing.
- 🌐 **Minimum Spanning Tree (MST)** using **Kruskal’s Algorithm** to minimize total infrastructure cost.
- 📦 **Dynamic Inventory Management** for warehouses (stock levels, prices).
- 🏪 **Store Order Processing** with real-time decision-making.
- 🧪 **Random Order Simulation** for testing load and efficiency.
- 📊 **Order Statistics** tracking total orders and cost savings.

---

## 🛠️ Components

### ➕ SparePart Class
Represents an individual part with a name, quantity, and price.

### 🏬 Warehouse Class
- Holds an inventory of spare parts.
- Supports stock addition and real-time availability checking.

### 🏪 Store Class
- Basic store representation (ID + Name).
- Used to simulate order placement.

### 🔗 Graph Class
- Models the network of stores and warehouses.
- Dijkstra's algorithm helps determine the shortest delivery paths.

### 🧮 OrderProcessor
- Matches store orders with nearest warehouses having enough stock.
- Prioritizes by price and distance.
- Calculates total order cost and logs metrics.

### 🏗️ SupplyChainSystem
- Integrates all components.
- Loads data from files (`warehouses.txt`, `stores.txt`, `connections.txt`).
- Provides CLI for interaction (e.g., add warehouse/store, process orders, MST view, simulate orders).

---

## 🧪 Example Usage

```bash
$ ./supply_chain_app

=== Spare Parts Distribution System ===
1. Describe System
2. Show Warehouses
3. Show Stores
4. Process Order
5. Minimum Spanning Tree
6. Simulate Random Orders
7. Show Statistics
8. Add Warehouse
9. Add Store
10. Add Stock to Warehouse
11. Exit
