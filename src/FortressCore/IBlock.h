// Copyright (c) 2011-2016 The Fortress developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "Fortress.h"

namespace Fortress {
class IBlock {
public:
  virtual ~IBlock();

  virtual const Block& getBlock() const = 0;
  virtual size_t getTransactionCount() const = 0;
  virtual const Transaction& getTransaction(size_t index) const = 0;
};
}
