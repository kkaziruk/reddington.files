# Crossword Project – Extra Credit

Author: Kaza-Zack Kazirukanyo  
File: `crossword_functions.c`

## Extra Credit Completed

### (a) Skip Unplaceable Words  
If a word cannot be placed on the board due to spacing, overlap, or adjacency violations, the program prints a message and skips it. This is handled during the initial pass of the `solve_puzzle()` function.

### (b) Retry Skipped Words  
After the first pass, the program revisits all unplaced words and attempts to place them again. This process repeats until no more words can be placed, maximizing word coverage on the board.

Both of these features are fully implemented and functional.

## Additional Features

### Menu System  
I added a simple *interactive menu* so that users can choose between viewing the solution, seeing the puzzle, displaying clues, playing a word-guessing game, or saving the output to a file. This improves usability and makes the program more engaging.

### Gamified Word-Guessing Component  
As an extra creative touch, I added a **game mode** where the player is shown scrambled (anagram) versions of each placed word and has to guess the original word.  
The program keeps track of the user’s score and displays it at the end of the game.

## Attempted Feature: Future-Looking Placement Model

Initially, I tried a **future-looking placement model**. The idea was to "scan ahead" and calculate how many open spaces would surround a proposed word placement. This score would be combined with the number of overlapping characters to choose placements that allow the best future flexibility. My inspiration for this was chess. Please see my attempt in the "futurecount.c" file.

However, in practice, this model caused too many words to be skipped or misaligned. Words that could technically fit were often rejected due to surrounding board conditions. I reverted to a simpler brute-force scanning method which proved more reliable and intuitive.


## Testing & Notes

I tested the program using the `ndwords` list.  
Originally, it was unable to place the words:

- LOOP  
- NOT  
- COMPUTER

After implementing the retry loop (`morePlaced`) in `solve_puzzle()`, all of these words were successfully placed in a later pass. The crossword now fits more words intelligently, even when initial placement fails.

