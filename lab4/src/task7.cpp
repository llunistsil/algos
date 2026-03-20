#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

typedef long long ll;

const ll MOD1 = 1e9 + 7;
const ll MOD2 = 1e9 + 9;
const ll X = 31;

vector<ll> pow1, pow2;

void precomputePowers(int maxLen) {
    pow1.resize(maxLen + 1);
    pow2.resize(maxLen + 1);
    pow1[0] = 1;
    pow2[0] = 1;
    for (int i = 1; i <= maxLen; i++) {
        pow1[i] = (pow1[i - 1] * X) % MOD1;
        pow2[i] = (pow2[i - 1] * X) % MOD2;
    }
}

pair<ll, ll> computeHash(const string& s) {
    ll h1 = 0, h2 = 0;
    for (char c : s) {
        h1 = (h1 * X + (c - 'a' + 1)) % MOD1;
        h2 = (h2 * X + (c - 'a' + 1)) % MOD2;
    }
    return {h1, h2};
}

bool hasCommonSubstring(const string& s, const string& t, int len, 
                        int& bestPosS, int& bestPosT) {
    if (len == 0) return true;
    
    unordered_set<ll> hashes;
    
    ll h1 = 0, h2 = 0;
    for (int i = 0; i < len; i++) {
        h1 = (h1 * X + (s[i] - 'a' + 1)) % MOD1;
        h2 = (h2 * X + (s[i] - 'a' + 1)) % MOD2;
    }
    hashes.insert(h1 * MOD2 + h2);
    
    for (int i = len; i < (int)s.length(); i++) {
        h1 = (h1 * X + (s[i] - 'a' + 1)) % MOD1;
        h1 = (h1 - pow1[len] * (s[i - len] - 'a' + 1)) % MOD1;
        if (h1 < 0) h1 += MOD1;
        
        h2 = (h2 * X + (s[i] - 'a' + 1)) % MOD2;
        h2 = (h2 - pow2[len] * (s[i - len] - 'a' + 1)) % MOD2;
        if (h2 < 0) h2 += MOD2;
        
        hashes.insert(h1 * MOD2 + h2);
    }
    
    h1 = 0; h2 = 0;
    for (int i = 0; i < len; i++) {
        h1 = (h1 * X + (t[i] - 'a' + 1)) % MOD1;
        h2 = (h2 * X + (t[i] - 'a' + 1)) % MOD2;
    }
    
    if (hashes.count(h1 * MOD2 + h2)) {
        bestPosS = 0;
        bestPosT = 0;
        return true;
    }
    
    for (int i = len; i < (int)t.length(); i++) {
        h1 = (h1 * X + (t[i] - 'a' + 1)) % MOD1;
        h1 = (h1 - pow1[len] * (t[i - len] - 'a' + 1)) % MOD1;
        if (h1 < 0) h1 += MOD1;
        
        h2 = (h2 * X + (t[i] - 'a' + 1)) % MOD2;
        h2 = (h2 - pow2[len] * (t[i - len] - 'a' + 1)) % MOD2;
        if (h2 < 0) h2 += MOD2;
        
        if (hashes.count(h1 * MOD2 + h2)) {
            bestPosT = i - len + 1;
            return true;
        }
    }
    
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    string s, t;
    while (cin >> s >> t) {
        int maxLen = max(s.length(), t.length());
        precomputePowers(maxLen);
        
        int left = 0, right = min(s.length(), t.length());
        int bestLen = 0;
        int bestPosS = 0, bestPosT = 0;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            int posS = 0, posT = 0;
            if (hasCommonSubstring(s, t, mid, posS, posT)) {
                bestLen = mid;
                bestPosS = posS;
                bestPosT = posT;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        if (bestLen == 0) {
            cout << "0 0 0" << endl;
        } else {
            unordered_set<ll> hashesS;
            ll h1 = 0, h2 = 0;
            for (int i = 0; i < bestLen; i++) {
                h1 = (h1 * X + (s[i] - 'a' + 1)) % MOD1;
                h2 = (h2 * X + (s[i] - 'a' + 1)) % MOD2;
            }
            hashesS.insert(h1 * MOD2 + h2);
            vector<pair<ll, ll>> hashToPos;
            hashToPos.push_back({h1 * MOD2 + h2, 0});
            
            for (int i = bestLen; i < (int)s.length(); i++) {
                h1 = (h1 * X + (s[i] - 'a' + 1)) % MOD1;
                h1 = (h1 - pow1[bestLen] * (s[i - bestLen] - 'a' + 1)) % MOD1;
                if (h1 < 0) h1 += MOD1;
                
                h2 = (h2 * X + (s[i] - 'a' + 1)) % MOD2;
                h2 = (h2 - pow2[bestLen] * (s[i - bestLen] - 'a' + 1)) % MOD2;
                if (h2 < 0) h2 += MOD2;
                
                hashesS.insert(h1 * MOD2 + h2);
                hashToPos.push_back({h1 * MOD2 + h2, i - bestLen + 1});
            }
            
            h1 = 0; h2 = 0;
            for (int i = 0; i < bestLen; i++) {
                h1 = (h1 * X + (t[i] - 'a' + 1)) % MOD1;
                h2 = (h2 * X + (t[i] - 'a' + 1)) % MOD2;
            }
            
            if (hashesS.count(h1 * MOD2 + h2)) {
                for (auto& p : hashToPos) {
                    if (p.first == h1 * MOD2 + h2) {
                        bestPosS = p.second;
                        break;
                    }
                }
                bestPosT = 0;
            } else {
                for (int i = bestLen; i < (int)t.length(); i++) {
                    h1 = (h1 * X + (t[i] - 'a' + 1)) % MOD1;
                    h1 = (h1 - pow1[bestLen] * (t[i - bestLen] - 'a' + 1)) % MOD1;
                    if (h1 < 0) h1 += MOD1;
                    
                    h2 = (h2 * X + (t[i] - 'a' + 1)) % MOD2;
                    h2 = (h2 - pow2[bestLen] * (t[i - bestLen] - 'a' + 1)) % MOD2;
                    if (h2 < 0) h2 += MOD2;
                    
                    if (hashesS.count(h1 * MOD2 + h2)) {
                        for (auto& p : hashToPos) {
                            if (p.first == h1 * MOD2 + h2) {
                                bestPosS = p.second;
                                break;
                            }
                        }
                        bestPosT = i - bestLen + 1;
                        break;
                    }
                }
            }
            
            cout << bestPosS << " " << bestPosT << " " << bestLen << endl;
        }
    }
    
    return 0;
}
