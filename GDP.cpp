#include <bits/stdc++.h>
using namespace std;

struct Area {
    int id;
    int population;     // people affected
    int distance;       // distance from base
    int resourceNeed;   // resources required
    int urgency;        // urgency level
};

// Function to display areas
void displayAreas(vector<Area> &areas) {
    cout << "\n--- Areas Information ---\n";
    for (auto &a : areas) {
        cout << "Area " << a.id
             << " | Pop: " << a.population
             << " | Dist: " << a.distance
             << " | Need: " << a.resourceNeed
             << " | Urgency: " << a.urgency << endl;
    }
}

// Greedy: Sort areas by priority (urgency / distance)
void greedyPriority(vector<Area> &areas) {
    sort(areas.begin(), areas.end(), [](Area a, Area b) {
        double p1 = (double)a.urgency / a.distance;
        double p2 = (double)b.urgency / b.distance;
        return p1 > p2;
    });
}

// DP: Knapsack to maximize population saved
int knapsackDP(vector<Area> &areas, int capacity, vector<int> &selected) {
    int n = areas.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (areas[i - 1].resourceNeed <= w) {
                dp[i][w] = max(
                    areas[i - 1].population +
                    dp[i - 1][w - areas[i - 1].resourceNeed],
                    dp[i - 1][w]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Backtracking to find selected areas
    int w = capacity;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected.push_back(areas[i - 1].id);
            w -= areas[i - 1].resourceNeed;
        }
    }

    return dp[n][capacity];
}

int main() {
    int n;
    cout << "Enter number of disaster areas: ";
    cin >> n;

    vector<Area> areas(n);

    // Input
    for (int i = 0; i < n; i++) {
        areas[i].id = i + 1;
        cout << "\nArea " << i + 1 << ":\n";
        cout << "Population affected: ";
        cin >> areas[i].population;
        cout << "Distance: ";
        cin >> areas[i].distance;
        cout << "Resource needed: ";
        cin >> areas[i].resourceNeed;
        cout << "Urgency: ";
        cin >> areas[i].urgency;
    }

    int totalResources;
    cout << "\nEnter total available resources: ";
    cin >> totalResources;

    // Display initial data
    displayAreas(areas);

    // Step 1: Greedy ordering
    greedyPriority(areas);

    cout << "\n--- Priority Order (Greedy) ---\n";
    for (auto &a : areas) {
        cout << "Area " << a.id << " ";
    }
    cout << endl;

    // Step 2: DP Optimization
    vector<int> selectedAreas;
    int maxSaved = knapsackDP(areas, totalResources, selectedAreas);

    // Output results
    cout << "\n--- Selected Areas (DP Optimal Allocation) ---\n";
    for (int id : selectedAreas) {
        cout << "Area " << id << " ";
    }

    cout << "\n\nMaximum People Saved: " << maxSaved << endl;

    return 0;
}