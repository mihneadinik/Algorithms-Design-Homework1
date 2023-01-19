#include <bits/stdc++.h>
#include <fstream>

#define file_in "prinel.in"
#define file_out "prinel.out"

// Used for shifting powers of 2
int s = 1;

// Function that reads the input file
void read(int &n, int &k, std::vector<int> &targets,
            std::vector<int> &points, int &maxi) {
    std::ifstream in;
    in.open(file_in);
    in >> n >> k;

    // read the target values vector
    for (int i = 0; i < n; i++) {
        int x;
        in >> x;
        targets.push_back(x);

        // find maximum value of targets
        if (x > maxi) {
            maxi = x;
        }
    }

    // read the points values vector
    for (int i = 0; i < n; i++) {
        int x;
        in >> x;
        points.push_back(x);
    }

    in.close();
}

// Function that returns a vector of a number's divizors
std::vector<int> get_divizors(int x,
        std::unordered_map<int, std::vector<int>> &mem) {
    // create a vector with divizors
    std::vector<int> out(1, 1);
    if (x == 1) {
        return out;
    }

    // If it's a power of 2 it is already stored
    if (mem.find(x) != mem.end()) {
        std::vector<int> vec = mem[x];
        vec.push_back(x);
        mem[x * 2] = vec;
        return vec;
    }

    // Find divizors
    for (int i = sqrt(x); i >= 2; i--) {
        if (x % i == 0) {
            out.push_back(i);
            out.push_back(x / i);
        }
    }

    out.push_back(x);

    // If it's a power of 2, store it for later
    if (x == 1 << s) {
        mem[x * 2] = out;
        s++;
    }

    return out;
}

// Get the minimum number of transformations
void precompute(std::vector<int> &transformations,
            std::unordered_map<int, std::vector<int>> &mem) {
    for (int i = 2; i < transformations.size(); i++) {
        std::vector<int> divs = get_divizors(i, mem);
        for (int div : divs) {
            int res = i + div;
            int futureSteps = 1 + transformations[i];
            if (res < transformations.size()
                && transformations[res] > futureSteps) {
                transformations[res] = futureSteps;
            }
        }
    }
}

// Function that solves the task using DP and writes the answer in file
void solve(int n, int k, std::vector<int> &points, std::vector<int> &targets,
                std::vector<int> &transformations) {
    std::ofstream out;
    out.open(file_out);

    // Check if we can manage all the transformations without computing the DP
    int sum_steps = 0;
    int sum_points = 0;

    for (int i = 0; i < n; i++) {
        sum_steps += transformations[targets[i]];
        sum_points += points[i];
    }

    if (sum_steps < k) {
        out << sum_points << std::endl;
        out.close();
        return;
    }

    // use 2 vectors instead of a matrix for efficiency
    std::vector<int> dp_curr(k + 1, 0);
    std::vector<int> dp_prev(k + 1, 0);

    for (int i = 0; i < n; i++) {
        int target = targets[i];
        int necessarySteps = transformations[target];
        int point = points[i];
        for (int j = 0; j < k + 1; j++) {
            // can't use this number as it involves to many steps to convert it
            if (j < necessarySteps) {
                // keep the previous result if exists
                dp_curr[j] = dp_prev[j];
            } else {
                // I have enough steps to convert this number,
                // but check if it's worth it
                dp_curr[j] = std::max(dp_prev[j], point + dp_prev[j
                                                - necessarySteps]);
            }
        }
        dp_prev = dp_curr;
    }
    out << dp_curr[k] << std::endl;

    out.close();
}

int main() {
    int n, k, maxi = -1;
    std::vector<int> targets;
    std::vector<int> points;
    read(n, k, targets, points, maxi);

    std::vector<int> transformations(maxi + 1);
    std::iota(transformations.begin() + 1, transformations.end(), 0);
    std::unordered_map<int, std::vector<int>> mem;
    precompute(transformations, mem);

    solve(n, k, points, targets, transformations);
    return 0;
}
