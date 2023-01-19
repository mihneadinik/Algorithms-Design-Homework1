#include <bits/stdc++.h>
#include <fstream>

#define file_in "crypto.in"
#define file_out "crypto.out"

// Function that reads the input file
void read(int &N, int &L, std::string &K, std::string &S) {
    std::ifstream in;
    in.open(file_in);
    in >> N >> L;
    in >> K;
    in >> S;

    in.close();
}

// Function that solves the task using dynamic programing
// and writes the answer in file
void solve(int N, int L, std::string &K, std::string &S) {
    std::ofstream out;
    out.open(file_out);

    // Create DP table
    std::vector<std::vector<long>> dp(N + 1, std::vector<long>(L + 1, 0));

    // Count number of unique chars
    std::unordered_map<char, int> chars;
    for (int i = 0; i < L; i++) {
        chars[S[i]]++;
    }

    int unique_chars = chars.size();
    long branches = 1;

    // If the key has no characters
    for (int i = 0; i <= L; i++) {
        dp[0][i] = 0;
    }

    // If the substring has no remaining characters, then it's one
    // occurrence per branch => store number of branches at each letter
    dp[0][0] = 1;
    for (int i = 1; i <= N; i++) {
        if (K[i - 1] == '?') {
            branches = (branches * unique_chars) % 1000000007;
        }
        dp[i][0] = branches;
    }

    // Solve in a bottom-up manner
    for (int i = 1; i <= N; i++) {
        char curr_char = K[i - 1];
        for (int j = 1; j <= L; j++) {
            if (curr_char == S[j - 1]) {
                // found matching characters
				dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % 1000000007;
            } else {
                // characters don't match, check for '?'
                if (curr_char == '?') {
                    // in case of splitting into branches
                    dp[i][j] = ((unique_chars * dp[i - 1][j]) % 1000000007
                                    + dp[i - 1][j - 1]) % 1000000007;
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
    }

    out << dp[N][L] % 1000000007 << std::endl;
    out.close();
}

int main() {
    int N, L;
    std::string K;
    std::string S;

    read(N, L, K, S);

    solve(N, L, K, S);
    return 0;
}
