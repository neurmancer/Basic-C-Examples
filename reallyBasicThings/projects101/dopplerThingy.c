/*    Includes    */


#include <limits.h>
#include <raylib.h>


/*      Defines     */
#define WIDTH 1280.0 //Since I am using floats everywhere for position .0 (or explicit casting is a better way to shut cc warnings)
#define HEIGHT 960.0

#define FPS 60

#define MAX_WAVES 32 //Overkill? We'll see...
#define WAVE_VELOCITY 20 //Should I use vel or speed? I mean... does a circle has vector? or just magnitude? it expands outwards...is that even a vector? 

#define COOL_RED (Color){70 , 0 , 2, 255}

/*              Sup? Got bored again and math fuckery wasn't enough...so here we are learning a 'framework' or lib I don't know what to call 
                but I am using raylib as you can see...
                Important shit:
                1- you need to have raylib.h in your system I used pacman -S raylib and it worked so I assume apt-get and dnf will work too... as always windows can suck mine
                2- you gotta compile with -lraylib to link raylib (duh)
                3- We're building a Doppler Effect Demonstrator/Simulator and I have no idea why the fuck I am doing this it's 00AM I ask questioning after 11PM
                4- I am using this cheat sheet from raylib https://www.raylib.com/cheatsheet/cheatsheet.html for seeing shit and funny enough? They're explaining as if I am an idiot and I am a sucker for it
                (thx for making my job easy raylib...)

                5- Since this is the first file in the repo requring external dependency (raylib) I am improvising the notation a little such as sectioning like defines,includes and shit


                Now the real tea...Wtf is doppler effect?
                It is the  change in the frequency or pitch of a wave in relation to an observer who is moving relative to the wave's source 
                so if an ambulance is coming towards you you'll hear a higher pitch and if it's going further away the pitch will lower 
                did I simulate it? Kinda visually but nah there is no frequency or wavelength detection in this program is there a math involved? Fuck yeah!
                I basically made a ball that you can move with WASD and it creates rings around itself no acceleration no visible pitch change and shit 
                But lowering part of the pitch (which is the part where rings gets further apart behind the ball is solid)
                I may add 
                1- A rectangle representing an observer on a random point 
                2- An acceleration element to the car
                3- Sprites for fun 
                4- Or turn this graph based thing into a CLI program for love of the game

                and before I dip (since it's fucking 2.30AM) doppler effect isn't a thing only applied to sound waves it applies to all waves...
                in fact we determine the relative positions of celestial bodies using doppler if you heard the term blueshift and redshift...this is exactly doppler effect applied on electromagnetic waves
                Redshift when the source getting further (lower frequency)
                Blueshift is when the source getting closer (higher frequency)

*/


/*      Objects(or Structs)     */

typedef struct{
    float x;
    float y;
    //Coordinates of the vehicle 
}Vehicle;

typedef struct{
    //first, Float because I want shit to move smooth. 
    // Second, dRadius instead of radius because it'll change over time and delta is literally the 'displacment' notation  
    float x;
    float y;
    float dRadius; 

}SoundWave; //I tried using Wave as var name but it conflicted with a raylib definition ig so we're going with soundwave 

/* Declarations */

void drawVehicle(Vehicle vehc);

void emmitWave(void);
void drawWaves(void);
void expandWaves(float dT);

/* Global Vars  (I dunno how many I'll have but here it is)*/

Vehicle car = { 0 };

unsigned int waveCount = 0; 
SoundWave waves[MAX_WAVES] = { 0 }; //Those are just empty array declaration... a habit of mine, don't mind...

int main(void)
{
    // CLITERAL(Color){ 0 }

    //Tweaks
    InitWindow(WIDTH, HEIGHT ,"Doppler Thingy");
    SetTargetFPS(FPS);

    car.x = WIDTH/2;
    car.y = HEIGHT/2;


    float waveFreq = 0.0f;
    //Game loop or logic loop (I AM USING GRAPHS FOR THE FIRST TIME IDK WHAT TO CALL THIS)
    while (!WindowShouldClose()) {
        

        float dt = GetFrameTime(); //Btw I love how raylib uses pascal case they're accurate with the shit so I am trying to use camel case to reduce confusion between funcs
        waveFreq+=dt;
        if ((waveFreq) > 0.25f) {
            emmitWave();
            waveFreq = 0.0f; //I love explicitly casting types to see the data type of the var. 
        }
        
        // 'Gameplay' 
        if (IsKeyDown(KEY_W)) {car.y -= 0.70f; }
        if (IsKeyDown(KEY_S)) {car.y += 0.70f; }
        if (IsKeyDown(KEY_D)) {car.x += 0.70f; }
        if (IsKeyDown(KEY_A)) {car.x -= 0.70f; }
        
        expandWaves(dt);

        BeginDrawing();
        ClearBackground(BLACK);
        drawVehicle(car);
        drawWaves();
        
        EndDrawing();
    }


    return(0);
}


/*  Funciton bodies   */

void drawVehicle(Vehicle vehc)
{
    DrawCircle(vehc.x, vehc.y, 25, COOL_RED); //Ok! I just figured out how to give custom colors and picked a cool red 
}


void emmitWave(void)
{
    SoundWave newWave = {car.x, car.y, 0.0f}; //soundwaves comes from a source point hence the radius starts with 0
    waves[waveCount % MAX_WAVES] = newWave;
    waveCount++;
}

void expandWaves(float dT)
{
    if (waveCount == 0) return;

    unsigned int activeWaves = (waveCount < MAX_WAVES) ? waveCount : MAX_WAVES;  //To keep track of the fucking waves
    unsigned int startIdx = (waveCount < MAX_WAVES) ? 0 : (waveCount % MAX_WAVES);

    for (unsigned int i = 0; i < activeWaves; i++) {
        unsigned int idx = (startIdx + i) % MAX_WAVES;
        waves[idx].dRadius += WAVE_VELOCITY * dT;
    }
}

void drawWaves(void)
{
    if (waveCount == 0) return;

    unsigned int activeWaves = (waveCount < MAX_WAVES) ? waveCount : MAX_WAVES;
    unsigned int startIdx = (waveCount < MAX_WAVES) ? 0 : (waveCount % MAX_WAVES);

    for (unsigned int i = 0; i < activeWaves; i++) {
        unsigned int idx = (startIdx + i) % MAX_WAVES;
        
        DrawCircleLines(waves[idx].x, waves[idx].y, waves[idx].dRadius, VIOLET);
    }
}