// Copyright (c) 2011-2016 The Fortress developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "INode.h"

#include <string>

namespace PaymentService {

class NodeFactory {
public:
  static Fortress::INode* createNode(const std::string& daemonAddress, uint16_t daemonPort);
  static Fortress::INode* createNodeStub();
private:
  NodeFactory();
  ~NodeFactory();

  Fortress::INode* getNode(const std::string& daemonAddress, uint16_t daemonPort);

  static NodeFactory factory;
};

} //namespace PaymentService
