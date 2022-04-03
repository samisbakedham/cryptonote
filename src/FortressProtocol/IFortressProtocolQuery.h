// Copyright (c) 2011-2016 The Fortress developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstddef>
#include <cstdint>

namespace Fortress {
class IFortressProtocolObserver;

class IFortressProtocolQuery {
public:
  virtual bool addObserver(IFortressProtocolObserver* observer) = 0;
  virtual bool removeObserver(IFortressProtocolObserver* observer) = 0;

  virtual uint32_t getObservedHeight() const = 0;
  virtual size_t getPeerCount() const = 0;
  virtual bool isSynchronized() const = 0;
};

} //namespace Fortress
