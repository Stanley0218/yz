#include <bits/stdc++.h>
using namespace std;

struct Trade {
    // <TimeStamp>,<Symbol>,<Quantity>,<Price> 
    long long timeStamp;
    string symbol;
    int quantity;
    int price;
};

long long maxTimeGap(vector<Trade>& trades){
    if(trades.size() == 1) return 0;
    long long res = 0;
    for(int i = 1; i < trades.size(); i++){
        res = max(res, trades[i].timeStamp - trades[i - 1].timeStamp);
    }
    return res;
}

long long totalVolume(vector<Trade>& trades){
    long long res = 0;
    for(auto t : trades){
        res += t.quantity;
    }
    return res;
}

int weightedAvgPrice(vector<Trade>& trades){
    long long amount = 0;
    long long weightSum = 0;
    for(auto t : trades){
        amount += t.price * t.quantity;
        weightSum += t.quantity;
    }
    long long res = amount / weightSum;
    return (int) res;
}

int maxTradePrice(vector<Trade>& trades){
    int res = trades[0].price;
    for(auto t : trades){
        res = max(res, t.price);
    }
    return res;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "wrong command" << endl;
        return 0;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cout << "Fail to find the input file." << endl;
        return 0;
    }
    ofstream outputFile(argv[2]);
    if (!outputFile) {
        cout << "Fail to find the output file." << endl;
        return 0;
    }

    map<string, vector<Trade>> trades;
    string line;
    while (getline(inputFile, line)) {
        Trade trade;
        string x;
        stringstream ss(line); 
        getline(ss, x, ',');
        istringstream is(x);
        is >> trade.timeStamp;
        getline(ss, x, ',');
        trade.symbol = x;
        getline(ss, x, ',');
        istringstream s1(x);
        s1 >> trade.quantity;
        getline(ss, x, ',');
        istringstream s2(x);
        s2 >> trade.price;
        trades[trade.symbol].push_back(trade);
    }

    for (auto it : trades) {
        outputFile << it.first << ","
                    << maxTimeGap(it.second) << ","
                    << totalVolume(it.second) << ","
                    << weightedAvgPrice(it.second) << ","
                    << maxTradePrice(it.second) << endl;
    }

    return 0;
}