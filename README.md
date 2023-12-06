# FTP Save Manager
 An FTP based save sync utilty between modded consoles and emulators, developed for Linux.


## Requirements
 In order to manage any two-way syncronization process, this software uses [pyftpsync](https://pypi.org/project/pyftpsync/).
 Therefore, it is required to have both Python (Version >= 3.7) and pyftpsync (Version >= 4.0) installed.
 This code was developed and tested only for Linux and WSL 2.0.

 ## Important notes
 This is no cloud syncing and it will probably never be: for every syncronization it needs the console connected to ftp (ex. FTPD on 3DS) and a pc with the utility running on the same local network (I made this tool in order to use it on my server).
 Due to file structure, this utility requires the presence of an already existing save file for 3DS Games on 3DS: make sure to have already made a backup on checkpoint named CITRA (if you don't wanna change the config.ini value). 
 This is also to be not considered as a save backup solution, it's very risky (especially with 3DS and its problems with timestamp: be sure to edit RTC within godmode9 if required).

## Q&A
 **Why there are two 3ds emulation folders?**
 I use on my 3DS nds_bootstrap for nds roms, snes9x_3ds for snes roms and retroarch for anything else: due to the fixed folder structure of nds_bootstrap and snes9x_3ds, i selected the second one save location ("/3ds/snes9x/saves") as main retroarch save path.
 This choice is made also because of the use of melonDS standalone for nds roms on my pc, while i run everything else in retroarch; it's pretty helpful to divide retro saves in ds and retroarch. 
 
## TODO
 - [x] Compatibility with 3DS (Emulators)
 - [X] Compatibility with 3DS (Checkpoint saves) [Required to find a way to automatically associate Checkpoint saves and Citra saves, both for normal saves and extdata]
 - [X] Syncing with emulators saves paths
 - [ ] Compatibility with PSVita (Emulators)
 - [ ] Compatibility with PSVita (Adrenaline - PSX) [Need to understand the required save fold conversions, should be similar to 3DS tho]
 - [ ] Compatibility with PSVita (Adrenaline - PSP) [Need to understand if there is any encription, thus requiring tools like Apollo]
 - [ ] Compatibility with PSVita (PSV saves) [Low priority at the moment]
