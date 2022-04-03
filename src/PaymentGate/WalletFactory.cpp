// Copyright (c) 2011-2016 The Fortress developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "WalletFactory.h"

#include "NodeRpcProxy/NodeRpcProxy.h"
#include "Wallet/WalletGreen.h"
#include "FortressCore/Currency.h"

#include <stdlib.h>
#include <future>

namespace PaymentService {

WalletFactory WalletFactory::factory;

WalletFactory::WalletFactory() {
}

WalletFactory::~WalletFactory() {
}

Fortress::IWallet* WalletFactory::createWallet(const Fortress::Currency& currency, Fortress::INode& node, System::Dispatcher& dispatcher) {
  Fortress::IWallet* wallet = new Fortress::WalletGreen(dispatcher, currency, node);
  return wallet;
}

}
