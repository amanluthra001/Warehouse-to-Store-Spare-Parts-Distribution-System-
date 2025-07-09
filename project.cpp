#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>
#include <tuple>
#include <set>
#include <fstream>
#include <sstream>
#include <random>
#include <ctime>
#include <functional>

using namespace std;

const int INF = INT_MAX;

// spare part with name quantity and price
class SparePart {
public:
    string name;
    int quantity;
    double price;

    SparePart(string n = "", int q = 0, double p = 0.0)
        : name(n), quantity(q), price(p) {}
};

// warehouse class
class Warehouse {
public:
    int id;
    string name;
    unordered_map<string, SparePart> inventory;

    Warehouse(int i = 0, string n = "") : id(i), name(n) {}

    void addSparePart(const SparePart& part) {
        inventory[part.name] = part;
    }

    bool hasPart(const string& partName, int qty) {
        return inventory.count(partName) && inventory[partName].quantity >= qty;
    }

    void reduceStock(const string& partName, int qty) {
        inventory[partName].quantity -= qty;
    }

    void displayInventory() {
        cout << "Warehouse ID: " << id << ", Name: " << name << "\n";
        for (auto& [name, part] : inventory) {
            cout << "  " << part.name << " Qty: " << part.quantity << " Price: " << part.price << "\n";
        }
    }
};

// Store class
class Store {
public:
    int id;
    string name;

    Store(int i = 0, string n = "") : id(i), name(n) {}

    void display() {
        cout << "Store ID: " << id << ", Name: " << name << "\n";
    }
};

// Graph class
class Graph {
public:
    int V;
    vector<vector<pair<int, int>>> adj;

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int weight) {
        adj[u].emplace_back(v, weight);
        adj[v].emplace_back(u, weight);
    }

    vector<int> dijkstra(int src) {
        vector<int> dist(V, INF);
        dist[src] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, src);

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u]) continue;

            for (auto& [v, w] : adj[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }
        return dist;
    }
};

// Edge class for MST
struct Edge {
    int from, to;
    int distance;
    int cost;

    bool operator<(const Edge& e) const {
        return cost < e.cost;
    }
};

// OrderProcessor class
class OrderProcessor {
public:
    int totalOrders = 0;
    double totalCostSaved = 0.0;

    void processOrder(int storeId, const string& partName, int quantity,
                      vector<Warehouse>& warehouses, Graph& graph) {
        cout << "\nProcessing order for Store " << storeId << ": "
             << partName << " x" << quantity << "\n";

        vector<tuple<int, int, double>> candidates;
        auto dist = graph.dijkstra(storeId);

        for (auto& w : warehouses) {
            if (w.hasPart(partName, quantity)) {
                candidates.emplace_back(w.id, dist[w.id], w.inventory[partName].price);
            }
        }

        if (candidates.empty()) {
            cout << "No warehouse has enough stock!\n";
            return;
        }

        sort(candidates.begin(), candidates.end(), [](auto& a, auto& b) {
            return tie(get<2>(a), get<1>(a)) < tie(get<2>(b), get<1>(b));
        });

        auto [wid, d, p] = candidates[0];
        warehouses[wid].reduceStock(partName, quantity);
        double cost = p * quantity;
        totalCostSaved += cost;

        cout << "Order fulfilled from Warehouse " << wid << "\n";
        cout << "Price/unit: " << p << ", Distance: " << d << ", Total cost: " << cost << "\n";
        totalOrders++;
    }

    void reportStatistics() {
        cout << "\n=== Order Statistics ===\n";
        cout << "Total Orders Processed: " << totalOrders << "\n";
        cout << "Total Cost of Orders: " << totalCostSaved << "\n";
    }
};

// SupplyChainSystem class
class SupplyChainSystem {
    vector<Warehouse> warehouses;
    vector<Store> stores;
    vector<Edge> edges;
    Graph* graph;
    OrderProcessor orderProcessor;

public:
    SupplyChainSystem(int V) {
        graph = new Graph(V);
    }

   void describeSystem() {

        cout << "\n=== System Description ===\n";
        cout << "This Spare Parts Distribution System aims to optimize logistics between warehouses and stores.\n";
        cout << "Key objectives include minimizing delivery cost and time while maintaining stock efficiency.\n\n";

        cout << "Core components and algorithms used:\n";
        cout << "1. *Dijkstra's Algorithm* - Finds the shortest path from a warehouse to a store,\n";
        cout << "   ensuring minimum transportation distance and time.\n";
        cout << "2. *Kruskal's Algorithm (MST)* - Builds a cost-effective transportation network\n";
        cout << "   by connecting nodes (warehouses/stores) with minimal total cost.\n";
        cout << "3. *Dynamic Inventory Management* - Manages spare part availability and pricing\n";
        cout << "   across different warehouses, ensuring accurate order fulfillment.\n\n";

        cout << "The system integrates real-time decision-making with algorithmic efficiency\n";
        cout << "to support businesses in scalable and cost-effective operations.\n";

}


    void loadWarehouses(const string& filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            int id; string name;
            iss >> id >> name;
            Warehouse w(id, name);
            int numParts;
            iss >> numParts;
            for (int i = 0; i < numParts; ++i) {
                string partName; int qty; double price;
                iss >> partName >> qty >> price;
                w.addSparePart(SparePart(partName, qty, price));
            }
            warehouses.push_back(w);
        }
    }

    void loadStores(const string& filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            int id; string name;
            iss >> id >> name;
            stores.emplace_back(id, name);
        }
    }

    void loadConnections(const string& filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            int u, v, dist, cost;
            iss >> u >> v >> dist >> cost;
            graph->addEdge(u, v, dist);
            edges.push_back({u, v, dist, cost});
        }
    }

    void showWarehouses() {
        for (auto& w : warehouses) w.displayInventory();
    }

    void showStores() {
        for (auto& s : stores) s.display();
    }

    void processOrder(int storeId, const string& partName, int quantity) {
        orderProcessor.processOrder(storeId, partName, quantity, warehouses, *graph);
    }
    void addWarehouse() {
    int id;
    string name;
    cout << "Enter Warehouse ID and Name: ";
    cin >> id >> name;
    warehouses.emplace_back(id, name);
    cout << "Warehouse added.\n";
}

void addStore() {
    int id;
    string name;
    cout << "Enter Store ID and Name: ";
    cin >> id >> name;
    stores.emplace_back(id, name);
    cout << "Store added.\n";
}

void addStock() {
    int wid;
    string partName;
    int qty;
    double price;
    cout << "Enter Warehouse ID: ";
    cin >> wid;
    cout << "Enter Part Name, Quantity, Price: ";
    cin >> partName >> qty >> price;

    auto it = find_if(warehouses.begin(), warehouses.end(),[&](Warehouse& w)
            {
                return w.id == wid;
            }
            );

    if (it != warehouses.end()) {
        it->addSparePart(SparePart(partName, qty, price));
        cout << "Stock added to warehouse.\n";
    } else {
        cout << "Warehouse not found.\n";
    }
}

    void minimumSpanningTree() {
        sort(edges.begin(), edges.end());
        vector<int> parent(graph->V);
        for (int i = 0; i < graph->V; i++) parent[i] = i;

        function<int(int)> find;
        find=[&](int u) {
            if(parent[u]!=u)
            {
                parent[u]=find(parent[u]);
            }
            return parent[u];
        };
        int totalCost = 0;
        cout << "\nMinimum Spanning Tree:\n";
        for (auto& e : edges) {
            int u = find(e.from);
            int v = find(e.to);
            if (u != v) {
                cout << "Edge: " << e.from << "-" << e.to << " Cost: " << e.cost << "\n";
                totalCost += e.cost;
                parent[u] = v;
            }
        }
        cout << "Total MST Cost: " << totalCost << "\n";
    }

    void simulateRandomOrders(int numOrders) {
        if (stores.empty() || warehouses.empty()) {
            cout << "Load data first!\n";
            return;
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> storeDist(0, stores.size() - 1);
        uniform_int_distribution<> partDist(0, warehouses[0].inventory.size() - 1);
        uniform_int_distribution<> qtyDist(1, 5);

        vector<string> partNames;
        for (auto& p : warehouses[0].inventory)
            partNames.push_back(p.first);

        for (int i = 0; i < numOrders; i++) {
            int storeId = stores[storeDist(gen)].id;
            string part = partNames[partDist(gen)];
            int qty = qtyDist(gen);
            processOrder(storeId, part, qty);
        }
    }

    void reportStatistics() {
        orderProcessor.reportStatistics();
    }

    ~SupplyChainSystem() {
        delete graph;
    }
};

// Menu
void printMenu() {
    cout << "\n=== Spare Parts Distribution System ===\n";
    cout << "1. Describe System\n";
    cout << "2. Show Warehouses\n";
    cout << "3. Show Stores\n";
    cout << "4. Process Order\n";
    cout << "5. Minimum Spanning Tree\n";
    cout << "6. Simulate Random Orders\n";
    cout << "7. Show Statistics\n";
    cout << "8. Add Warehouse\n";
    cout << "9. Add Store\n";
    cout << "10. Add Stock to Warehouse\n";
    cout << "11. Exit\n";
    cout << "Enter choice: ";
}


int main() {
    SupplyChainSystem system(10);

    system.loadWarehouses("warehouses.txt");
    system.loadStores("stores.txt");
    system.loadConnections("connections.txt");

    int choice;
while (true) {
    printMenu();
    cin >> choice;

    if (choice == 1) {
        system.describeSystem();
    }
    else if (choice == 2) {
        system.showWarehouses();
    }
    else if (choice == 3) {
        system.showStores();
    }
    else if (choice == 4) {
        int storeId, qty;
        string partName;
        cout << "Enter Store ID, Part Name, Quantity: ";
        cin >> storeId >> partName >> qty;
        system.processOrder(storeId, partName, qty);
    }
    else if (choice == 5) {
        system.minimumSpanningTree();
    }
    else if (choice == 6) {
        int num;
        cout << "Enter number of random orders: ";
        cin >> num;
        system.simulateRandomOrders(num);
    }
    else if (choice == 7) {
        system.reportStatistics();
    }
    else if (choice == 8) {
        system.addWarehouse();
    }
    else if (choice == 9) {
        system.addStore();
    }
    else if (choice == 10) {
        system.addStock();
    }

    else if (choice == 11) {
        break;
    }
    else {
        cout << "Invalid choice!\n";
    }
}
return 0;
}
