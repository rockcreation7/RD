#include "WalletList.h"
#include <iostream>

void WalletList::addWallet(const std::string &walletName, int balance)
{
    std::lock_guard<std::mutex> lock(walletList[walletName].mutex);

    walletList[walletName].balance += balance;
}

int WalletList::getBalance(const std::string &walletName)
{
    if (walletList.find(walletName) == walletList.end())
    {
        return -1;
    }

    std::lock_guard<std::mutex> lock(walletList[walletName].mutex);
    return walletList[walletName].balance;
}

void WalletList::printAllWallets()
{
    for (const auto &wallet : walletList)
    {
        std::lock_guard<std::mutex> lock(wallet.second.mutex);

        std::cout << "Wallet: " << wallet.first << ", Balance: " << wallet.second.balance << std::endl;
    }
}
