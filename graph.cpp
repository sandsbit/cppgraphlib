/**
 * This file is part of cppgraphlib.
 *
 *  cppgraphlib is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of
 *  the License, or (at your option) any later version.
 *
 *  cppgraphlib is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  and GNU Lesser General Public License along with cppgraphlib.  If not,
 *  see <https://www.gnu.org/licenses/>.
 */

#include "graph.h"

cgl::Graph::Graph() {
    edges = 0;
    connected = true;
    weighted = false;
    tree = true;
    complete = true;
    directed = false;
    loops = false;
    null = true;
    empty = true;
    integer = true;
}

void cgl::Graph::set(const cgl::graph_t &g) {
    graph = g;
    weighted = true;
    null = g.empty();
    integer = false;
}

void cgl::Graph::set(const cgl::intgraph_t &g) {
    size_t n = g.size();
    for (int i = 0; i < n; ++i) {
        size_t con = g[i].size();
        for (int j = 0; j < con; ++j) {
            graph[i].emplace_back(g[i][j].first, (double) g[i][j].second);
        }
    }

    weighted = true;
    null = n == 0;
    integer = true;
}

void cgl::Graph::set(const cgl::nwgraph_t &g) {
    size_t n = g.size();
    for (int i = 0; i < n; ++i) {
        size_t con = g[i].size();
        for (int j = 0; j < con; ++j) {
            graph[i].emplace_back(g[i][j], 1.0);
        }
    }

    weighted = false;
    null = n == 0;
    integer = true;
}

cgl::Graph::Graph(const cgl::nwgraph_t &g) {
    set(g);
}

cgl::Graph::Graph(const cgl::graph_t &g) {
    set(g);
}

cgl::Graph::Graph(const cgl::intgraph_t &g) {
    set(g);
}

cgl::Graph &cgl::Graph::operator=(const cgl::nwgraph_t &g) {
    set(g);
    return *this;
}

cgl::Graph &cgl::Graph::operator=(const cgl::graph_t &g) {
    set(g);
    return *this;
}

cgl::Graph &cgl::Graph::operator=(const cgl::intgraph_t &g) {
    set(g);
    return *this;
}

cgl::graph_t cgl::Graph::getGraph() const {
    return graph;
}

std::vector<std::pair<size_t, double>> cgl::Graph::connectedWith(size_t n) const {
    return graph[n];
}

size_t cgl::Graph::numberOfVertices() const {
    return graph.size();
}

size_t cgl::Graph::numberOfEdges() const {
    if (edges) {
        return *edges;
    } else {
        int c = 0;
        for (auto i = std::begin(graph); i != std::end(graph); ++i) {
            int ver = i - std::begin(graph);
            for (auto j = std::begin(*i); j != std::end(*i); ++j) {
                if (j->first >= ver)
                    c++;
            }
        }
        return c;
    }
}

bool cgl::Graph::isWeighted() const {
    return weighted;
}

bool cgl::Graph::isNull() const {
    return null;
}

bool cgl::Graph::isInteger() const {
    return integer;
}

void cgl::Graph::connect(size_t a, size_t b) {
    graph[a].emplace_back(b, 1);
    graph[b].emplace_back(a, 1);
    if (connected && !*connected)
        connected = std::nullopt;
    if (tree && *tree)
        tree = false;
    else if (tree)
        tree = std::nullopt;
    complete = std::nullopt;
    null = false;
    empty = false;
}

void cgl::Graph::connect(size_t a, size_t b, double w) {
    graph[a].emplace_back(b, w);
    graph[b].emplace_back(a, w);
    if (connected && !*connected)
        connected = std::nullopt;
    if (tree && *tree)
        tree = false;
    else if (tree)
        tree = std::nullopt;
    complete = std::nullopt;
    weighted = true;
    integer = false;
    null = false;
    empty = false;
}

void cgl::Graph::connect(size_t a, size_t b, int i) {
    graph[a].emplace_back(b, i);
    graph[b].emplace_back(a, i);
    if (connected && !*connected)
        connected = std::nullopt;
    if (tree && *tree)
        tree = false;
    else if (tree)
        tree = std::nullopt;
    complete = std::nullopt;
    weighted = true;
    null = false;
    empty = false;
}

void cgl::Graph::connecto(size_t a, size_t b) {
    graph[a].emplace_back(b, 1);
    if (connected && !*connected)
        connected = std::nullopt;
    if (tree && *tree)
        tree = false;
    else if (tree)
        tree = std::nullopt;
    complete = std::nullopt;
    directed = true;
    null = false;
    empty = false;
}

void cgl::Graph::connecto(size_t a, size_t b, double w) {
    graph[a].emplace_back(b, w);
    if (connected && !*connected)
        connected = std::nullopt;
    if (tree && *tree)
        tree = false;
    else if (tree)
        tree = std::nullopt;
    complete = std::nullopt;
    weighted = true;
    integer = false;
    directed = true;
    null = false;
    empty = false;
}

void cgl::Graph::connecto(size_t a, size_t b, int i) {
    graph[a].emplace_back(b, i);
    if (connected && !*connected)
        connected = std::nullopt;
    if (tree && *tree)
        tree = false;
    else if (tree)
        tree = std::nullopt;
    complete = std::nullopt;
    weighted = true;
    directed = true;
    null = false;
    empty = false;
}
