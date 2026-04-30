#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int id;
    int weight;
    int value;
};

bool compareItems(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

void solveGreedy(int W, vector<Item> items) {
    sort(items.begin(), items.end(), compareItems);
    int currentWeight = 0;
    double finalValue = 0.0;
    cout << "Greedy Selection: ";
    for (int i = 0; i < items.size(); i++) {
        if (currentWeight + items[i].weight <= W) {
            currentWeight += items[i].weight;
            finalValue += items[i].value;
            cout << items[i].id << " ";
        }
    }
    cout << "\nGreedy Total Value: " << finalValue << endl;
}

void solveDP(int W, const vector<Item>& items) {
    int n = items.size();
    vector<vector<int> > dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "DP Optimal Value: " << dp[n][W] << endl;
    cout << "Items included: ";
    int res = dp[n][W];
    int w = W;
    for (int i = n; i > 0 && res > 0; i--) {
        if (res == dp[i - 1][w]) continue;
        else {
            cout << items[i - 1].id << " ";
            res -= items[i - 1].value;
            w -= items[i - 1].weight;
        }
    }
    cout << endl;
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter capacity: ";
    cin >> W;

    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        items[i].id = i + 1;
        cout << "Enter weight and value for item " << i + 1 << ": ";
        cin >> items[i].weight >> items[i].value;
    }

    cout << "\n--- Results ---\n";
    solveGreedy(W, items);
    solveDP(W, items);

    return 0;
}
