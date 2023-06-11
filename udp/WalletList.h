#pragma once

#include <unordered_map>
#include <mutex>
#include <string>

struct Wallet {
    mutable std::mutex mutex;
    int balance;
};

class WalletList {
private:
    std::unordered_map<std::string, Wallet> walletList;

public:
    void addWallet(const std::string& walletName, int balance);
    int getBalance(const std::string& walletName);
    void printAllWallets();
};
