It is recommended you emulate/virtualize AphelionOS on your host OS as it has not been tested on
real hardware, Even though we are getting close to booting AphelionOS on actual hardware.

Therefore:

*********************************************************
How to run AphelionOS on Linux - based Operating Systems:
*********************************************************

Download the source code from the latest release tag.
Install QEMU first. for instructions on how to do that, check out:
https://www.qemu.org/download/
Run the "run.sh" via the terminal. Choose your boot medium by typing either 1 or 2.(ISO recommended, as it gets tested most often)

What you should expect:
Expect everything to function properly.

*****************************************************
How to run AphelionOS On Windows / MacOS / Other OSs:
*****************************************************

Download the ISO from the latest release tag,
Then put the ISO image into An virtualization platform (Like Vmware or VirtualBox).
Select "other" In the OS list (On VirtualBox) and
give it ~5 MegaBytes of memory and ~5 MegaBytes of disk space

********************************************
What you should expect on Windows / MacOS:
********************************************
You should expect sound to (PROBABLY) not work. You (PROBABLY) need extra configuration on virtualbox for sound to work.
Configuration that has not been properly documented yet.
I am currently not able to find the proper configuration because 
I am on GNOME Fedora Linux 45 and VirtualBox does not have support for Fedora 45 yet. 
For those willing to try:
This is the QEMU sound configuration that makes it work on Linux:

"-audiodev sdl,id=snd0 -machine pcspk-audiodev=snd0"

For more information on that check out the run.sh in the source code

If you find the proper sound configuration please comment it on my YouTube channel and i will credit you for the discovery If you want to be credited of course (please make that clear)
My youtube channel is @squidy_fish (If you for whatever reason can not find it, search up "aphelionos" on youtube and try to look for an eevee profile picture) 

