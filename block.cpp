//
// Created by Aleksandr Eremeev on 05.10.2023.
//

#include "block.h"


class Transaction{
public:
    std::string sender;
    std::string recipient;
    double amount;
    double senderBalance;
    Transaction(std::string sender,std::string recipient,double amount,double senderBalance){
        this->sender=std::move(sender);
        this->amount=amount;
        this->recipient=std::move(recipient);
        this->senderBalance = senderBalance;
    }
};

class Block{
public:
    std::string previous_hash;
    std::time_t timestamp{};
    std::vector<Transaction> transactions;
    std::string hash;

    Block(const std::string& previous_hash, std::vector<Transaction> transactions){
        this->previous_hash=previous_hash;
        this->transactions=std::move(transactions);
        timestamp = std::time(nullptr);
        hash = HashGenerate();
    }
    std::string HashGenerate(){
        std::stringstream ss;
        ss<<previous_hash<<timestamp<<transactions[0].sender;
        std::string new_data = ss.str();

        unsigned char hash_calc[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(new_data.c_str()),new_data.length(),hash_calc);
        std::stringstream newHash;
        for (unsigned char i: hash_calc)
            newHash << std::hex << static_cast<int>(i);
        return newHash.str();
    }
};

class BlockChain{
public:
    std::vector<Block>chain;
    std::unordered_map<std::string, double> balances;
    BlockChain(){
        Transaction generalTransaction ("General","Satoshi",100.0,0.0);
        balances["General"]=100.0;
        balances["Satoshi"]=0.0;
        std::vector <Transaction>generalTransactions;
        generalTransactions.push_back(generalTransaction);
        Block generalBlock("0",generalTransactions);
        chain.push_back(generalBlock);
        updateBalances(generalTransaction);
    }
    void addBlock(Block NewBlock){
        NewBlock.previous_hash = chain.back().hash;
        NewBlock.hash = NewBlock.HashGenerate();
        chain.push_back(NewBlock);
        for (const Transaction& transaction : NewBlock.transactions) {
            updateBalances(transaction);
        }
    }
    void updateBalances(const Transaction& transaction) {
        balances[transaction.sender] -= transaction.amount;
        balances[transaction.recipient] += transaction.amount;
    }

};

