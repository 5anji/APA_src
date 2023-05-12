#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>
#include <iomanip>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

// Define the graph type
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, uint64_t>> Graph;

// Function to run Dijkstra's algorithm
void dijkstra_shortest_paths(const Graph& graph, uint64_t source) {
    std::vector<uint64_t> distance(boost::num_vertices(graph));
    std::vector<Graph::vertex_descriptor> predecessor(boost::num_vertices(graph));

    boost::dijkstra_shortest_paths(graph, source, boost::predecessor_map(&predecessor[0]).distance_map(&distance[0]));

    // std::cout << "Dijkstra Shortest Paths:\n";
    // for (uint64_t i = 0; i < boost::num_vertices(graph); ++i) {
    //     std::cout << "Distance from " << source << " to " << i << ": " << distance[i] << std::endl;
    // }
}

// Function to run Floyd-Warshall algorithm
void floyd_warshall_shortest_paths(const Graph& graph) {
    std::vector<std::vector<uint64_t>> distance(boost::num_vertices(graph), std::vector<uint64_t>(boost::num_vertices(graph)));

    boost::floyd_warshall_all_pairs_shortest_paths(graph, distance);

    // std::cout << "Floyd-Warshall Shortest Paths:\n";
    // for (uint64_t i = 0; i < boost::num_vertices(graph); ++i) {
    //     for (uint64_t j = 0; j < boost::num_vertices(graph); ++j) {
    //         std::cout << "Distance from " << i << " to " << j << ": " << distance[i][j] << std::endl;
    //     }
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
    for (size_t i = 10; i <= 100000; i *= 10) {
        // Create a graph
        std::cout << "Calculate for " << i << " elements:" << std::endl;
        Graph graph(generateRandomGraph(i));

        // Run Dijkstra's algorithm from vertex 0
        clock_t start = clock();
        dijkstra_shortest_paths(graph, 0);
        double timer = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
        std::cout << "Time taken (Dijkstra): " << std::fixed << std::setprecision(6) << timer << std::endl;

        // Run Floyd-Warshall algorithm
        start = clock();
        floyd_warshall_shortest_paths(graph);
        timer = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
        std::cout << "Time taken (Floyd-Warshall): " << std::fixed << std::setprecision(6) << timer << std::endl;

        std::cout << std::endl;
    }
    return 0;
}
