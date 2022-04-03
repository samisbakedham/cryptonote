// Copyright (c) 2011-2016 The Fortress developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <vector>
#include <unordered_map>

#include "FortressCore/Account.h"
#include "FortressCore/FortressBasic.h"
#include "FortressCore/Currency.h"
#include "FortressCore/BlockchainIndices.h"
#include "crypto/hash.h"

#include "../TestGenerator/TestGenerator.h"

class TestBlockchainGenerator
{
public:
  TestBlockchainGenerator(const Fortress::Currency& currency);

  //TODO: get rid of this method
  std::vector<Fortress::Block>& getBlockchain();
  std::vector<Fortress::Block> getBlockchainCopy();
  void generateEmptyBlocks(size_t count);
  bool getBlockRewardForAddress(const Fortress::AccountPublicAddress& address);
  bool generateTransactionsInOneBlock(const Fortress::AccountPublicAddress& address, size_t n);
  bool getSingleOutputTransaction(const Fortress::AccountPublicAddress& address, uint64_t amount);
  void addTxToBlockchain(const Fortress::Transaction& transaction);
  bool getTransactionByHash(const Crypto::Hash& hash, Fortress::Transaction& tx, bool checkTxPool = false);
  const Fortress::AccountBase& getMinerAccount() const;
  bool generateFromBaseTx(const Fortress::AccountBase& address);

  void putTxToPool(const Fortress::Transaction& tx);
  void getPoolSymmetricDifference(std::vector<Crypto::Hash>&& known_pool_tx_ids, Crypto::Hash known_block_id, bool& is_bc_actual,
    std::vector<Fortress::Transaction>& new_txs, std::vector<Crypto::Hash>& deleted_tx_ids);
  void putTxPoolToBlockchain();
  void clearTxPool();

  void cutBlockchain(uint32_t height);

  bool addOrphan(const Crypto::Hash& hash, uint32_t height);
  bool getGeneratedTransactionsNumber(uint32_t height, uint64_t& generatedTransactions);
  bool getOrphanBlockIdsByHeight(uint32_t height, std::vector<Crypto::Hash>& blockHashes);
  bool getBlockIdsByTimestamp(uint64_t timestampBegin, uint64_t timestampEnd, uint32_t blocksNumberLimit, std::vector<Crypto::Hash>& hashes, uint32_t& blocksNumberWithinTimestamps);
  bool getPoolTransactionIdsByTimestamp(uint64_t timestampBegin, uint64_t timestampEnd, uint32_t transactionsNumberLimit, std::vector<Crypto::Hash>& hashes, uint64_t& transactionsNumberWithinTimestamps);
  bool getTransactionIdsByPaymentId(const Crypto::Hash& paymentId, std::vector<Crypto::Hash>& transactionHashes);

  bool getTransactionGlobalIndexesByHash(const Crypto::Hash& transactionHash, std::vector<uint32_t>& globalIndexes);
  bool getMultisignatureOutputByGlobalIndex(uint64_t amount, uint32_t globalIndex, Fortress::MultisignatureOutput& out);
  void setMinerAccount(const Fortress::AccountBase& account);

private:
  struct MultisignatureOutEntry {
    Crypto::Hash transactionHash;
    uint16_t indexOut;
  };

  struct KeyOutEntry {
    Crypto::Hash transactionHash;
    uint16_t indexOut;
  };
  
  void addGenesisBlock();
  void addMiningBlock();

  const Fortress::Currency& m_currency;
  test_generator generator;
  Fortress::AccountBase miner_acc;
  std::vector<Fortress::Block> m_blockchain;
  std::unordered_map<Crypto::Hash, Fortress::Transaction> m_txs;
  std::unordered_map<Crypto::Hash, std::vector<uint32_t>> transactionGlobalOuts;
  std::unordered_map<uint64_t, std::vector<MultisignatureOutEntry>> multisignatureOutsIndex;
  std::unordered_map<uint64_t, std::vector<KeyOutEntry>> keyOutsIndex;

  std::unordered_map<Crypto::Hash, Fortress::Transaction> m_txPool;
  mutable std::mutex m_mutex;

  Fortress::PaymentIdIndex m_paymentIdIndex;
  Fortress::TimestampTransactionsIndex m_timestampIndex;
  Fortress::GeneratedTransactionsIndex m_generatedTransactionsIndex;
  Fortress::OrphanBlocksIndex m_orthanBlocksIndex;

  void addToBlockchain(const Fortress::Transaction& tx);
  void addToBlockchain(const std::vector<Fortress::Transaction>& txs);
  void addToBlockchain(const std::vector<Fortress::Transaction>& txs, const Fortress::AccountBase& minerAddress);
  void addTx(const Fortress::Transaction& tx);

  bool doGenerateTransactionsInOneBlock(Fortress::AccountPublicAddress const &address, size_t n);
};
