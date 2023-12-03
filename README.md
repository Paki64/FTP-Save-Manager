# FTP Save Manager
 An FTP based save sync utilty between modded consoles and emulators, developed for Linux.


## Requirements
 In order to manage any two-way syncronization process, this software uses [pyftpsync](https://pypi.org/project/pyftpsync/).
 Therefore, it is required to have both Python (Version >= 3.7) and pyftpsync (Version >= 4.0) installed.
 This code was developed and tested only for Linux and WSL 2.0.

 ## Important notes
 This is no cloud syncing, 
 Due to file structure, this utility requires the presence of an already existing save file for 3DS Games on 3DS: make sure to have already made a backup on checkpoint named CITRA (if you don't wanna change the config.ini value). 

## Q&A
 **Why there are two 3ds emulation folders?**
 I preferred redundance over file division and, since already have two different paths for retro emulation on 3ds, I decided to cause a double connection.

## TODO
 - [x] Compatibility with 3DS (Emulators)
 - [X] Compatibility with 3DS (Checkpoint saves) [Required to find a way to automatically associate Checkpoint saves and Citra saves, both for normal saves and extdata]
 - [ ] Syncing with emulators saves paths
 - [ ] Compatibility with PSVita (Emulators)
 - [ ] Compatibility with PSVita (Adrenaline - PSX) [Need to understand the required save fold conversions, should be similar to 3DS tho]
 - [ ] Compatibility with PSVita (Adrenaline - PSP) [Need to understand if there is any encription, thus requiring tools like Apollo]
 - [ ] Compatibility with PSVita (PSV saves) [Low priority at the moment]
