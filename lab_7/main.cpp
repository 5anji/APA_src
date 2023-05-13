#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, int>>
        Graph;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;

void primMST(const Graph& graph) {
    std::vector<Vertex> p(boost::num_vertices(graph));
    boost::prim_minimum_spanning_tree(graph, &p[0]);

    // std::cout << "Prim's Minimum Spanning Tree:\n";
    // for (std::size_t i = 0; i < p.size(); ++i) {
    //     if (p[i] != boost::graph_traits<Graph>::null_vertex()) {
    //         std::cout << "Edge: " << p[i] << " - " << i << "\n";
    //     }
    // }
}

void kruskalMST(const Graph& graph) {
    std::vector<Edge> mst;
    boost::kruskal_minimum_spanning_tree(graph, std::back_inserter(mst));

    // std::cout << "Kruskal's Minimum Spanning Tree:\n";
    // for (const auto& edge : mst) {
    //     std::cout << "Edge: " << boost::source(edge, graph) << " - " << boost::target(edge, graph) << "\n";
    // }
}

Graph generateRandomGraph(uint64_t limit) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, limit);

    Graph graph;

    uint64_t numVertices = dis(gen);
    uint64_t numEdges = dis(gen);

    for (uint64_t i = 0; i < numVertices; ++i)
        boost::add_vertex(graph);

    std::vector<std::pair<uint64_t, uint64_t>> edges;

    while (edges.size() < numEdges) {
        uint64_t source = dis(gen) % numVertices;
        uint64_t target = dis(gen) % numVertices;

        if (source != target)
            edges.push_back(std::make_pair(source, target));
    }

    for (const auto& edge : edges)
        boost::add_edge(edge.first, edge.second, graph);

    return graph;
}

int main() {
    for (size_t i = 10; i <= 10000000; i *= 10) {
        // Create a graph
        std::cout << "Calculate for " << i << " elements:" << std::endl;
        Graph graph(generateRandomGraph(i));

        // Run Prim's algorithm from vertex 0
        clock_t start = clock();
        primMST(graph);
        double timer = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
        std::cout << "Time taken (Prim): " << std::fixed << std::setprecision(6) << timer << std::endl;

        // Run Kruskal algorithm
        start = clock();
        kruskalMST(graph);
        timer = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
        std::cout << "Time taken (Kruskal): " << std::fixed << std::setprecision(6) << timer << std::endl;

        std::cout << std::endl;
    }
    return 0;
}
