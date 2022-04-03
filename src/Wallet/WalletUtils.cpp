// Copyright (c) 2011-2016 The Fortress developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "WalletUtils.h"

#include "Fortress.h"

namespace Fortress {

bool validateAddress(const std::string& address, const Fortress::Currency& currency) {
  Fortress::AccountPublicAddress ignore;
  return currency.parseAccountAddressString(address, ignore);
}

}
