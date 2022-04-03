// Copyright (c) 2011-2016 The Fortress developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once 
#include "Chaingen.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
class gen_simple_chain_split_1 : public test_chain_unit_base 
{
public: 
  gen_simple_chain_split_1();
  bool generate(std::vector<test_event_entry> &events) const; 
  bool check_split_not_switched(Fortress::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_split_not_switched2(Fortress::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_split_switched(Fortress::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_split_not_switched_back(Fortress::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_split_switched_back_1(Fortress::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_split_switched_back_2(Fortress::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_mempool_1(Fortress::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_mempool_2(Fortress::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  /*bool check_orphaned_chain_1(Fortress::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_orphaned_switched_to_alternative(Fortress::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_orphaned_chain_2(Fortress::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_orphaned_switched_to_main(Fortress::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_orphaned_chain_38(Fortress::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_orphaned_chain_39(Fortress::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_orphaned_chain_40(Fortress::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_orphaned_chain_41(Fortress::core& c, size_t ev_index, const std::vector<test_event_entry> &events); */
private:
};
