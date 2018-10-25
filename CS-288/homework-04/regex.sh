# Domenico Maisano

# 1a) contains but does not start with 'A'
egrep '^[^A].*[A]' raven.txt

# 1b) empty / whitespace lines
egrep '^ *$' raven.txt

# 1c) lines with 40+ chars
egrep '^.{40,}$' raven.txt

# 1d) lines with upperase letter(s), ignoring first char on each line
egrep '^[^.].*[A-Z]' raven.txt

# 1e) two p's followed by 'ore'
egrep 'p.*p.*ore' raven.txt

# 1f) two consecutive words...
# where the last letter in the first word is the first letter in the second word
egrep '([a-zA-Z]) \1' raven.txt

# 1g) lines with 3 sets of double letters
egrep '([a-zA-Z])\1.*([a-zA-Z])\2.*([a-zA-Z])\3' raven.txt

# 1h) 5 consecutive letters that form a palindrome
egrep '([a-zA-Z])([a-zA-Z])[a-zA-Z]\2\1' raven.txt

# 2) even parity
egrep '^([02468]+|(([02468]*[13579]){2})+[02468]*)$'

# 3a) lines that contain [aA] @ index m, and [zZ] at index n, where n > m
egrep '[aA].*[zZ]'

# 3b) zip+4
egrep '^[0-9]{5}(-[0-9]{4})?$'

# 3c) int between 0-211
egrep '^([0-9]|[1-9][0-9]|1[0-9][0-9]|20[0-9]|21[01])$'
