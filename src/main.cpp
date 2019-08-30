

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <iostream>
#include "Renderer.h"
#include "Phys.h"
#include "Router.h"
#include "Rndroute.h"

SDL_Window *mainWindow;
SDL_GLContext mainContext;

void Frame();
bool InitGL();
void Cleanup();
void MainLoop();
renderer * r;
IRouter *router;
Phys * phys;


void Frame()
{
  
   if (phys->isUpdate())
   {
         RouteItem ri = router->getRouteItem();
         phys->Reset(ri);
         router->Next();
   }
   int ticks = SDL_GetTicks();

   phys->Frame(ticks);
   //std::cout << ticks << std::endl;
   r->Pos(phys->getX(),phys->getY());
   r->LookAt(phys->getLookPosX(),phys->getLookPosY());
   r->frame();
   SDL_GL_SwapWindow(mainWindow);
}

bool InitGL()
{
   if (SDL_Init(SDL_INIT_VIDEO)  < 0 )
   {
      std::cout << "SDL_Init Failed" << std::endl;
      return false;
   }

   mainWindow = SDL_CreateWindow("Labyrinth SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		  WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
   if (!mainWindow)
   {
      std::cout << "SDL_CreateWindow Failed" << std::endl;
      return false;
   }

   mainContext = SDL_GL_CreateContext(mainWindow);

   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


   	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);


   	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);



   	glEnable(GL_DEPTH_TEST);

   if (glewInit() != GLEW_OK)
   {
	   std::cout << "SDL_CreateWindow Failed" << std::endl;
	   return -1;
   }


   SDL_GL_SetSwapInterval(1);

   return true;
}


void Cleanup()
{
   SDL_GL_DeleteContext(mainContext);

   SDL_DestroyWindow(mainWindow);

   SDL_Quit();
}

void MainLoop()
{
   while(true)
   {
      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
         if (event.type == SDL_QUIT) return;
      }
      Frame();
   }

}

int main(int argc, char *argv[])
{
	
	Map map;

    if (!map.LoadFromFile("Data/map"))
       return false;

    router =new RandomRouter(0,0,EAST) ;
    if (!router->Create(map)) {
        std::cout << "Create rout failed" << std::endl;
        return false;
    }

    phys = new Phys(1.5f,1.5f, EAST);
r = new renderer();
   if (!InitGL())
     return -1;
   r->init(map);


   MainLoop();

   Cleanup();
   delete r;
   delete phys;
   delete router;
   return 0;
}



