# FakeReal
Encoder and decoder for my dumb fakereal cipher

## How to use it

Very simple, type "in" to write in normal words and recieve fakereal encoded words, type "out" to do the reverse.
You can also type "in number" or "out number" to do the same thing except for numbers (not words)

## How it works

Fakereal is a version of ASCII encoding but way more dumb. "fake" is treated as a 0 and "real" is treated as a 1, each series of fakes and reals without a space is treated as binary, (asin realfakereal becomes a 5) BUT when you add a space between these it is treated as concatinating strings and parsing them back into integers (realfakereal fake fake equals to 500)
Therefore you can type any unsigned integer using a series of sets of 4 fakes and reals followed by a space. (Note that this means that the system cannot understand fractions or negative numbers).
These letters are then encoded into ASCII (0 being A, 25 being a, 1 being b, 26 being B etc).

the word "yes" is used to denote a character change and the word "not" is used to denote a word change.
