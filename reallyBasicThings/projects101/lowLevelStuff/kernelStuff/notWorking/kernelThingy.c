#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/random.h>
#include <linux/kmod.h>
#include <linux/jiffies.h>


static struct task_struct *rick_thread;

static struct task_struct *thread;          //Unistd was not able so we're improvising shit lmfao and let me get this straight I HAVE NO FUCKING IDEA WHAT I AM DOING


/*
    To install this (although I don't even advise to do so) you gotta change the Makefile obj to filename of this file instead of the other one...I'll keep it as it is for education purposes but 
    Who doesn't want to get haunted by rickroll anyways?



        Yup...another failed attempt...
            It loads the module but the loop doesn't work for some reason that I couldn't solve
*/


MODULE_LICENSE("GPL-3.0");
MODULE_AUTHOR("Neuro");
MODULE_DESCRIPTION("Rick Astley attempts to haunt your kernel");
MODULE_VERSION("0.53"); 

static int rick_fn(void *data)
{   
    //Ffplay flags that I scraped from man page for ShittyJukebox lol
    
    char *argv[] = {
            "/usr/bin/ffplay",
            "-nodisp",
            "-autoexit",
            "-fflags", "nobuffer",
            "-flags", "low_delay",
            "-probesize", "32",
            "-analyzeduration", "0",
            "-strict", "experimental",
            "-loglevel", "quiet",
            "https://drive.google.com/uc?export=open&id=10aiePDkX2t2XruCaFROIum9nGkQGUzth",  // THE CLASSIC (yeah pirate stream...my own google drive)
            NULL
        };

    char *envp[] = {
            "HOME=/",
            "PATH=/usr/bin:/bin:/sbin",
            NULL
        };
    int flag = 0;
    //This is a thread Ig...man I miss the forks already
    while (!kthread_should_stop()) {
        flag = 0;
        pr_info("I am in your walls\t\t-Rick\n");
        if (get_random_u32() % 5 == 3) {
            flag = 1;
            call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);
        }
        if (flag) {
            ssleep(210);
        }
        else {
            ssleep(10);
        }
    }

    return(0);
}


//AAAAAAAAAAAAAAAAAAAAAA I wanted it to work... and ladies and gentlemen...that's reason will be behind my first Linux Kernel Dev journey...presenting you the idea of RickrOS
static int __init haunt(void)
{
    pr_info("Loading important shit\n");
    
    rick_thread = kthread_run(rick_fn, NULL, "rick_astley");
    if (IS_ERR(rick_thread)) {
        pr_err("Failed to rickroll you: %ld\n", PTR_ERR(rick_thread));
        return PTR_ERR(rick_thread);
    }

    return(0);
}

static void __exit escape(void)
{
    pr_info("Fine!!!I won't haunt you anymore...unless?\t OwO \n");
    if (rick_thread)
        kthread_stop(rick_thread);
    pr_info("Rick has left the kernel.\n");
}

module_init(haunt);
module_exit(escape);