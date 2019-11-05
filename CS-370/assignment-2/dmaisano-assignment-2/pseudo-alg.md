# Pseudo Code for Davis-Putnam

> Input: clauses in CNF form (S)

```

DP(ATOMS, S) {
  // V = truth_assignments
  // initially set all atoms to UNBOUND
  V[ATOMS] = UNBOUND
  DP_HELPER(ATOMS, S, V)
}

DP_HELPER(ATOMS, S, V) {
  loop {
    1)
    if (S is null) {
      assign all UNBOUNDs True or False
    }

    2)
    if (S contains a NULL clause) {
      return null
    }

    3)
    if (some literal, L, appears with only one sign) {
      assign L that value and propagate
    }

    4)
    if (S contains a clause with one literal) {
      assign that literal the appropriate value
    }

    5)
    propagate
  }

  6)
  choose UNBOUND ATOM A

  SC = deep_copy(S)
  VC = deep_copy(V)
  VC[A] = true // assign ATOM A True

  propagate


  return DP_HELPER(ATOMS, SC, VC)
}
```
