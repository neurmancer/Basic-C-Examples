#include <linux/module.h>       // Kernel stuff
#include <linux/kthread.h>      // For fork() (actully not but I am coping with imagining threads like forks)
#include <linux/delay.h>        // Pretty self-explanatory...
#include <linux/random.h>       // Same as well
#include <linux/kmod.h>         // Why the fuck I brought this one ((Just remembered :Userspace stuff accessibilty (or how tf u spell it))

static struct task_struct *rickThread;


/*
            Sup? You know the tea... I always come back, with shittier and dangerouser(yeah I know that's not how you spell more dangerous but IDK) ideas
            Here is the working version of the rickroll driver...all you gotta do is rename the Makefile (if you've changed the name of the file)
            then insert the .ko file to the modules... I mean you have one life you GOTTA TRY THIS AT LEAST ONCE 
            
            after insterting check the logs with sudo (required) dmesg | tail -10 to see if shit happened or not if there is no Tux yelling at you you'll be fineeeeeeeee
            Since ssleep() yk...stops the program you won't be able to unload the module without waiting so consider this

            Is this malware? I don't think so...can I abuse this yeah, will I? Nah it's 4AM I need to sleep
            (btw before I forget you're unloding the module with sudo rmmod name.ko)

            Well...the next step is getting a signature for this right? with sign-file and shit 

            And Mr.Torvalds, thx for giving me this chance lmfao

*/


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Neuro");
MODULE_DESCRIPTION("Rick Astley haunts your kernel");
MODULE_VERSION("5.3"); 

#define STEALTH 10

static int rick(void *data)
{
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
        "https://drive.google.com/uc?export=open&id=10aiePDkX2t2XruCaFROIum9nGkQGUzth",
        NULL
    };
    //Lmao even DMCA can't touch Rick in ring 0

    char *envp[] = {
        "HOME=/",
        "PATH=/usr/bin:/bin:/sbin:/usr/local/bin",
        "DISPLAY=:0",
        "XDG_RUNTIME_DIR=/run/user/1000",  //Check your user's UID but 1000 is default in many distros for the first user. Change 1000 to your uid if needed
        NULL
    };

    int ret;

    while (!kthread_should_stop()) {
        pr_info("**I AM IN YOUR WALLS**\t\t-Rick\n");
        // %4 is the perfect amount of annoying but I'd keep it I guess...
        if (get_random_u32() % 25 == 5) {
            pr_warn("**Missed me?**\n");
            
            ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);
            
            if (ret != 0) {
                pr_err("**FUCK GHOSTBUSTERS'RE HERE: %d**\n", ret);
            } else {
                pr_info("**NEVER GONNA GIVE YOU UP**\n");
            }
        }

        ssleep(STEALTH);   
    }

    return(0);
}

static int __init haunt(void)
{
    pr_info("I'm breaching in your walls\tRick\n");
    
    rickThread = kthread_run(rick, NULL, "rick_daemon"); //Should I rename daemon with pokemon?lmfao imagine a family of deamons called after pokemons
    if (IS_ERR(rickThread)) {
        pr_err("Failed to create the rick thread: %ld\n", PTR_ERR(rickThread));
        return(PTR_ERR(rickThread));
    }

    pr_info("**I am become kernel, rickroller of the userspace\t-Rick**\n");
    return(0);
}

static void __exit escape(void)
{
    pr_info("**Aight fine... Rick is leaving the kernel... reluctantly**\n");
    if (rickThread)
        kthread_stop(rickThread);
    pr_info("**Rick has left... but we both know he'll be back. OwO**\n");
}

module_init(haunt);
module_exit(escape);