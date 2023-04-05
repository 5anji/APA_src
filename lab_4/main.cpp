#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <iomanip>
#include <iostream>

using namespace boost;

int main() {
    typedef adjacency_list<vecS, vecS, undirectedS> Graph;

    Graph g;
    int num_vertices = 25;
    int num_edges = 24;

    // Add vertices to the graph
    for (size_t i = 0; i < num_vertices; i++) {
        add_vertex(g);
    }

    // Add edges to the graph
    for (size_t i = 0; i < num_edges; i++) {
        auto temp = ((i % 8 == 0) ? 0 : i);
        add_edge(temp, (i + 1) % num_vertices, g);
    }
    //  the graph will look like:
    //
    //            0
    //          / | \
    //         1  9 17
    //         2 10 18
    //         3 11 19
    //         4 12 20
    //         5 13 21
    //         6 14 22
    //         7 15 23
    //         8 16 24
    //
    // after all we will apply DFS & BFS

    // Print out the vertices and edges of the graph
    std::cout << "Vertices: ";
    for (auto vd : boost::make_iterator_range(vertices(g))) {
        std::cout << vd << " ";
    }
    std::cout << std::endl;

    std::cout << "Edges: ";
    for (auto ed : boost::make_iterator_range(edges(g))) {
        std::cout << "(" << source(ed, g) << "," << target(ed, g) << ") ";
    }
    std::cout << std::endl;

    // Run BFS on the graph
    std::vector<int> distances(num_vertices);
    clock_t start = clock();
    breadth_first_search(g, vertex(0, g), boost::visitor(boost::make_bfs_visitor(boost::record_distances(&distances[0], boost::on_tree_edge{}))));
    double timer = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken (BFS): " << std::fixed << std::setprecision(6) << timer << std::endl;

    std::cout << "BFS distances from vertex 0: ";
    for (size_t i = 0; i < num_vertices; i++) {
        std::cout << distances[i] << " ";
    }
    std::cout << std::endl;

    // Run DFS on the graph
    std::vector<int> visited(num_vertices);
    start = clock();
    depth_first_search(g, visitor(boost::make_dfs_visitor(boost::record_predecessors(&visited[0], boost::on_tree_edge{}))));
    timer = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken (DFS): " << std::fixed << std::setprecision(6) << timer << std::endl;

    std::cout << "DFS visited order: ";
    for (size_t i = 0; i < num_vertices; i++) {
        std::cout << visited[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}