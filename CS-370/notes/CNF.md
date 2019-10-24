# How to Convert to CNF

1. remove double implication

- a <=> b -> (a => b) ∧ (b => a)

2. remove implication

- a => b -> (¬a ∨ b)

3. Apply De Morgan's Law _(negation rules)_

- ¬(α ∨ β) -> ¬a ∧ ¬β

- ¬(α ∧ β) -> ¬a ∨ ¬β

- ¬¬α -> α

4. Move all conjunctions (∧) outside of the disjunctions (∨) by using distributivity repeatedly

- (α ∧ β) ∨ γ -> (α ∨ γ) ∧ (β ∨ γ)

- γ ∨ (α ∧ β) -> (γ ∨ α) ∧ (γ ∨ β)

5. split up conjuncts

- each conjunct is one of the clauses in CNF
