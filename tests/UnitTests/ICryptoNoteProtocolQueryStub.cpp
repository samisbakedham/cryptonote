// Copyright (c) 2011-2016 The Fortress developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "IFortressProtocolQueryStub.h"

bool IFortressProtocolQueryStub::addObserver(Fortress::IFortressProtocolObserver* observer) {
  return false;
}

bool IFortressProtocolQueryStub::removeObserver(Fortress::IFortressProtocolObserver* observer) {
  return false;
}

uint32_t IFortressProtocolQueryStub::getObservedHeight() const {
  return observedHeight;
}

size_t IFortressProtocolQueryStub::getPeerCount() const {
  return peers;
}

bool IFortressProtocolQueryStub::isSynchronized() const {
  return synchronized;
}

void IFortressProtocolQueryStub::setPeerCount(uint32_t count) {
  peers = count;
}

void IFortressProtocolQueryStub::setObservedHeight(uint32_t height) {
  observedHeight = height;
}

void IFortressProtocolQueryStub::setSynchronizedStatus(bool status) {
    synchronized = status;
}
