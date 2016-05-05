#include "rectStash.h"
//#include "C:\Users\Brian\Desktop\finalv2\freeglutapp\Simple OpenGL Image Library\lib\SOIL.h"

float zCord = 0.99;
int numSelect = 0;

time_t rawtime;
struct tm * timeinfo;

mainMenu myMenu;
vector <Game*> myGames;
time_t timer;
float miliseconds;
bool remake;

//GLuint bg;

AppWindow::AppWindow ( const char* label, int x, int y, int w, int h )
          :GlutWindow ( label, x, y, w, h )
 {
   _markx = 0;
   _marky = 0;
   addMenuEntry ( "Option 0", evOption0 );
   addMenuEntry ( "Option 1", evOption1 );
   srand (time(NULL));

   DodgingSpikes* tempGame1 = new DodgingSpikes();
   myGames.push_back(tempGame1);

   PuzzleTiles* tempGame2 = new PuzzleTiles();
   myGames.push_back(tempGame2);

   BrickBreaker* tempGame3 = new BrickBreaker;
   myGames.push_back(tempGame3);

   Invaders* tempGame4 = new Invaders();
   myGames.push_back(tempGame4);

   remake = false;

   PlaySound("Runescape.wav", NULL, SND_LOOP | SND_ASYNC);

}

// mouse events are in window coordinates, but your scene is in [0,1]x[0,1],
// so make here the conversion when needed
void AppWindow::windowToScene ( float& x, float &y )
 {
   x = (2.0f*(x/float(_w))) - 1.0f;
   y = 1.0f - (2.0f*(y/float(_h)));
 }

// Called every time there is a window event
void AppWindow::handle ( const Event& e )
 {

   bool rd=true;

   if ( e.type==Keyboard ) 
    switch ( e.key )
    { 

	  case 27: // Esc was pressed
	   exit(1);
	   break;

	  case ' ':
			  if (!myMenu.notPlaying)
			  {
				  for (unsigned int i = 0; i < myGames.size(); ++i)
				  {
					  if (myGames[i]->playCheck)
					  {
						  myGames[i]->keyboard(e.key);
						  break;
					  }
				  }
			  }


	  		else if (myMenu.notPlaying)
	  		{	
	  				  for (unsigned int i = 0; i < myMenu.myGameRects.size(); i++) {
	  		
	  					  if (myMenu.myGameRects[i].focus) {
	  		
	  						  myGames[i]->playCheck = true;
	  						  myMenu.notPlaying = false;

							  PlaySound(NULL, NULL, SND_LOOP | SND_ASYNC);

	  						  if (i == 0) {
	  		
	  							  myGames[0]->msStart = miliseconds;
	  							  myGames[0]->msEnd = myGames[0]->msStart + 133.5;
								  PlaySound("Clubstep.wav", NULL, SND_ASYNC);
	  							remake = true;
	  						  }
	  		
	  						  if (i == 1) {
	  		
	  							  myGames[1]->startTime = time(NULL);
	  							  myGames[1]->endTime = myGames[i]->startTime + 180; // sliding tiles for 3 mins
	  							remake = true;
	  						  }
	  		
	  						  if (i == 2) {
	  		
								  myGames[2]->msStart = miliseconds;
								  myGames[2]->msEnd = myGames[2]->msStart + 500;
	  							remake = true;
	  						  }
	  		
	  						  if (i == 3) {
	  		
	  							  myGames[3]->startTime = time(NULL);
	  							  myGames[3]->endTime = myGames[i]->startTime + 120; // sliding tiles for 2 mins
	  							remake = true;
	  						  }
	  						  
	  		
	  					  }
	  		
	  				}

	  		}

	}

   if (e.type == Motion) {

	   float old_markx = _markx;
	   float old_marky = _marky;
	   _markx = (float)e.mx;
	   _marky = (float)e.my;
	   windowToScene(_markx, _marky);
	   float xChange = _markx - old_markx;
	   float yChange = _marky - old_marky;

	   Vec mouseCords(_markx, _marky);

	   if (!myMenu.notPlaying) {

		   for (unsigned int i = 0; i < myGames.size(); i++) {

			   myGames[i]->motion(xChange, yChange);

		   }

	   }


   }

   if ( e.type==MouseDown /*|| e.type==Motion*/) // motion is uncessary?
    { 
	float old_markx = _markx;
	float old_marky = _marky;
	_markx=(float)e.mx;
    _marky=(float)e.my;
    windowToScene(_markx,_marky);

	  int containCheck1 = 0;
	  int containCheck2 = 0;
	  int containCheck3 = 0;
	  float xChange = _markx - old_markx;
	  float yChange = _marky - old_marky;
	  Vec mouseCords(_markx, _marky);

	  if (myMenu.notPlaying) {

		  if (myMenu.coinCount == '0') {	// Retry option

			  if (myMenu.retry.contains(mouseCords)) {

				  myMenu.attemptCount++;
				  myMenu.coinCount = '1';
				  myMenu.gameCount = '0';

				  if (myMenu.attemptCount > '9') {

					  exit(1);

				  }

			  }

			  else {

				  exit(1);

			  }

		  }

	  }

	  if (myMenu.notPlaying) {

		  for (unsigned int i = 0; i < myMenu.myGameRects.size(); i++) {	// Selecting/Deselecting Game Rectangles

			  containCheck1 = myMenu.myGameRects[i].contains(mouseCords);

			  if (containCheck1 == 1) {

				  myMenu.myGameRects[i].focus = true;
				  myMenu.difficultly = i + 1;

				  for (unsigned int j = i + 1; j < myMenu.myGameRects.size(); j++) {

					  myMenu.myGameRects[j].focus = false;

				  }

			  }

			  if ((containCheck1 == 0) && (myMenu.myGameRects[i].focus)) {

				  myMenu.myGameRects[i].focus = false;
				  myMenu.difficultly = 0;

			  }

		  }

		}
		// if a game is playing, send mouse event to game
		else {

			for (unsigned int i = 0; i < myGames.size(); ++i) {

				if (myGames[i]->playCheck) {

					myGames[i]->click(_markx,_marky);
					break;

				}

			}

		}

    }

   if ( e.type==Menu )
    { std::cout<<"Menu Event: "<<e.menuev<<std::endl;
      rd=false; // no need to redraw
    }

   const float incx=0.02f;
   const float incy=0.02f;
   if ( e.type==SpecialKey )
    switch ( e.key )
    { case GLUT_KEY_LEFT:
		if (!myMenu.notPlaying)
		{
			for (unsigned int i = 0; i < myGames.size(); ++i)
			{
				if (myGames[i]->playCheck)
				{
					myGames[i]->keyboard('a');
					myGames[i]->leftKey(true);
					break;
				}
			}
		}
		break;
      case GLUT_KEY_RIGHT:
		  if (!myMenu.notPlaying)
		  {
			  for (unsigned int i = 0; i < myGames.size(); ++i)
			  {
				  if (myGames[i]->playCheck)
				  {
					  myGames[i]->keyboard('d');
					  myGames[i]->rightKey(true);
					  break;
				  }
			  }
		  }
		  break;
      case GLUT_KEY_UP:    _marky+=incy; break;
      case GLUT_KEY_DOWN:  _marky-=incy; break;
      default: rd=false; // no redraw
	}

   if (rd) redraw(); // ask the window to be rendered when possible
}

void AppWindow::resize ( int w, int h )
 {
   // Define that OpenGL should use the whole window for rendering
   glViewport( 0, 0, w, h );
   _w=w; _h=h;
 }

// here we will redraw the scene according to the current state of the application.
void AppWindow::draw ()
 {
   // Clear the rendering window
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   // Clear the trasnformation stack
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();


   glColor3d ( 0.0, 1.0, 1.0 );

   // Draw a cross
   const double s=0.05;
   glBegin ( GL_LINES );
   glVertex2d ( _markx-s, _marky );
   glVertex2d ( _markx+s, _marky );
   glVertex2d ( _markx, _marky-s );
   glVertex2d ( _markx, _marky+s );
   glEnd();


	if (myGames[0]->playCheck) {

		myMenu.coinCount = myGames[0]->play();

	}

	else if (myGames[1]->playCheck) {

		myMenu.coinCount = myGames[1]->play();

	}

	else if (myGames[2]->playCheck) {

		myMenu.coinCount = myGames[2]->play();

	}

	else if (myGames[3]->playCheck) {

		myMenu.coinCount = myGames[3]->play();

	}

	else {

		if (remake)
		{
			for(unsigned int i = 0; i < myGames.size(); ++i)
			{
				delete myGames[i];
			}

			myGames[0] = new DodgingSpikes();

			myGames[1] = new PuzzleTiles();

			myGames[2] = new BrickBreaker;

			myGames[3] = new Invaders();

			myMenu.notPlayed = true;

			remake = false;
		}

		myMenu.notPlaying = true;
		myMenu.draw();

	}


   // Swap buffers
   glFlush();         // flush the pipeline (usually not necessary)
   glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}

void GlutWindow::glutIdleCB()
{
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	myMenu.currentTime = asctime(timeinfo);

	miliseconds = glutGet(GLUT_ELAPSED_TIME);
	miliseconds = miliseconds / 1000;

	glutPostRedisplay(); //Redraws

}

