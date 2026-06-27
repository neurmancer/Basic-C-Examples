# A BASIC C CODING REPO FOR BEGINNERS(ME lulz(at this point I am kinda an intermediate level but fuck it we ball))


## Table of Contents
* [Basic Projects and Lectures](#basic-projects-and-lectures)
* [Funny Things](#funny-things)
* [Spicy C Nudes](#asm-disassemblies-of-files-for-those-low-level-gremlins-like-me-loves-spicy-c-nudes)
* [Compiling & Running](#compile-and-run)
* [Books & Learning Sources](#nerdy-part)

# Basic Projects and Lectures

* [Projects 101](#projects-101)

* [May RNGSUS Bless Us With sran()](#prngforbeginners)

* [Experimenting(Madman's Diary)](#experimenting)

* [LECTURES(KINDA BORING but lowkey enjoyable PART)](#lectureish-boring-part)


### Note to myself

> First if you are not me you shall pass
>
> - Handle subfoldering better shit is growing so fast...
> - Maybe...just maybe *slow down turbo*  **NAH** go for it

## Projects 101

- **Now projects101 got a renewed folder tree for math fuckery and low-level stuff**

- Hello, world script

- %.*s format for printf 

- Basic FizzBuzz script 

- Conditionals intro

- Basic enum101 lectureishy (yeah I started to make words up)

- Struct intro 

- Unions intro

- A basic inverted array walk via pointers (with memory address laid out)

- Subfoldef for bitwise sorcery 

> - A bitwise operations chart 
> - and a cmpbits program

### PRNGForBeginners
- >  Basic heads or tails program (with explanations)
- >  guess game
- >  D6 roller (Now go implement you D20 DND freaks)
- >  Magic 8Ball thingy that roasts you
- > Rock,Paper,Scissors game (but it's cursed AF)




## Lectureish (boring part)


* [UNCLASSIFED](#unclassified-math-fuckery)

* [Low-Level Stuff](#low-level-stuff)

* [Pointer Inferno](#pointerhell)

* [DynamicMemoryShit](#dynamicmemoryshit)

* [Preprocessors](#_ifnwin32-yippie-part)


### Unclassified Math Fuckery

- All math fuckery files moved into a subfolder in projects101 folder called mathFuckery

- Fibonacci sequence function (with loops and recursion)

- Prime indicator (I guess it's optimized but dunno for sure) when the Satan took the wheels

- Basic prime number counter with user input

- Get time program experiment

- Basic terminal window get test program for myself just syntax and shit. To use in DVD-Screensaver but till I use it this will stay here(And So I Did)

- Cmp popcount program

- Koch Curve from Binary interpretation I made (not sure if it's accurate) 

- Koch Snowflake using Thue-Morse Sequence (same thing with Koch Curve file but with graphics(raylib required) and yeah still not sure if it's accurate)

- A Discrete Fourier Transform with cosine samples as a placeholder for a future FFT implamentation (no libs except math.h) 

- A Fast Fourier Transform with cosine samples added as a placeholder for future math fuckery my ideas ran dry for now (and ofc no external libs with the sole exception of math.h)

- Doppler Effect Simulator (using raylib.h so you gotta have it too)

- Screensaver that paints screen from scratch using primes  with raylib 

- Screensaver that paints screen from scratch using primes  with ANSI for CLI 



### Low-Level Stuff

> Baby's Kernel Drivers (We'll learn together)
> 
> - First failed attempt added(using TLDP's old sources)
> - Non-failed second modern-attempt (_working_) with no tutorial (I'll add shit in the future let me learn first TnT) 
>
>
> Networking
> 
> A basic HTTP TCP server using sockets (pure C...no external libs) **Will be Developed Further**
>
> Other Low-Level Stuff
>
> - A mainless C file that you can run (for no apperant reason)
> - Buffer oveflow for lulz. 


### PointerHell 

> - Basic pointer101 lecture with syntax and detailed explanations without making it scary (yet)
>
> - Second pointer lecture about array navigation and fucking with .rodata 
>
> - Pointer&function relation lecture
>
> - Pointer and array relation quickie
>
> -  Function Pointer introduction Lecture (honestly it's not the best practice to use them this way but good for seeing syntax)
>
> - Struct usage with pointers intro
>
> - Array and pointer relation lecture
>
> - Funfact about language itself  


### DynamicMemoryShit

> - Subfolder for dynamic memory allocation
> - Introduction for malloc() 
> - Simple malloc usage with arrays 
> - Realloc& calloc introduction
> - Structs with dynamic allocation intro 


### _IFNWIN32 "Yippie" Part

> - First lecture using define and macros
>
> - Second lecture Conditional blocks (IFDEF,IFNDEF,ELIF)





## Funny Things

- Bring Me To Life lyrics spitter for CLI (prototype shitty jukebox from day 3)

- A program that gives you an output file and spits a text on terminal anyways because I used stderr instead of stdout

- Added a walking segfault PTSD on purpose 


## ASM DISASSEMBLIES OF FILES FOR THOSE LOW-LEVEL GREMLINS LIKE ME LOVES SPICY C NUDES

- Basically Every script I'll put in the repo will get it's assembly file with the same name 
- I may add -O2 flag to make it torturing to get what even the program was in the first place if I feel like it
- Fresh C nudes came (17.02.2026 00.02AM) 
- __*Been gone to get some cigs*__ New updated will be here once when I remember how to use the Makefile again



## Compile and Run
```bash

#For the ones don't know how to compile and run 
#if there is additional lib/flag for any specific file it will be commented within file itself.
#Mostly used one being -lm to link math.h (future update some of them requires raylib for graphs so you gotta use -lraylib too for said files

cc filename.c -o output #To compile

./output 
#To run (but since all the files written for 
#Linux and don't have Windows ports I presume you already know to do this because windows sux)
```


## Future Adds 
- **More** Janky physics simulators and _Math Fuckery_ such as :
>
> - Doppler effect simulator for celestial bodies (redshifting/blueshifting)
> - A basic pendulum 
> - Maybe a function visualizer 
> - Tupper's self-referntial graph (possible but no promises)
> - Sierpinski's triangle (if I can reverse engineer the math lol)
> -  Sierpinski's tetrahedron (if I learn cameras & movements on raylib)
> 
> I may add basic games either into this repo or I might create another repo for games here are the ones I'd love to build
>
> - **Galaga** Clone
> - **Pong** ofc (maybe multiplier with my own server for flex)
> - **Breakout**
(yeah I am a retro guy...and those serves to the purpose of this repo...beginner friendly...no DS emulation yet)


## Nerdy Part

> Those are the books I've digged and wanna read/ already read and think would help anyones here's the ***PDFs*** for each

> - **The C Programming Language 2nd Edition** by K&R (The Holy Bible...ehm acktually it's Old Testament)
> - **Linux System Programming**
> - **Writing Solid Code** 
> - **Advanced Bash-Scripting** (haven't started to read yet)
> - **Clean Archicture**
> - **Grokking Algorithms** (The classic beginner friendly DSA book)
> - **Linux Kernel Dev**(That's where I wanna end at)





### P.S. 

> If you think 'Beginner apps' are to-do lists and CLI calculators and those are advanced stuff...You are missing the part that I value.Hence, this repo is not suitable for you or on the other hand I am glad you are here if you are reading this.
