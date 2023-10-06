#include <iostream>
#include "block.cpp"

int main() {
    // Создаем блокчейн и добавляем несколько блоков
    BlockChain blockchain;

    Transaction transaction1("Satoshi", "Bob", 50.0,0.0);
    std::vector<Transaction> transactions1;
    transactions1.push_back(transaction1);
    Block block1(blockchain.chain.back().hash, transactions1);
    blockchain.addBlock(block1);
    std::cout<<"  Sender Balance:"<<blockchain.balances[transaction1.sender]<< std::endl;
    std::cout<<"  Recipient Balance:"<<blockchain.balances[transaction1.recipient]<< std::endl;

    Transaction transaction2("Bob", "Charlie", 30.0,0.0);
    std::vector<Transaction> transactions2;
    transactions2.push_back(transaction2);
    Block block2(blockchain.chain.back().hash, transactions2);
    blockchain.addBlock(block2);
    std::cout<<"  Sender Balance:"<<blockchain.balances[transaction2.sender]<< std::endl;
    std::cout<<"  Recipient Balance:"<<blockchain.balances[transaction2.recipient]<< std::endl;

    for (const Block& block : blockchain.chain) {
        std::cout << "Block Hash: " << block.hash << std::endl;
        std::cout << "Previous Hash: " << block.previous_hash << std::endl;
        std::cout << "Timestamp: " << std::asctime(std::localtime(&block.timestamp));
        std::cout << "Transactions:" << std::endl;
        for (const Transaction& transaction : block.transactions) {
            std::cout << "  Sender: " << transaction.sender << std::endl;
            std::cout << "  Recipient: " << transaction.recipient << std::endl;
            std::cout << "  Amount: " << transaction.amount << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
