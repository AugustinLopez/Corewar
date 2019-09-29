# Corewar
The *Corewar* project is the final exercice from the *Algorithm* branch at [42]( https://www.42.fr ). [**Core War**](https://en.wikipedia.org/wiki/Core_War) is a programming game in which several programs battle for domination in a virtual computer using a limited set of instructions. Students must build the arena, develop a champion and an interpreter to convert it into a binary. This project is relatively straight-forward but requires a complete reading of the documentation and a precise implementation.

## Useful links

TBD

## Download & Launch

TBD

## Usage

TBD

## Champion Implementation
The *Corewar* project does not requires the implementation of an efficient battle program: strong strategies should be kept secret for the and implemented for the annual championship.

Our champion relies on a cheeky strategy: stealing the opponent's program as fast as possible. This is a hit-or-miss move: it immediately punishes a bad defense but it also loses instantly if the opponent has a proper setup. This can be compared to the [Scholar mate](https://en.wikipedia.org/wiki/Scholar%27s_mate) in chess: a pure beginner destroyer. It relies on precise pre-calculated moves and is not suited for games with 3 players.

It builds two springboards to launch its process at the start of the opponent program, and uses the opponent's starting setup against it, overwriting the previous ID with its own. An efficient defense against that strategy is to overwrite the setup part immediately after using it.

## Virtual Machine Implementation
The *Virtual Machine* is the arena of the *Corewar*. The program runs the champions in a simulated *virtual memory* until a winner has been found. We used the binary provided by the subject as a reference and compared the dumps with `diff`: differences are purely visual.

## Interpreter Implementation

TBD
