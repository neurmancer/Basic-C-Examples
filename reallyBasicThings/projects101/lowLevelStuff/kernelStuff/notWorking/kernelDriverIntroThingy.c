#include <linux/module.h> //   needed for all modules (they say)
#include <linux/kernel.h> //Needed for KERN_INFO 


/*  And if you can't tell this is a Linux only Lecture...duh*/

/*
            This TUTORIAL IS OUT-DATED AS FUCK AND DOESN'T WORK WITH THE GIVEN MAKFILE SO PLESE DON'T WASTE YOUR TIME I'LL LEAVE IT AS A ATTEMPT IN THE FOLDER


    Wassup? Dear cc, today we're gonna build the baby's first kernel module are you as exicted as me?(Satire...don't take this too seriously since neither do I)
    You know the tea...I saw something, I gotta dig...I lowkey feel like Sysphius...Push the boulder, find a new one at the bottom and push it again...

    Nah...enough with diary(dairy? which one was the notebook for crying and which one was the milky products?anyways)
    Important shit to know:
        1- I am looking to The Linux Documentation Project's website for information on modulues. Here is a link for you: https://tldp.org/LDP/lkmpg/2.6/html/x121.html
        2- I fucking love how they document... so let me quote the introduction from their documentation 
            "When the first caveman programmer chiseled the first program on the walls of the first cave computer, it was a program to paint the string `Hello, world' in Antelope pictures. Roman programming textbooks began with the `Salut, Mundi' program. 
            I don't know what happens to people who break with this tradition, but I think it's safer not to find out. "
            And that's exactly how a documentation should start...it must acknowledge that you are new here and calm you down before getting techical anyways enough yap...         
    

            This file probably will not work since the tutorial seems out-dated but we'll see

*/

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Test?");

int my_module(void) //Doesn't take any argument 
{
	//What init does basically (man...it's hard to simplify KERNEL STUFF) registering a handler for something on the (or with the) kernel or 
	//replace/overwrite one of kernel's own functions
	

	printk(KERN_INFO "Hello, Ring 0 (still single?)\n");	//I'll explain the kernel print 'log priority levels' but as you can guess printk was not meant 
								//to communicate with user directly...yk...that's the whole deal of...yk...being bare-metal  



	return(0); //Returns something than 0 different on errors
}

//And this one is the Ctrl+Z of init_module...it undoes(is that a word?) what init_module have done and in the website that I provided you with they say
//Those function names can differ but this is a common usage as far as I understood...


void cleanup_module(void)
{
	printk(KERN_INFO "Now I'll just say goodbyeeee\n");
}

