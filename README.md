# Pepsiman Texture Unpacker
**Pepsiman Texture Unpacker** is a experimental mini-suite for extracting and package texture files for the PSX videogame Pepsiman The Running Hero (SLPS-01762). Of couse, I'm pretty sure that could work in other games too (well... maybe). I made this for a cancelled attempt to make a hack-rom based on this game, but that's another story...
 ![BAAAALTICA!!!](https://i.imgur.com/WWCsUGY.jpg)
 
This is a suite of two tools: Extractor and Packer that extract PSX TIM texture files from Pepsiman PSX game CD files (those files are located in the folder CDDATA, named just by numbers, and does not have any extension).

You can edit TIM files with a plenty of tools available on internet (since TIM is a standard PSX texture format). If you are asking where you can obtain tools to edit TIM images I can suggest you **TIM Viewer** (https://www.romhacking.net/utilities/486/)
## How to use.
For extract TIM files from a package file, run extractor in this way:

    extractor NAME_OF_PACKED_FILE
Where `NAME_OF_PACKED_FILE` is the filename of the packed file you want to extract. It fill find possible TIM files inside and will output all of those in the same folder with the prefix of the name file (if the filename was 0001, it will generate files 0001_extract_1.tim,  0001_extract_2.tim and so on...), including a extra file called `NAME_OF_PACKED_FILE_filetable.txt` where is the location of the files in the original packed file. This will be used at the re-packing process. Just don't try to edit this if you don't know what are you doing, ok? :D

Now, for packing the TIM files back to a packed file, the process is very similar.

    packer NAME_OF_PACKED_FILE

Where `NAME_OF_PACKED_FILE` is the filename of the original packed file. That will take the extracted TIM files and the generated filetable generated before and will generate a new packed file. Also it will generate a backup of the original one if you made some mistake. 
## How it works.
Much packages files present in Pepsiman don't have much information about the files stored inside. Some of them have a file index first, but some others are just TIM files stacked one by one. So, for extract those files the extractor seeks in the package in search of a possible valid TIM file headers. Be warned, that this tool assumes that editing a TIM file (indexed bitmaps) will not change the resulting file size. 

The process how this tool set unpack TIM files is in fact really simple: 

 - It searchs the packed file in search of TIM headers.
 - When a TIM header is found, it dumps in a file until a next header is found.
 - Writes in a filename table the location where the file is found for the packing process.
 - Repeat the process until the end of the file is reached.

In the other side, the packing process works as follows:

 - Reads the filename table to seek the location of each one in the original package.
 - All the data not covered by the filetable is copied from the original package file.
 - The modified files are compsed in one new generated packaged file. 

## Compiling (or just using).

Both tools, Extractor and Packer are made in Standard ANSI C language. You can compile with your favourite flavour of C compiler (GCC or MSVC) without any major issues.
If you're really lazy, you can use provided pre-compiled binaries in that ZIP file :) 

## License.

These tools are licensed with WTFPL license. You can see more details at COPYING.txt or in  http://www.wtfpl.net/about/.