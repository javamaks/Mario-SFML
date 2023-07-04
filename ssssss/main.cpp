#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;


float offsetX=0, offsetY=0;


const int H = 17;
const int W = 150;


String TileMap[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                                                                                                                                    0",
"0                                                                                    w                                                               0",
"0                   w                                  w                   w                                                                         0",
"0                                      w                                       kk                                                                    0",
"0                                                                             k  k    k    k                                                         0",
"0                      c                                                      k      kkk  kkk  w                                                     0",
"0                                                                       r     k       k    k                                                         0",
"0                                                                      rr     k  k                                                                   0",
"0                                                                     rrr      kk                                                                    0",
"0               c    kckck                                           rrrr                                                                            0",
"0                                      t0                           rrrrr                                                                            0",
"0G                                     00              t0          rrrrrr            G                                                               0",
"0           d    g       d             00              00         rrrrrrr                                                                            0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
}; 


class PLAYER
{
public:
float dx,dy;
FloatRect rect;
bool onGround;
Sprite sprite;
float currentFrame;
bool life;



    PLAYER(Texture &image) //конструктор
   {
	sprite.setTexture(image);
	rect = FloatRect(100,180,16,16);

	dx=dy=0.1;
	currentFrame = 0;
   }


   void update(float time)
   {	

	 rect.left += dx * time;	
     Collision(0);
   

	 if (!onGround) dy=dy+0.0005*time;	
	 rect.top += dy*time;
	 onGround=false;
     Collision(1);
	

     currentFrame += time * 0.005;
     if (currentFrame > 3) currentFrame -= 3;


    if (dx>0) sprite.setTextureRect(IntRect(112+31*int(currentFrame),144,16,16));
	if (dx<0) sprite.setTextureRect(IntRect(112+31*int(currentFrame)+16,144,-16,16));
  

	 sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	  
	 dx=0;
   }


   void Collision(int num)
{
	
	for (int i = rect.top/16 ; i<(rect.top+rect.height)/16; i++)
		for (int j = rect.left/16; j<(rect.left+rect.width)/16; j++)
			 {
				 if ((TileMap[i][j]=='P') || (TileMap[i][j]=='k') || (TileMap[i][j]=='0') || (TileMap[i][j]=='r') || (TileMap[i][j]=='t'))
				                         { 
												   if (dy>0 && num==1)
												   { rect.top =   i*16 -  rect.height;  dy=0;   onGround=true; }
											       if (dy<0 && num==1)
												   { rect.top = i*16 + 16;   dy=0;}
												   if (dx>0 && num==0)
												   { rect.left =  j*16 -  rect.width; }
											       if (dx<0 && num==0)
												   { rect.left =  j*16 +16;}
										 }

				 if (TileMap[i][j]=='c') {
												 // TileMap[i][j]=' '; 
			                          	 }
			 }

}

};

class ENEMY
{

public:
	float dx,dy;
FloatRect rect;
bool onGround;
Sprite sprite;
float currentFrame;
bool life;
   void set(Texture &image, int x, int y)
   {
	sprite.setTexture(image);
	rect = FloatRect(x,y,16,16);

    dx=0.05;
	currentFrame = 0;
	life=true;
   }

   void update(float time)
   {	
	 rect.left += dx * time;
	
     Collision();
  

     currentFrame += time * 0.005;
     if (currentFrame > 2) currentFrame -= 2;

    sprite.setTextureRect(IntRect(18*int(currentFrame),   0, 16,16));
    if (!life) sprite.setTextureRect(IntRect(58, 0, 16,16));


	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	  
   }


   void Collision()
  {

	for (int i = rect.top/16 ; i<(rect.top+rect.height)/16; i++)
		for (int j = rect.left/16; j<(rect.left+rect.width)/16; j++)
			 if ((TileMap[i][j]=='P') || (TileMap[i][j]=='0'))
			                           { 
                                                    if (dx>0)
												   { rect.left =  j*16 - rect.width; dx*=-1; }
											        else if (dx<0)
												   { rect.left =  j*16 + 16;  dx*=-1; }
											
										}
  }

};



int main()
{  

    RenderWindow window(VideoMode(400, 250), "SFML works!");

	Texture tileSet;
	tileSet.loadFromFile("Mario_Tileset.png");
	
	PLAYER Mario(tileSet);
	ENEMY  enemy;
	enemy.set(tileSet,48*16,13*16);

	Sprite tile(tileSet);

	SoundBuffer buffer;
	buffer.loadFromFile("Jump.ogg");
	Sound sound(buffer);




	Texture menu_texture1,menu_texture2,menu_texture3,about_texture;
	menu_texture1.loadFromFile("111.png");
	menu_texture2.loadFromFile("222.png");
    menu_texture3.loadFromFile("333.png");
	about_texture.loadFromFile("about.png");
	Sprite menu1(menu_texture1),menu2(menu_texture2),menu3(menu_texture3),about(about_texture);
	bool Menu=1;
	int MenuNum=0;
	menu1.setPosition(100,30);
	menu2.setPosition(100,90);
    menu3.setPosition(100,150);


	/////меню
	while(Menu)
	{	   
	   menu1.setColor(Color::White);
	   menu2.setColor(Color::White);
	   menu3.setColor(Color::White);
	   MenuNum=0;
	   window.clear(Color(0,0,0));

	   if (IntRect(100,30,300,50).contains(Mouse::getPosition(window))) {menu1.setColor(Color::Yellow); MenuNum=1;}
       if (IntRect(100,90,300,50).contains(Mouse::getPosition(window))) {menu2.setColor(Color::Yellow); MenuNum=2;}
       if (IntRect(100,150,300,50).contains(Mouse::getPosition(window))) {menu3.setColor(Color::Yellow); MenuNum=3;}

	   if (Mouse::isButtonPressed(Mouse::Left))
	     {
			 if (MenuNum==1) Menu=false;
			 if (MenuNum==2) {window.draw(about); window.display(); while(!Keyboard::isKeyPressed(Keyboard::Escape)) ;}
			 if (MenuNum==3)  {window.close();Menu=false;}

	     }

	   
		    window.draw(menu1);
            window.draw(menu2);
			window.draw(menu3);

		window.display();
	}
    ////////////////

	Music music;
    music.openFromFile("Mario_Theme.ogg");
    music.play();

	Clock clock;

    while (window.isOpen())
    { 
		
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time/500;  // здесь регулируем скорость игры

		if (time > 20) time = 20; 

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)      
                window.close();
		}


		if (Keyboard::isKeyPressed(Keyboard::Left))    Mario.dx=-0.1; 
       
	    if (Keyboard::isKeyPressed(Keyboard::Right))    Mario.dx=0.1;
    
	    if (Keyboard::isKeyPressed(Keyboard::Up))	if (Mario.onGround) { Mario.dy=-0.27; Mario.onGround=false;  sound.play();}
	 



		 Mario.update(time);
		 enemy.update(time);


		 if  (Mario.rect.intersects( enemy.rect ) )
		 {
			 if (enemy.life) {
			 if (Mario.dy>0) { enemy.dx=0; Mario.dy=-0.2; enemy.life=false;}
			 else Mario.sprite.setColor(Color::Red);
			 }
		 }


		 if (Mario.rect.left>200) offsetX = Mario.rect.left-200;           //смещение




		 window.clear(Color(107,140,255));

		 for (int i=0; i<H; i++)
			 for (int j=0; j<W; j++)
			  { 
				if (TileMap[i][j]=='P')  tile.setTextureRect( IntRect(143-16*3,112,16,16) );

				if (TileMap[i][j]=='k')  tile.setTextureRect( IntRect(143,112,16,16) );
				                                 
   			    if (TileMap[i][j]=='c')  tile.setTextureRect( IntRect(143-16,112,16,16) );

				if (TileMap[i][j]=='t')  tile.setTextureRect( IntRect(0,47,32,95-47) );

				if (TileMap[i][j]=='g')  tile.setTextureRect( IntRect(0,16*9-5,3*16,16*2+5) );

				if (TileMap[i][j]=='G')  tile.setTextureRect( IntRect(145,222,222-145,255-222) );

			    if (TileMap[i][j]=='d')  tile.setTextureRect( IntRect(0,106,74,127-106) );

				if (TileMap[i][j]=='w')  tile.setTextureRect( IntRect(99,224,140-99,255-224) );

				if (TileMap[i][j]=='r')  tile.setTextureRect( IntRect(143-32,112,16,16) );

				if ((TileMap[i][j]==' ') || (TileMap[i][j]=='0')) continue;

  			    tile.setPosition(j*16-offsetX,i*16 - offsetY) ; 
		        window.draw(tile);
		     }
		 


		window.draw(Mario.sprite);
	    window.draw(enemy.sprite);

		window.display();
    }

    return 0;
}



