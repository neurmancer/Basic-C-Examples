/*
            Sup? This file probably will be the same as the first working kernel module but with more commentary and explanations 
            since I've started to read The Linux Kernel Module Programmin Guide (you can find the PDF under NerdyShit subfolder or on google)

            So here we go...my final goal is being able to build a rickroll module and load it lol


            Here is the important shit before starting  (First half is copy-paste from book)

            Linux distributions provide the commands modprobe, insmod and depmod within a package.

                On Ubuntu/Debian GNU/Linux:

                sudo apt-get install build-essential kmod                                        
                On Arch Linux:

                sudo pacman -S gcc kmod                                                          

                1.5 What Modules are in my Kernel?
                To discover what modules are already loaded within your current kernel, use the command lsmod.

                lsmod                                                                            
                Modules are stored within the file /proc/modules, so you can also see them with:

                cat /proc/modules                                                                
                This can be a long list, and you might prefer to search for something particular. To search for the fat module:

                lsmod | grep fat                                                                 

                and my personal fuckeries so you don't follow my steps... run echo (uname -r) to see what's your kernel version and find linux-headers matching with it 
                if not compatible you may struglle to load module to kernel if not fail to compile instantly package name was something like linux-headers for arch but dunno for others

                I'll be using The Linux Kernel Documentation to get more info about what the fuck I am doing (here is the link : https://docs.kernel.org for nerds ) along with the said PDF
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Intro module");

                Final notes before including: 
                    1- It's better to know what is where in your system at least roughly since I presume we'll mention /proc/modules or sbin 
                    2- Being comfortable with fucking your entire system
                    3- And a rough understanding of pointer safety since you may nuke your rig while trying to get to hello kernel lol
                    4- You may wanna use an emulator such as QEMU to not nuke your rig but I won't be doing that since that what keeps adrenaline flowing for me 
                    5- Every lecture will have it's own subfolder with needed Makefile (since I don't know how to do it with cc or even possible)
                    6- I'll be copying the Makefiles from the said sources since I don't trust myself with Makefiles


                Faced problems (and possible solutions)
                    1- My kernel version and header version was conflicting (14.smth headers and 13.smth kernel itself) ran pacman -Syu and rebooted *Fixed*
                    2- Module licenses are necessary you can install module without make bitching about it
                    3- And I probably have secure boot preventing me from loading module to kernel and I haven't tried disabling it yet 

*/


#include <linux/module.h>           /*Needed by all modules (and this comment started to give me TLDP PTSD already)*/
#include <linux/printk.h>       //For pr_info
#include <linux/kernel.h>
#include <linux/init.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Neuro");
MODULE_DESCRIPTION("first kernel driver attempt");


int init_fn(void);
void exit_fn(void);

// Modern init function
int init_fn(void)
{
    pr_info("Sup ring 0?");
    return (0);  // 0 = success, nonzero = shit went sideways DO NOT LOAD
}

// Modern cleanup function
void exit_fn(void)
{

}

module_init(init_fn); 
module_exit(exit_fn);





