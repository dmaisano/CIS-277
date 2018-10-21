# Domenico Maisano

# contains but does not start with 'A'
egrep '^[^A].*[A]' raven.txt

# empty / whitespace lines
egrep '^\s+*$' raven.txt

# lines with 40+ chars
egrep '.{40,}' raven.txt

# lines with upperase letter(s), ignoring first char on each line
egrep '^[^A-Z].*[A-Z]' raven.txt

# two p's followed by 'ore'
egrep 'p.*p.*ore' raven.txt

# two consecutive words...
# where the last letter in the first word is the first letter in the second word
egrep '([a-zA-Z]) \1' raven.txt

# lines with 3 sets of double letters
egrep '([a-zA-Z])\1.*([a-zA-Z])\2.*([a-zA-Z])\3' raven.txt

# 5 consecutive letters that form a palindrome
egrep '([a-zA-Z])([a-zA-Z])[a-zA-Z]\2\1' raven.txt

# even parity
# best to use `egrep -o [pattern] [filename]` to avoid empty lines
egrep -o '^(([02468]*[13579]){2})*[02468]*$' filename
