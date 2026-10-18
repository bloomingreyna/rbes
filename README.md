# Reyna's Blooming Entertainment System (RBES)

RBES (pronounced like the shittiest fast food chain of all time, Arby's) is my attempt at an emulator for the original Nintendo Entertainment System. It's a console far beyond my years (born in the year of our Lord 2007), but I've always wanted to eventually play all that old-school shit. Castlevania goes so hard. By the way, did you know that the term "Metroidvania" is, in reality, a fusion of "Metroid" and "Pennsylvania"? It's true, trust me.

*Note from Captain Obvious: This project is a work-in-progress.*

## Goals
- Maybe not *full* cycle accuracy, but at least attempt individual cycle-stepping
- Consistent performance (it's an 80's console, for heaven's sake)
- Ease of use/configuration

## Technical Info
### Languages:
The main emulation logic is written entirely in C++. External libraries (listed below) are written in either C++ or C.

### Libraries:
* [glfw](https://github.com/glfw/glfw)
* [whereami](https://github.com/gpakosz/whereami/tree/master)
