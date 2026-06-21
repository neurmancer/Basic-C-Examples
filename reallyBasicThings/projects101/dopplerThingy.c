/*    Includes    */

#include <math.h>
#include <stdio.h>
#include <raylib.h> //Yeah now I am a pathetic lib dependent guy...
#include <time.h>

/*      Defines     */
#define WIDTH 1280.0 //Since I am using floats everywhere for position .0 (or explicit casting is a better way to shut cc warnings)
#define HEIGHT 960.0

#define FPS 60

#define MAX_WAVES 64    // Old value: 1024 | Overkill? We'll see...
#define WAVE_SPEED 60 //Should I use vel or speed? I mean... does a circle has vector? or just magnitude? it expands outwards...
                         // is that even a vector? I mean isn't a 'ring' is infinite set of points equally far from a point and propagating them is basically 
                         //moving all of the with different angles outwards? I'm confused and changing name from WAVE_VELOCITY to WAVE_SPEED since due to only storing magnitude

#define FRICTION 0.42f //Yeah meaning of life
#define ACCELERATION 30.0f

#define COOL_RED CLITERAL(Color){53, 0, 13, 255} //Get it? because it has a essance of blue in it?
#define DA_BLUE CLITERAL(Color){0, 13, 53, 255}


/*              Sup? Got bored again and math fuckery wasn't enough...so here we are learning a 'framework' or lib I don't know what to call 
                but I am using raylib as you can see...


                And that's where I call it 'Eh close enough' and abonden the rest for a while probably I'll be buliding more janky physics simulators lol
                
                Important shit to know:
                1- you need to have raylib.h in your system I used pacman -S raylib and it worked so I assume apt-get and dnf will work too... as always windows can suck mine
                2- you gotta compile with -lraylib to link raylib (duh)
                3- We're building a Doppler Effect Demonstrator/Simulator and I have no idea why the fuck I am doing this it's 00AM I stop questioning after 11PM
                4- I am using this cheat sheet from raylib https://www.raylib.com/cheatsheet/cheatsheet.html for seeing shit and funny enough? 
                They're explaining as if I am an idiot and I am a sucker for it.
                I may know a little bit of C but libs and frameworks has their own rules which I am not familiar with 
                (thx for making my job easy raylib...)

                5- Since this is the first file in the repo requring external dependency (raylib) I am improvising the notation a little such as sectioning like defines,includes and shit

                6- I am doing this purely with what I remember so it might not be correct. 
                For instance....waves probably need a vector as the car moves due to Newtonian laws... 
                or just due to common sense summing  the velocity of car and wave since the emmited wave starts at a speed relative to a stationary observer..or does it? I mean if you move in a train you'd move at speed of you+train do sounds do the same? waves? but they're physical too if not why the fuck even doppler occurs? it should be dependent on the medium (if that's the right term) right otherwise how raptors would go super...I mean if the vectors would summed sound would always act stationary relative to the source right? but shit goes mach1+ so IDK MAN IDK...
                but I gotta check that to implement...
                i think Newtonian motion is fine since we're working on soundwaves so no Lorenz factor or relative velocity fuckery yet..
                but really tho I am not a physicist so this might be way off...
                as I said this file is from memory of mine not based on wikipedia so don't expect me to show you lambda = vel / freq at least for now  

                Now the real tea...Wtf is doppler effect? 
                and here is the first name drop of the file: It is named after the physicist Christian Doppler, 
                who described the phenomenon in 1842

                It is the  change in the frequency or pitch of a wave in relation to an observer who is moving relative to the wave's source 
                so if an ambulance is coming towards you you'll hear a higher pitch and if it's going further away the pitch will lower 
                did I simulate it?
                    -Kinda visually but nah there is no frequency or wavelength detection in this program is there a math involved? Fuck yeah!
                
                    I basically made a ball that you can move with WASD and it creates rings around itself no acceleration no visible pitch change and shit 
                    But lowering part of the pitch (which is the part where rings gets further apart behind the ball is solid)
                
                I may add 
                    1- A rectangle representing an observer on a random point *Started working On*
                    2- An acceleration element to the car *Added* 
                    3- Adding sounds to demonstrate pitch shift (Probably gonna be a ear-fucker)
                    4-or if I can figure out how to partially color a circle I may add 'blue-shift' 
                    for the positive vector and 'red-shift' for the negative as the vehicle goes visually ofc (maybe a little math for the fun too)  
                
                Known bugs: 
                    -Frequency is twice for some FUCKING reason it emits waves twice as much in a given time...tried to use time(NULL), clock(),
                    and I wanna get an accurate shit hence I don't just tune it to twice as much or /2 the result but now you can see the period in terminal as a counter 
                    (if you don't now what is a period it is basically (freq)^-1 or wave count per unit of time (second)) 


                    and before I dip (since it's fucking 2.30AM) doppler effect isn't a thing only applied to sound waves it applies to all waves...
                in fact we determine the relative positions of celestial bodies using doppler if you heard the term blueshift and redshift...
                this is exactly doppler effect applied on electromagnetic waves
                Redshift when the source getting further (lower frequency)
                Blueshift is when the source getting closer (higher frequency) 
                and that's how Edwin Hubble realized that shit is getting further from us using redshift
                (yeah the dude we named a huge telescope after) and 
                    -if you are saying 'shut up nerd' 
                        First, Fuck off, 
                        Second, Why the fuck you are looking for a doppler Thingy if you are NOT interested bruh? 

                Btw since we're on astronomy...have you known that why there is no 'Green' stars? yeah I checked there is none...well they emmit 'green' 
                but since all the stars have infrared or ultaviolet emmisons the peak of the visible color always hits somewhere closer to the edges such as red or violet 
                and since green is in the middle of the visible spectrum the peak never becomes green and if it is they would simply emmit all the spectrum and we'd see it as white due to blackbody radiation...damn I've yapped so much didn't I?
                and if you don't know how the spectrum goes it goes like infrared(invisible to human eye)-Red, Orange,Yellow, Green, Blue, Indigo, Violet - Ultraviolet(invisible to human eye) simply ROYGBIV
                
*/


/*      Objects(or Structs)     */

typedef struct{
    /*
            Chart before I forget
            x,y -> Position
            aX,aY -> acceleration on the given axis
            vX,vY -> velocity on the given axis

            speed for maginute 
    */
    float x;
    float y;

    float aX;
    float aY;
    
    float vX;
    float vY; //Man that's fucking overwhelming....
 
    float speed;
}Vehicle;



typedef struct{
    //first, Float because I want shit to move smooth. 
    // Second, dRadius instead of radius because it'll change over time and delta is literally the 'displacment' notation  
    float x;
    float y;
    float dRadius; 

    int isDetected; //To flag collision

}SoundWave; //I tried using Wave as var name but it conflicted with a raylib definition ig so we're going with soundwave 

/* Declarations */

void drawVehicle(Vehicle vehc);
void drawWaves(void);
void drawObserver(Rectangle obs);

void emmitWave(void);
void expandWaves(float dT);

unsigned int checkObserverCollisions(void);

/* Global Vars  (I dunno how many I'll have but here it is)... */

Vehicle car = { 0 };
Rectangle observer = { 0 };
/*This is not the best practice but I ended up having only 3 globabls and adding parameteres for only 3 globals seemed too much work tbh so deal with it pls*/

unsigned int waveCount = 0; 
SoundWave waves[MAX_WAVES] = { 0 }; //Those are just empty array declaration... a habit of mine, don't mind...

int main(void)
{

    SetRandomSeed(time(NULL)); //I really dunno why I used this from raylib instead of rand() but I did...I NEED CHANGE TOO forgive me RNGsus for what I've sinned
    

    observer.x = GetRandomValue((WIDTH/10),WIDTH-50);
    observer.y = GetRandomValue((HEIGHT/10),HEIGHT-50);
    observer.width = 30.0f; 
    observer.height = 30.0f;
    
    //Tweaks
    InitWindow(WIDTH, HEIGHT ,"Doppler Thingy");
    SetTargetFPS(FPS);

    if (!IsWindowReady()) { perror("Window got fucked up\n"); return(-1) ;}

    //Car props
    car.x = WIDTH/2;
    car.y = HEIGHT/2;
    
    car.vX = 0.0f;
    car.vY = 0.0f;

    car.aX = 0.0f;
    car.aY = 0.0f;

    car.speed = 0.0f;
    //Shit I'll use and don't know how to sector 

    double relativeFrequency = 0.0l;

    unsigned int waveCollisions = 0;
    
    double lastEmitTime = 0.0f;

    //Game loop or logic loop (I AM USING GRAPHS FOR THE FIRST TIME IDK WHAT TO CALL THIS)
    while (!WindowShouldClose()) {
        

        float dt = GetFrameTime(); //Btw I love how raylib uses pascal case they're accurate with their shit 
                                   // so I am trying to use camel case to reduce confusion between funcs

        double currentTime = GetTime();
            
            while(currentTime - lastEmitTime >= 0.50f) {
                emmitWave();
                lastEmitTime = GetTime();  // veya += 0.20 (catch-up için) lol I switched back to my native mid-coding and didn't even realize 
            }

        car.aX = 0.0f;
        car.aY = 0.0f;
        
        // 'Gameplay' 
        if (IsKeyDown(KEY_W)) {car.aY -= ACCELERATION; } //Attempt 1: Car yote itself out of fucking screen I floored the fucking gas car goes past mach god knows how much
        if (IsKeyDown(KEY_S)) {car.aY += ACCELERATION; } //Attempt 2: Car yote self more affectionetly
        if (IsKeyDown(KEY_D)) {car.aX += ACCELERATION; } //Attempt 3: I got blinded by the rings
        if (IsKeyDown(KEY_A)) {car.aX -= ACCELERATION; }
        if (IsKeyPressed(KEY_SPACE)) {car.vX = 0; car.vY = 0;} //Yeah a fucking absolute hand-break
        if (IsKeyPressed(KEY_ESCAPE)) {CloseWindow();} //And a yk...close the win button lol I use dwm and I was using Ctrl+C up until this point to terminate the program

        //Velocity updates
        car.vX += car.aX * dt; 
        car.vY += car.aY * dt;

        car.vX -= car.vX * FRICTION * dt; //So you don't yeet into orbit after reaching escape velocity
        car.vY -= car.vY * FRICTION * dt;

        //Position updates
        car.x += car.vX * dt;
        car.y += car.vY * dt;

        //Speed (magnitude update )
        car.speed = sqrt((car.vX*car.vX)+(car.vY*car.vX));
        expandWaves(dt);
        waveCollisions += checkObserverCollisions();


        BeginDrawing();
        ClearBackground(BLACK);
        drawVehicle(car);
        drawObserver(observer); // Works but no detection yet so it'll stay like this
        drawWaves();


        if (car.speed > WAVE_SPEED) 
        {
            DrawText("SUPER SONIC! BITCH!", (WIDTH/2)-5, 5, 25,(Color){13,53,15,150});
        }
        EndDrawing();
    }


    CloseWindow();

    return(0);
}


/*  Funciton bodies   */

void drawVehicle(Vehicle vehc)
{
    DrawCircle(vehc.x, vehc.y, 25, COOL_RED); //Ok! I just figured out how to give custom colors and picked a cool red 
    //#define PURPLE     CLITERAL(Color){ 200, 122, 255, 255 }  this line taken directly from raylib's header file they define colors like that RGB+transparency
    //You can use this as a template to define your own colors (CLITERAL isn't necessary ig since I didn't use it for COOL_RED but they added as const ig...)
}

 
void emmitWave(void)
{
    SoundWave newWave = {car.x, car.y, 0.0f,0}; //soundwaves comes from a source point hence the radius starts with 0.
    waves[waveCount % MAX_WAVES] = newWave;
    waveCount++;
}


//I searched internet for keeping track of buffer since it was causing UB and found what a ring buffer is and tried to implement (half mine, half copy-paste  )
void expandWaves(float dT)
{
    if (waveCount == 0) return;

    unsigned int activeWaves = (waveCount < MAX_WAVES) ? waveCount : MAX_WAVES;  //To keep track of the fucking waves
    unsigned int startIdx = (waveCount < MAX_WAVES) ? 0 : (waveCount % MAX_WAVES); //if the wave count is lower than MAX_VAVES start at 0 and if not start at where you left off 

    for (unsigned int i = 0; i < activeWaves; i++) {
        unsigned int idx = (startIdx + i) % MAX_WAVES;
        waves[idx].dRadius += WAVE_SPEED * dT;
    }
}

void drawWaves(void)
{
    if (waveCount == 0) return;

    unsigned int activeWaves = (waveCount < MAX_WAVES) ? waveCount : MAX_WAVES; //same logic
    unsigned int startIdx = (waveCount < MAX_WAVES) ? 0 : (waveCount % MAX_WAVES);

    for (unsigned int i = 0; i < activeWaves; i++) {
        unsigned int idx = (startIdx + i) % MAX_WAVES;
        
        DrawCircleLines(waves[idx].x, waves[idx].y, waves[idx].dRadius, DA_BLUE);
    }
}


void drawObserver(Rectangle obs)
{
    DrawRectangle(obs.x, obs.y, obs.width, obs.height,PURPLE);
}


unsigned int checkObserverCollisions(void)
{
    unsigned int collisionCount = 0;
    if (waveCount == 0) { return(0); }

    unsigned int activeWaves = (waveCount < MAX_WAVES) ? waveCount : MAX_WAVES;

    unsigned int startIdx = (waveCount < MAX_WAVES) ? 0 : (waveCount % MAX_WAVES);


    for (unsigned int i = 0; i < activeWaves; i++)
    {
        unsigned int idx = (startIdx + i) % MAX_WAVES;

        Vector2 center = {
            waves[idx].x,
            waves[idx].y
        };

        if (!waves[idx].isDetected && CheckCollisionCircleRec(center,waves[idx].dRadius,observer))
        {
            waves[idx].isDetected = 1;
            collisionCount++;
        }
    }
    return(collisionCount);
}