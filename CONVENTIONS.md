# Error Naming Conventions and Project Structures

- This file is a guide for all the considerably large projects in this repo
- Will cover: 
- - return codes and meanings,
- - How I structure bigger (usually raylib) projects
- but not right now lmfao it's 5.03AM...I just left this here so I won't forget tomorrow

## Error Codes 

- (-1) For Allocation related problems (malloc,realloc,calloc etc. even mmem or sbrk if exists)
- (-13) Multi-purpose errors
- (-53) System Errors 
- (13) User Invalid Input
- (53) User fuck up 
- (-689) Critical Failure
- (689)  Multi-purpose 
- (-1368953) Fatal Eror 
- (1368953) Error 
- (INT_MIN and INT_MAX) Computational Errors 



## Project Structure



