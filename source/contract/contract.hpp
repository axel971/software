#ifndef CONTRACTS_H
#define CONTRACTS_H

#ifdef CONTRACTS_USE_ASSERT
#include <cassert>
#define REQUIRE(cond, texte) assert(cond)
#define ENSURE(cond, texte) assert(cond)
#define INVARIANT(cond, texte) assert(cond)
#define BEGIN_INVARIANT_BLOCK(className) void _contract_check_invariants() {
#define END_INVARIANT_BLOCK }
#define CHECK_INVARIANTS _contract_check_invariants
#endif

#ifndef CONTRACTS_USE_ASSERT
#define REQUIRE(cond, texte) 
#define ENSURE(cond, texte) 
#define INVARIANT(cond, texte) 
#define BEGIN_INVARIANT_BLOCK(className) void _contract_check_invariants() {
#define END_INVARIANT_BLOCK }
#define CHECK_INVARIANTS _contract_check_invariants

#endif

#endif
