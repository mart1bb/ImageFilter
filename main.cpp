#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace sf;
using namespace std;

#pragma region variables
RenderWindow window;

#pragma endregion variables
void BW(Image& img);
void flou(Image& img);
void tracer(Image& img, int& x, int& y);

int main()
{
    window.create(VideoMode(1000, 800), "Image Filter");
    
    // Variables
        // Images var
            Texture texture;
            Sprite sprite;
            Image img;
        //

        // FPS + Size var
            Clock clock;
            float nbFps;
            int nbFpsInt;
            Vector2u size;
            Font font;
            Text fps;
        //
        
        // Images set up
            img.loadFromFile("images/PSize.jpg");
            // img.create(800,600, Color::White);
            texture.loadFromImage(img);
            sprite.setTexture(texture);
            sprite.setPosition(100.0f,100.0f);
            
            int x = img.getSize().x/2;
            int y = img.getSize().x/2;
        //

        // FPS + Size set up
            font.loadFromFile("font/OoohBaby-Regular.ttf");
            fps.setFont(font);
            fps.setCharacterSize(24);
            fps.setColor(Color::White);
            fps.setStyle(Text::Bold);
        //
    //
    window.setFramerateLimit(200);

    // process one time
        
    //

    texture.loadFromImage(img);
    sprite.setTexture(texture);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Update
            // FPS + Size
                nbFps = floor(1/(clock.restart().asSeconds()));
                nbFpsInt = floor(nbFps);
                string strFps = to_string(nbFpsInt);
                size = window.getSize();
                string strX = to_string(size.x);
                string strY = to_string(size.y);
                fps.setString("X = " + strX + ", FPS = "+ strFps +  "\nY = " + strY);
            //

            // Img process while window open

            //
        //

        // Draw
        window.clear();
        window.draw(fps);
        window.draw(sprite);
        window.display();

        
    }
}

void tracer(Image& img, int& x, int& y){
    img.setPixel(x,y,Color::Black);
    Color tc[8];
    if(y > 0){
        tc[0] = img.getPixel(x,y-1);
    }
    if(y > 0 && x < img.getSize().x-1){
        tc[1] = img.getPixel(x+1,y-1);
    }  
    if(y > 0 && x > 0){
        tc[7] = img.getPixel(x-1,y-1);
    }
    if(y < img.getSize().y-1 && x < img.getSize().x-1){ 
        tc[3] = img.getPixel(x+1,y+1);
    } 
    if(x < img.getSize().x-1){
        tc[2] = img.getPixel(x+1,y);
    } 
    if(x > 0 && y < img.getSize().y-1){
        tc[5] = img.getPixel(x-1,y+1);
    }   
    if(y < img.getSize().y-1){
        tc[4] = img.getPixel(x,y+1);
    }
    if(y > 0){
        tc[6] = img.getPixel(x-1,y);
    }    
        
    float tf[8];
    int g = 1000;
    int f = 7;
    for(int i = 0; i<7 ; i++){
        tf[i] = tc[i].r+tc[i].g+tc[i].g;
        if(tf[i] < g && tf[i] != 0){
            f = i;
            g = tf[i];
        }
    }

    if(f == 0){
        y = y-1;
    } else if(f == 1){
        x = x+1;
        y = y-1;
    }else if(f == 2){
        x = x+1;
    } else if(f == 3){
        x = x+1;
        y = y+1;
    } else if(f == 4){
        y = y+1;
    } else if(f == 5){
        x = x-1;
        y = y+1;
    } else if(f == 6){
        x = x-1;
    } else{
        x = x-1;
        y = y-1;
    }
}

void flou(Image& img){
    for(int i = 0 ; i < img.getSize().x-1 ; i++){
        for(int j = 0 ; j < img.getSize().y-1 ; j++){
            Color pre = img.getPixel(i,j);
            Color post = img.getPixel(i,j+1);
            Color pre2 = img.getPixel(i+1,j);
            Color post2 = img.getPixel(i+1,j+1);
            img.setPixel(i,j,Color((post.r+pre.r+post2.r+pre2.r)/4,(post.g+pre.g+post2.g+pre2.g)/4,(post.b+pre.b+post2.b+pre2.b)/4));
            img.setPixel(i,j+1,Color((post.r+pre.r+post2.r+pre2.r)/4,(post.g+pre.g+post2.g+pre2.g)/4,(post.b+pre.b+post2.b+pre2.b)/4));
            img.setPixel(i+1,j+1,Color((post.r+pre.r+post2.r+pre2.r)/4,(post.g+pre.g+post2.g+pre2.g)/4,(post.b+pre.b+post2.b+pre2.b)/4));
            img.setPixel(i+1,j,Color((post.r+pre.r+post2.r+pre2.r)/4,(post.g+pre.g+post2.g+pre2.g)/4,(post.b+pre.b+post2.b+pre2.b)/4));
        }
    }
}

void BW(Image& img){
    // Clock clock;
    // float n1 = clock.restart().asSeconds();
    for(int i = 0 ; i < img.getSize().x ; i++){
        for(int j = 0 ; j < img.getSize().y ; j++){
            Color old = img.getPixel(i,j);
            float moy = (old.r+old.b+old.g)/3;
            img.setPixel(i,j,Color(moy,moy,moy));
        }
    }
}