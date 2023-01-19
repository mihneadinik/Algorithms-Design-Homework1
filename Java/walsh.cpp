#include <fstream>
#include <vector>

#define W 0
#define Wneg 1

#define file_in "walsh.in"
#define file_out "walsh.out"

// Function that reads the input file
void read(int &n, int &k, std::vector<std::pair<int, int>> &queries) {
    std::ifstream in;
    in.open(file_in);
    in >> n >> k;

    // read the queries as pairs
    for (int i = 0; i < k; i++) {
        int x, y;
        in >> x >> y;
        std::pair<int, int> indices = {x, y};
        queries.push_back(indices);
    }

    in.close();
}

// Function that recursively breaks the matrices in 4 equal squares
// and finds the place where my indices fit; nr_neg counts how many
// times I go through the down-right side, where the elements are 'not'ed
int find_pos(int x, int y, int n, int nr_neg) {
    // base case
    if (n == 1) {
        if (nr_neg % 2 == 0)
            return W;
        return Wneg;
    }

    // recursion (compare with the middle line (divide by 2))
    // shift the indexes to fit the new matrix size
    if (x <= ((n >> 1) - 1) && y <= ((n >> 1) - 1))  // C1
        return find_pos(x, y, n >> 1, nr_neg);

    if (x <= ((n >> 1) - 1) && y > ((n >> 1) - 1))  // C2
        return find_pos(x, y - (n >> 1), n >> 1, nr_neg);

    if (x > ((n >> 1) - 1) && y <= ((n >> 1) - 1))  // C3
        return find_pos(x - (n >> 1), y, n >> 1, nr_neg);

    return find_pos(x - (n >> 1), y - (n >> 1), n >> 1, nr_neg + 1);  // C4
}

// Driver function that solves all the queries
void solve(int n, int k, std::vector<std::pair<int, int>> &queries) {
    std::ofstream out;
    out.open(file_out);

    for (int i = 0; i < k; i++) {
        int res = find_pos(queries[i].first - 1, queries[i].second - 1,
                            n, 0);
        out << res << std::endl;
    }

    out.close();
}

int main() {
    int n, k;
    std::vector<std::pair<int, int>> queries;
    read(n, k, queries);
    solve(n, k, queries);
    return 0;
}
