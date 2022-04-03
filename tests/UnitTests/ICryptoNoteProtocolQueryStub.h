// Copyright (c) 2011-2016 The Fortress developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstdint>

#include "FortressProtocol/IFortressProtocolObserver.h"
#include "FortressProtocol/IFortressProtocolQuery.h"

class IFortressProtocolQueryStub: public Fortress::IFortressProtocolQuery {
public:
  IFortressProtocolQueryStub() : peers(0), observedHeight(0), synchronized(false) {}

  virtual bool addObserver(Fortress::IFortressProtocolObserver* observer) override;
  virtual bool removeObserver(Fortress::IFortressProtocolObserver* observer) override;
  virtual uint32_t getObservedHeight() const override;
  virtual size_t getPeerCount() const override;
  virtual bool isSynchronized() const override;

  void setPeerCount(uint32_t count);
  void setObservedHeight(uint32_t height);

  void setSynchronizedStatus(bool status);

private:
  size_t peers;
  uint32_t observedHeight;

  bool synchronized;
};
