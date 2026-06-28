#include <linux/module.h>      // Needed for all modules
#include <linux/kernel.h>      // For printk, KERN_INFO etc.
#include <linux/init.h>        // For __init and __exit
#include <linux/printk.h>      // For pr_info() 



/*          Sup? You know the tea from the file before this one (the old TLDP documentation caused one)
            This is same as it but this one can be compiled lol I'll cut the chase short in this one since I realized the knowledge gap between me and kernel space
            Hence,I'll add more comments and info as I learn more and add more kernel thingies but here you go
            Important shit to know:
                1- There is a make file here that you can compile this file with typing only 'make' on the terminal and it'll generate fuck ton of files
                2- Luckily you can clear those files with make clean
                3- You gotta attach or bind(I dunno the term yet) this module to kernel via : sudo insmod kernelActualDriverThingy.ko 
                4- Then if you wanna see the log out put you gotta type: sudo dmesg | tail -15 (tail -n gives you the last n amount of logs)
                5- To unbind or detach the module: sudo rmmod kernelActualDriverThingy.ko (or however you renamed it)
                6- And you can run the dmesg with sudo privs to see cleanup messages too 
                7- If your kernel panics it's not on me, Works on my Machine OwO
*/





MODULE_LICENSE("GPL-3.0");
MODULE_AUTHOR("Neuro");
MODULE_DESCRIPTION("Panic at the Kernel");
MODULE_VERSION("0.13");  

// Modern init function
static int __init intro(void)
{
    pr_info("Sup? Ring 0?(Still single?)"); //Yeah still making fun of lack of engagement ring...in the kernel...and I trust myself with god privs on a rig...I got balls...or great ignorance lmfao
    pr_info("Locked&Loaded!\n");
    return (0);  // 0 = success, nonzero = shit went sideways
}

// Modern cleanup function
static void __exit dip(void)
{
    pr_info("Breaking up already? :/\n");
    pr_info("Module unlocked&unloaded.\n");
}

module_init(intro); //Modern registering way ig...TLDP made me dirty with init_module thingies
module_exit(dip);
