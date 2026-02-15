#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define WIPE_TERMINAL "\033[H\033[J"
#define VANISH_CURSOR "\033[?25l"
#define BRING_BACK_THE_CURSOR_FROM_THE_DEAD "\033[?25h" //Yeah I know it doesn't need to be that dramatic or long but C'MON WE ARE BUILDING A EMO JUKEBOX, DUH.
#define FREQ 0.35

const char *bringMeToLife = "How can you see into my eyes like open doors?\nLeading you down into my core\nWhere I've become so numb\nWithout a soul\nMy spirit's sleeping somewhere cold\nUntil you find it there and lead it back home\nWake me up inside (save me)\nCall my name and save me from the dark (wake me up)\nBid my blood to run (I can't wake up)\nBefore I come undone (save me)\nSave me from the nothing I've become\nNow that I know what I'm without\nYou can't just leave me\nBreathe into me and make me real\nBring (bring) me (me) to life\nWake me up inside (save me)\nCall my name and save me from the dark (wake me up)\nBid my blood to run (I can't wake up)\nBefore I come undone (save me)\nSave me from the nothing I've become\nBring me to life\nI've been living a lie\nThere's nothing inside\nBring me to life\nFrozen (frozen) inside without your touch\nWithout your love darling\nOnly (only) you are the life among the dead\nAll of this time I can't believe I couldn't see\nKept in the dark but you were there in front of me\nI've been sleeping a thousand years it seems\nGot to open my eyes to everything\nWithout a thought without a voice without a soul\nDon't let me die here\n(There must be something more) bring me to life\nWake me up inside (save me)\nCall my name and save me from the dark (wake me up)\nBid my blood to run (I can't wake up)\nBefore I come undone (save me)\nSave me from the nothing I've become\nBring me to life\nI've been living a lie\nThere's nothing inside\nBring me to life\n";

const char *iHateEverything = "Every time we lie awake\n"
    "After every hit we take\n"
    "Every feeling that I get\n"
    "But I haven't missed you yet\n"
    "Every roommate kept awake\n"
    "By every sigh and scream we make\n"
    "All the feelings that I get\n"
    "But I still don't miss you yet\n"
    "Only when I stop to think about it\n"
    "I hate everything about you\n"
    "Why do I love you?\n"
    "I hate everything about you\n"
    "Why do I love you?\n"
    "Every time we lie awake\n"
    "After every hit we take\n"
    "Every feeling that I get\n"
    "But I haven't missed you yet\n"
    "Only when I stop to think about it\n"
    "I hate everything about you\n"
    "Why do I love you?\n"
    "I hate everything about you\n"
    "Why do I love you?\n"
    "Only when I stop to think about you\n"
    "I know\n"
    "Only when you stop to think about me\n"
    "Do you know?\n"
    "I hate everything about you\n"
    "Why do I love you?\n"
    "You hate everything about me\n"
    "Why do you love me?\n"
    "I hate\n"
    "You hate\n"
    "I hate\n"
    "You love me\n"
    "I hate everything about you\n"
    "Why do I love you?\n";

const char *myImmortal =
    "I'm so tired of being here\n"
    "Suppressed by all my childish fears\n"
    "And if you have to leave\n"
    "I wish that you would just leave\n"
    "'Cause your presence still lingers here\n"
    "And it won't leave me alone\n"
    "These wounds won't seem to heal\n"
    "This pain is just too real\n"
    "There's just too much that time cannot erase\n"
    "When you cried I'd wipe away all of your tears\n"
    "When you'd scream I'd fight away all of your fears\n"
    "And I held your hand through all of these years\n"
    "But you still have\n"
    "All of me\n"
    "You used to captivate me\n"
    "By your resonating light\n"
    "Now I'm bound by the life you left behind\n"
    "Your face it haunts\n"
    "My once pleasant dreams\n"
    "Your voice it chased away\n"
    "All the sanity in me\n"
    "These wounds won't seem to heal\n"
    "This pain is just too real\n"
    "There's just too much that time cannot erase\n"
    "When you cried I'd wipe away all of your tears\n"
    "When you'd scream I'd fight away all of your fears\n"
    "And I held your hand through all of these years\n"
    "But you still have\n"
    "All of me\n"
    "I've tried so hard to tell myself that you're gone\n"
    "But though you're still with me\n"
    "I've been alone all along\n"
    "When you cried I'd wipe away all of your tears\n"
    "When you'd scream I'd fight away all of your fears\n"
    "And I held your hand through all of these years\n"
    "But you still have\n"
    "All of me\n"
    "All of me\n"
    "All of me\n";


const char *howYouRemindMe =
    "Never made it as a wise man\n"
    "I couldn't cut it as a poor man stealing\n"
    "Tired of living like a blind man\n"
    "I'm sick of sight without a sense of feeling\n"
    "And this is how you remind me\n"
    "This is how you remind me\n"
    "Of what I really am\n"
    "This is how you remind me\n"
    "Of what I really am\n"
    "It's not like you to say sorry\n"
    "I was waiting on a different story\n"
    "This time I'm mistaken\n"
    "For handing you a heart worth breaking\n"
    "And I've been wrong\n"
    "I've been down\n"
    "To the bottom of every bottle\n"
    "These five words in my head\n"
    "Scream \"Are we having fun yet?\"\n"
    "Yeah, yeah, yeah, no no\n"
    "Yeah, yeah, yeah, no no\n"
    "It's not like you didn't know that\n"
    "I said I love you and I swear I still do\n"
    "And it must have been so bad\n"
    "Cause living with him must have damn near killed you\n"
    "And this is how you remind me\n"
    "Of what I really am\n"
    "This is how you remind me\n"
    "Of what I really am\n"
    "It's not like you to say sorry\n"
    "I was waiting on a different story\n"
    "This time I'm mistaken\n"
    "For handing you a heart worth breaking\n"
    "And I've been wrong\n"
    "I've been down\n"
    "To the bottom of every bottle\n"
    "These five words in my head\n"
    "Scream \"Are we having fun yet?\"\n"
    "Yeah, yeah, yeah, no no\n"
    "Yeah, yeah, yeah, no no\n"
    "Yeah, yeah, yeah, no no\n"
    "Yeah, yeah, yeah, no no\n"
    "Never made it as a wise man\n"
    "I couldn't cut it as a poor man stealing\n"
    "And this is how you remind me\n"
    "This is how you remind me\n"
    "This is how you remind me\n"
    "Of what I really am\n"
    "This is how you remind me\n"
    "Of what I really am\n"
    "It's not like you to say sorry\n"
    "I was waiting on a different story\n"
    "This time I'm mistaken\n"
    "For handing you a heart worth breaking\n"
    "And I've been wrong\n"
    "I've been down\n"
    "To the bottom of every bottle\n"
    "These five words in my head\n"
    "Scream \"Are we having fun yet?\"\n"
    "Yeah, yeah\n"
    "Are we having fun yet?\n"
    "Yeah, yeah\n"
    "Are we having fun yet?\n"
    "Yeah, yeah\n"
    "Are we having fun yet?\n"
    "Yeah, yeah\n"
    "No no\n";


const char *nirvanaLithium = 
    "I'm so happy 'cause today\n"
    "I found my friends\n"
    "They're in my head\n"
    "I'm so ugly, but that's okay\n"
    "My world is nothing without your love\n"
    "I'm so happy 'cause today\n"
    "I found my friends\n"
    "They're in my head\n"
    "I'm so ugly, but that's okay\n"
    "My world is nothing without your love\n"
    "I'm so happy 'cause today\n"
    "I found my friends\n"
    "They're in my head\n"
    "I'm so ugly, but that's okay\n"
    "My world is nothing without your love\n"
    "I'm so happy 'cause today\n"
    "I found my friends\n"
    "They're in my head\n"
    "I'm so ugly, but that's okay\n"
    "My world is nothing without your love\n"
    "Yeah, yeah, yeah\n"
    "Yeah, yeah, yeah\n"
    "Yeah, yeah, yeah\n"
    "Yeah, yeah, yeah\n"
    "I'm so happy 'cause today\n"
    "I found my friends\n"
    "They're in my head\n"
    "I'm so ugly, but that's okay\n"
    "My world is nothing without your love\n"
    "I'm so happy 'cause today\n"
    "I found my friends\n"
    "They're in my head\n"
    "I'm so ugly, but that's okay\n"
    "My world is nothing without your love\n"
    "Yeah\n"
    "Yeah\n"
    "Yeah\n"
    "I'm so happy 'cause today\n"
    "I found my friends\n"
    "They're in my head\n"
    "I'm so ugly, but that's okay\n"
    "My world is nothing without your love\n"
    "I'm so happy 'cause today\n"
    "I found my friends\n"
    "They're in my head\n"
    "I'm so ugly, but that's okay\n"
    "My world is nothing without your love\n"
    "Yeah, yeah, yeah\n"
    "Yeah, yeah, yeah\n"
    "Yeah, yeah, yeah\n"
    "Yeah, yeah, yeah\n"
    "I'm so happy 'cause today\n"
    "I found my friends\n"
    "They're in my head\n"
    "I'm so ugly, but that's okay\n"
    "My world is nothing without your love\n"
    "I'm so happy 'cause today\n"
    "I found my friends\n"
    "They're in my head\n"
    "I'm so ugly, but that's okay\n"
    "My world is nothing without your love\n"
    "Yeah\n"
    "Yeah\n"
    "Yeah\n";




    const char *evanescenceLithium =
    "Lithium, don't want to lock me up inside\n"
    "Lithium, don't want to forget how it feels without\n"
    "Lithium, I want to stay in love with my sorrow\n"
    "Don't want to let it lay me down this time\n"
    "Drown my will to fly\n"
    "Here in the darkness I know myself\n"
    "Can't break free until I let it go\n"
    "Let me go\n"
    "Darling, I forgive you after all\n"
    "Anything is better than to be alone\n"
    "And in the end I guess I had to fall\n"
    "Always find my place among the ashes\n"
    "I can't hold on to me\n"
    "Wonder what's wrong with me\n"
    "Lithium, don't want to lock me up inside\n"
    "Lithium, don't want to forget how it feels without\n"
    "Lithium, I want to stay in love with my sorrow\n"
    "Don't want to let it lay me down this time\n"
    "Drown my will to fly\n"
    "Here in the darkness I know myself\n"
    "Can't break free until I let it go\n"
    "Let me go\n"
    "Ooh, ooh, ooh\n"
    "Ooh, ooh, ooh\n"
    "Ooh, ooh, ooh\n"
    "Ooh, ooh, ooh\n"
    "Lithium, don't want to lock me up inside\n"
    "Lithium, don't want to forget how it feels without\n"
    "Lithium, I want to stay in love with my sorrow\n"
    "Stay in love with you\n"
    "Oh\n";


const char *theUnforgiven =
    "New blood joins this earth\n"
    "And quickly he's subdued\n"
    "Through constant pained disgrace\n"
    "The young boy learns their rules\n"
    "With time the child draws in\n"
    "This whipping boy done wrong\n"
    "Deprived of all his thoughts\n"
    "The young man struggles on and on he's known\n"
    "A vow unto his own\n"
    "That never from this day\n"
    "His will they'll take away\n"
    "What I've felt\n"
    "What I've known\n"
    "Never shined through in what I've shown\n"
    "Never be\n"
    "Never see\n"
    "Won't see what might have been\n"
    "What I've felt\n"
    "What I've known\n"
    "Never shined through in what I've shown\n"
    "Never free\n"
    "Never me\n"
    "So I dub thee unforgiven\n"
    "They dedicate their lives\n"
    "To running all of his\n"
    "He tries to please them all\n"
    "This bitter man he is\n"
    "Throughout his life the same\n"
    "He's battled constantly\n"
    "This fight he cannot win\n"
    "A tired man they see no longer cares\n"
    "The old man then prepares\n"
    "To die regretfully\n"
    "That old man here is me\n"
    "What I've felt\n"
    "What I've known\n"
    "Never shined through in what I've shown\n"
    "Never be\n"
    "Never see\n"
    "Won't see what might have been\n"
    "What I've felt\n"
    "What I've known\n"
    "Never shined through in what I've shown\n"
    "Never free\n"
    "Never me\n"
    "So I dub thee unforgiven\n"
    "What I've felt\n"
    "What I've known\n"
    "Never shined through in what I've shown\n"
    "Never be\n"
    "Never see\n"
    "Won't see what might have been\n"
    "What I've felt\n"
    "What I've known\n"
    "Never shined through in what I've shown\n"
    "Never free\n"
    "Never me\n"
    "So I dub thee unforgiven\n"
    "Never free\n"
    "Never me\n"
    "So I dub thee unforgiven\n"
    "You labeled me\n"
    "I'll label you\n"
    "So I dub thee unforgiven\n"
    "Never free\n"
    "Never me\n"
    "So I dub thee unforgiven\n"
    "Never free\n"
    "Never me\n"
    "So I dub thee unforgiven\n";


const char *fadeToBlack =
    "Life it seems will fade away\n"
    "Drifting further every day\n"
    "Getting lost within myself\n"
    "Nothing matters, no one else\n"
    "I have lost the will to live\n"
    "Simply nothing more to give\n"
    "There is nothing more for me\n"
    "Need the end to set me free\n"
    "Things not what they used to be\n"
    "Missing one inside of me\n"
    "Deathly lost, this can't be real\n"
    "Cannot stand this hell I feel\n"
    "Emptiness is filling me\n"
    "To the point of agony\n"
    "Growing darkness taking dawn\n"
    "I was me, but now he's gone\n"
    "No one but me can save myself, but it's too late\n"
    "Now I can't think, think why I should even try\n"
    "Yesterday seems as though it never existed\n"
    "Death greets me warm, now I will just say goodbye\n"
    "Goodbye\n";


const char *rickroll = 
    "We're no strangers to love\n"
    "You know the rules and so do I\n"
    "A full commitment's what I'm thinking of\n"
    "You wouldn't get this from any other guy\n"
    "I just wanna tell you how I'm feeling\n"
    "Gotta make you understand\n"
    "Never gonna give you up\n"
    "Never gonna let you down\n"
    "Never gonna run around and desert you\n"
    "Never gonna make you cry\n"
    "Never gonna say goodbye\n"
    "Never gonna tell a lie and hurt you\n"
    "Never gonna give you up\n"
    "Never gonna let you down\n"
    "Never gonna run around and desert you\n"
    "Never gonna make you cry\n"
    "Never gonna say goodbye\n"
    "Never gonna tell a lie and hurt you\n"
    "We've known each other for so long\n"
    "Your heart's been aching but you're too shy to say it\n"
    "Inside we both know what's been going on\n"
    "We know the game and we're gonna play it\n"
    "And if you ask me how I'm feeling\n"
    "Don't tell me you're too blind to see\n"
    "Never gonna give you up\n"
    "Never gonna let you down\n"
    "Never gonna run around and desert you\n"
    "Never gonna make you cry\n"
    "Never gonna say goodbye\n"
    "Never gonna tell a lie and hurt you\n"
    "Never gonna give you up\n"
    "Never gonna let you down\n"
    "Never gonna run around and desert you\n"
    "Never gonna make you cry\n"
    "Never gonna say goodbye\n"
    "Never gonna tell a lie and hurt you\n";







void epilepsy_typewriter(const char* song);
void typewriter(const char* song);
void sigintHandler(int sig);
int jukeBoxInput(void);

enum songList {
    BRING_ME_TO_LIFE,
    LITHIUM_EVA,
    MY_IMMORTAL,
    I_HATE_EVERYTHING_ABOUT_C,
    UNFORGIVEN,
    FADE_TO_BLACK,
    HOW_YOU_REMIND_ME,
    LITHIUM_NIRVANA
};

int main(void)
{
    srand(time(NULL));
    setvbuf(stdout,NULL,_IONBF,0);
    signal(SIGINT,sigintHandler);
    while (1)
    {    
        int songChoice = jukeBoxInput();

        if (songChoice)
        {
            switch (songChoice-1)
            {
            case BRING_ME_TO_LIFE:
                typewriter(bringMeToLife);
                break;
            case LITHIUM_EVA:
                typewriter(evanescenceLithium);  
                break;
            case MY_IMMORTAL:
                typewriter(myImmortal);  
                break;
            case I_HATE_EVERYTHING_ABOUT_C:
                typewriter(iHateEverything);
                break;
            case UNFORGIVEN:
                typewriter(theUnforgiven);
                
                break;
            case FADE_TO_BLACK:
                typewriter(fadeToBlack);
                
                break;
            case HOW_YOU_REMIND_ME:
                typewriter(howYouRemindMe);
                
                break;
            case LITHIUM_NIRVANA:
                typewriter(nirvanaLithium);
                
                break;
            default:
                //Since we got what we need probably we don't need this but I let it stay 'till -O2 wipes it off.
                break;
            }


        }
        printf(BRING_BACK_THE_CURSOR_FROM_THE_DEAD);
    }

    return(0);
}

void typewriter(const char* song)
{


    printf(VANISH_CURSOR);
    printf(WIPE_TERMINAL);
    usleep(500000);
    while (*song != '\0')
    {
        if (*song == '\n')
        {
            usleep(500000);
            printf("%c\a",*song);
        }
        else
        {
            printf("%c",*song);
            usleep(8*1650);
        }
        song++;
    }
}


void sigintHandler(int sig)
{
    int gettingRickrolledOrNot = (rand() % 4)+1; //Never trust a computer's calculation use bracelets    -Sun Tzu (or Linus Torvalds IDK)
    if (gettingRickrolledOrNot == 3)
    {
        printf(WIPE_TERMINAL);
        usleep(5000);
        epilepsy_typewriter(rickroll); //If you get this ctrl+c ain't saving you.
    }
    printf(WIPE_TERMINAL);
    printf(BRING_BACK_THE_CURSOR_FROM_THE_DEAD); //Don't worry bro got your cursor back
    exit(0);
}


int jukeBoxInput(void)
{
    int choice = -1;

    printf(WIPE_TERMINAL);
    printf("1)Bring Me To Life - Evanescence\n");
    printf("2)Lithium - Evanescence\n");
    printf("3)My Immortal - Evanescence");
    printf("4)I Hate Everything About You - Three Days Grace\n");
    printf("5)Unforgiven - Metallica\n");
    printf("6)Fade To Black - Metallica\n");
    printf("7)How You Remind Me - Nickelback\n");
    printf("8)Lithium - Nirvana\n\n");

    printf("Please select a song(1-8) or Ctrl+C to exit:");                                                      
    //Program -for some reason- doesn't know how to handle just an 'enter' stroke please don't > /// < 
    if(scanf("%d", &choice) != 1 || choice < 1 || choice > 8)  //I'll probably make the length dynamic one day but not today at 5.57AM
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { } //To clear stdin buffer ig my bro said trust me 
        printf("Bro...either try not to be a idiot or Delta the fuck out\n"); //Delta as in displacement a 'Naive' way to GTFO...(not physics 101 flex)
        return(0);
    } 
    else
    {
        return(choice);
    }
}


void epilepsy_typewriter(const char* song) {
    // hide cursor clear screen and shit.
    long color_timer = 0;
    while (*song != '\0') {
        int r = (sin(FREQ * color_timer * 0.2) * 127) + 128;
        int g = (sin(FREQ * color_timer * 0.2 + 2) * 127) + 128;
        int b = (sin(FREQ * color_timer * 0.2 + 4) * 127) + 128;

        printf("\033[38;2;%d;%d;%dm%c", r, g, b, *song);
        fflush(stdout);

        if (*song == '\n') usleep(450000);
        else usleep(15555);
        song++;
        color_timer++;
    }
    printf("\033[0m"); // reset colors
}

/*


                       _______
                  _.-'\       /'-._
              _.-'    _\ .-. /_    '-._
           .-'    _.-' |/.-.\| '-._    '-.
         .'    .-'    _||   ||_    '-.    '.
        /    .'    .-' ||___|| '-.    '.    \
       /   .'   .-' _.-'-----'-._ '-.   '.   \
      /   /   .' .-' ~       ~   '-. '.   \   \
     /   /   / .' ~   *   ~     ~   '. \   \   \
    /   /   /.'........    *  ~   *  ~'.\   \   \
    |  /   //:::::::::: ~   _____._____ \\   \  |
    |  |  |/:::::::::::  * '-----------' \|  |  |
   .--.|__||_____________________________||__|.--.
  .'   '----. .-----------------------. .----'   '.
  '.________' |o|==|o|====:====|o|==|o| '________.'
  .'--------. |o|==|o|====:====|o|==|o| .--------'.
  '.________' |o|==|o|====:====|o|==|o| '________.'
  .'--------. |o|==|o|====:====|o|==|o| .--------'.
  '.________' |o|==|o|====:====|o|==|o| '________.'
    |  |  ||  ____ |:| | | | | |:| ____  ||  |  |
    |  |  || |    ||:| | | | | |:||    | ||  |  |
    |  |  || |____||: Wurlitzer :||____| ||  |  |
    |  |  ||  |   /|:| | | | | |:|\   |  ||  |  |
    |  |  ||  |_.` |:| | | | | |:| `._|  ||  |  |
    |  |  || .---.-'-'-'-'-'-'-'-'-.---. ||  |  |
    |  |  || |   |\  /\  / \  /\  /|   | ||  |  |
    |  |  || |   |~\/  \/ ~ \/  \/ |   | ||  |  |
    |  |  || |   | /\ ~/\ ~ /\ ~/\ |   | ||  |  |
    |  |  || |   |/  \/  \ /  \/ ~\|   | ||  |  |
    |  |  || |   |\~ /\~ / \~ /\  /|   | ||  |  |
    |  |  || |   | \/  \/ ~ \/  \/ |   | ||  |  |
    |  |  || |   | /\~ /\ ~ /\ ~/\ |   | ||  |  |
    |  |  || |===|/  \/  .-.  \/  \|===| ||  |  |
    |  |  || |   | ~ /\ ( * ) /\ ~ |   | ||  |  |
    |  |  || |    \ /  \/'-'\/  \ /    | ||  |  |
   /-._|__||  \    \ ~ /\ ~ /\~  /    /  ||__|_.-\
   |-._/__/|   \    './  .-.  \.'    /   |\__\_.-|
   | | |  ||    '._    '-| |-'    _.'    ||  | | |
   | | |  ||      '._    | |    _.'      ||  | | |
   | | |  ||         '-._| |_.-'         ||  | | |
   | | |  ||  __         | |             ||  | | |
   | | |  || O__O        |_|             ||  | | |
   '.|_|__||_____________________________||__|_|.'
    |  |   |-----------------------------|   |  |
    |  |   [_____________________________]   |  |
    |  |   |/  LGB                      \|   |  |
    '._|__.'                             '.__|_.'



For the vibe it'll stay here 


*/