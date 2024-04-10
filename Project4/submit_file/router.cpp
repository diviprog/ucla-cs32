//
//  router.cpp
//  Project4
//
//  Created by Devansh Mishra on 12/03/24.
//

#include "router.h"
#include "geodb.h"
#include "geotools.h"
#include <queue>
#include <vector>
#include <unordered_map>
using namespace::std;

Router::Router(const GeoDatabaseBase& geo_db) : map(geo_db) {}

vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const {
        priority_queue<Node*, vector<Node*>, NodeComparator> openSet;
        unordered_map<string, Node*> allNodes; // Using string representation of GeoPoint as key

        Node* startNode = new Node(pt1, 0, heuristic(pt1, pt2), nullptr);
        openSet.push(startNode);
        allNodes[pt1.to_string()] = startNode;

        while (!openSet.empty()) {
            Node* current = openSet.top();
            openSet.pop();

            if (current->point.to_string() == pt2.to_string()) {
                vector<GeoPoint> path = reconstructPath(current);
                // Clean up dynamically allocated nodes
                for (auto& entry : allNodes) {
                    delete entry.second;
                }
                return path;
            }

            for (const GeoPoint& neighbor : map.get_connected_points(current->point)) {
                double tentative_g_score = current->g_score + distance_earth_miles(current->point, neighbor); // Use miles for consistency

                if (!allNodes.count(neighbor.to_string()) || tentative_g_score < allNodes[neighbor.to_string()]->g_score) {
                    Node* neighborNode = allNodes[neighbor.to_string()];
                    if (!neighborNode) {
                        neighborNode = new Node(neighbor, tentative_g_score, tentative_g_score + heuristic(neighbor, pt2), current);
                        allNodes[neighbor.to_string()] = neighborNode;
                        openSet.push(neighborNode);
                    } else {
                        neighborNode->g_score = tentative_g_score;
                        neighborNode->f_score = tentative_g_score + heuristic(neighbor, pt2);
                        neighborNode->parent = current;
                        // Since priority_queue doesn't support decrease-key operation, we push the updated node again.
                        openSet.push(neighborNode);
                    }
                }
            }
        }

        for (auto& entry : allNodes) {
            delete entry.second;
        }
        return {}; // No path found
    }

