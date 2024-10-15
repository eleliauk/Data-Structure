//5.5.3数组的应用
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string LongestStr(const string& s1, const string& s2) {
    int len1 = s1.length();
    int len2 = s2.length();

    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

    int maxLength = 0;  
    int endIndex = 0;   
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            if (s1[i - 1] == s2[j - 1]) {  
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i - 1;  
                }
            }
        }
    }
    return s1.substr(endIndex - maxLength + 1, maxLength);
}

int main() {
    string s1, s2;
    cout << "请输入第一个字符串: ";
    cin >> s1;
    cout << "请输入第二个字符串: ";
    cin >> s2;

    string result = LongestStr(s1, s2);
    if (!result.empty()) {
        cout << "最长公共子串是: " << result << endl;
    } else {
        cout << "没有公共子串。" << endl;
    }

    return 0;
}