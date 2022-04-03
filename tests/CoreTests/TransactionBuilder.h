// Copyright (c) 2011-2016 The Fortress developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "FortressCore/Account.h"
#include "FortressCore/FortressFormatUtils.h"
#include "FortressCore/Currency.h"

class TransactionBuilder {
public:

  typedef std::vector<Fortress::AccountKeys> KeysVector;
  typedef std::vector<Crypto::Signature> SignatureVector;
  typedef std::vector<SignatureVector> SignatureMultivector;

  struct MultisignatureSource {
    Fortress::MultisignatureInput input;
    KeysVector keys;
    Crypto::PublicKey srcTxPubKey;
    size_t srcOutputIndex;
  };

  TransactionBuilder(const Fortress::Currency& currency, uint64_t unlockTime = 0);

  // regenerate transaction keys
  TransactionBuilder& newTxKeys();
  TransactionBuilder& setTxKeys(const Fortress::KeyPair& txKeys);

  // inputs
  TransactionBuilder& setInput(const std::vector<Fortress::TransactionSourceEntry>& sources, const Fortress::AccountKeys& senderKeys);
  TransactionBuilder& addMultisignatureInput(const MultisignatureSource& source);

  // outputs
  TransactionBuilder& setOutput(const std::vector<Fortress::TransactionDestinationEntry>& destinations);
  TransactionBuilder& addOutput(const Fortress::TransactionDestinationEntry& dest);
  TransactionBuilder& addMultisignatureOut(uint64_t amount, const KeysVector& keys, uint32_t required);

  Fortress::Transaction build() const;

  std::vector<Fortress::TransactionSourceEntry> m_sources;
  std::vector<Fortress::TransactionDestinationEntry> m_destinations;

private:

  void fillInputs(Fortress::Transaction& tx, std::vector<Fortress::KeyPair>& contexts) const;
  void fillOutputs(Fortress::Transaction& tx) const;
  void signSources(const Crypto::Hash& prefixHash, const std::vector<Fortress::KeyPair>& contexts, Fortress::Transaction& tx) const;

  struct MultisignatureDestination {
    uint64_t amount;
    uint32_t requiredSignatures;
    KeysVector keys;
  };

  Fortress::AccountKeys m_senderKeys;

  std::vector<MultisignatureSource> m_msigSources;
  std::vector<MultisignatureDestination> m_msigDestinations;

  size_t m_version;
  uint64_t m_unlockTime;
  Fortress::KeyPair m_txKey;
  const Fortress::Currency& m_currency;
};
