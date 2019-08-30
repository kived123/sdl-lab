#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Map.h"


const int V_WALL=2;
const int H_WALL=1;

Map::Map():cells(0),width(-1),height(-1), dir(WEST)
{
  for (int i=0; i<4; i++)
    walls[i] = false;
}

bool Map::LoadFromFile(const char * path)
{
   std::ifstream file(path);

   map_buffer_desc mbd;
  
  
   std::string str;         
   int m=0;
   std::vector<int> data;
   while(getline(file,str)) {
     switch(m){
       case 0:mbd.width = atoi(str.c_str());break;
       case 1:mbd.height = atoi(str.c_str());break;	
       default:
         for (char c : str){
           if (c>='0' && c<='3') {
              data.push_back(c-'0'); 
            } else {
              std::cout << "invalid char" << c  << std::endl;
	      return false;
            }
             
           
           
         }
    }    
    if (m<2) m++;
   }
   if (m<2){
       std::cout << "Reading map failed"  << std::endl;
       return false;
   }	

   int size = data.size();
   int exp_size = mbd.width*mbd.height;
   if (size!=exp_size) {
       std::cout << "Expected " << exp_size << " elemets, giving "<< size << std::endl;
       return false;       
   }

   

   std::cout << "map width" << mbd.width << std::endl;
   std::cout << "map height" << mbd.height << std::endl;
   for (int x:data) {
      std::cout << x  << " ";
   }
   std::cout << std::endl;
   mbd.pData = &data[0];


   return LoadFromMemory(mbd); 
}

bool Map::LoadFromMemory(const map_buffer_desc& mbd)
{
  if (mbd.width<=0 || mbd.height<=0 || mbd.pData==0) {
    return false;
  }

  cells = new int*[mbd.height];
  for (int row=0, i=0;row<mbd.height; row++){
    cells[row] = new int[mbd.width];
    for (int col=0; col<mbd.width; col++) {
      cells[row][col] = mbd.pData[i++];
    }
  }

  width = mbd.width;
  height = mbd.height;
  return true;
}

bool Map::MoveTo(int x, int y)
{
  if ( cells == 0 ) {
    return false;
  }

  bool ret=false;

  if ((x>=0 && x<width) && (y>=0 && y<height))
  {
    walls[WEST] = (x==0) || ((cells[y][x] & V_WALL)!=0);
    walls[NORTH] = (y==0) || ((cells[y][x] & H_WALL)!=0);

    if (x==width-1) {
      walls[EAST] = true;
    } else {
      walls[EAST] = (cells[y][x+1] & V_WALL) !=0 ;
    }

    if (y==height-1) {
      walls[SOUTH] = true;
    } else {
      walls[SOUTH] = (cells[y+1][x] & H_WALL) !=0;
    }

    ret = true;
  }
  return ret;
}

bool Map::Wall(int side) const
{
  if (side>=WEST && side<=SOUTH)
    return walls[side];

  switch (side) {
    case FRONT:
      return walls[dir.value()];
    case RIGHT:
      return walls[dir.right().value()];
    case LEFT:
      return walls[dir.left().value()];
    case REAR:
      return walls[dir.opposite().value()];
  }
  return false;
}

Map::~Map()
{
   for (int row=0; row<height; row++)
     delete[] cells[row];
   delete[] cells;
}
