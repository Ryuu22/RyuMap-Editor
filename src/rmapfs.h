#include <fstream>
#include <iostream>

namespace rmapfs {
    struct Vector2int
    {
    	Vector2int(){}
    	Vector2int(short int xi, short int yi)
    	{
    		x = xi;
    		y = yi;
    	}
    	short int x;
    	short int y;
    };

    class MapTile{
    public:
    	unsigned short int x;
    	unsigned short int y;

    	unsigned short int type;

    	MapTile(){}
    	MapTile(short int newx, short int newy, unsigned short int newtype){
    		x = newx;
    		y = newy;
    		type = newtype;
    	}
    };

    void loadMap()
    {

        std::fstream myFile;
        myFile.open ("data.rmap", std::ios::in | std::ios::binary);

        //Read file header
        char header[4];
    	char version[4];
    	int tileSetID;

        myFile.read((char*)&header, sizeof(header));
        myFile.read((char*)&version, sizeof(version));
        myFile.read((char*)&tileSetID, sizeof(tileSetID));

        //Read map size
    	Vector2int mapsize;
        myFile.read((char*)&mapsize.x, sizeof(mapsize.x));
        myFile.read((char*)&mapsize.y, sizeof(mapsize.y));

        //Read the actual map data
    	MapTile map[mapsize.x][mapsize.y];

        for (int i = 0; i < mapsize.x; ++i)
        {
            for (int j = 0; j < mapsize.y; ++j)
            {
            	unsigned short int x;
            	unsigned short int y;
            	unsigned short int type;
        	    myFile.read((char*)&x, sizeof(x));
        	    myFile.read((char*)&y, sizeof(y));
        	    myFile.read((char*)&type, sizeof(type));

        	    map[i][j] = MapTile(x, y , type);
            }
        }


    	std::cout << "Header: "<< header << std::endl;
    	std::cout << "Map size: "<< mapsize.x << "x" << mapsize.y << std::endl;

        for (int i = 0; i < mapsize.x; ++i)
        {
            for (int j = 0; j < mapsize.y; ++j)
            {
            	std::cout << " " << map[i][j].type;
            }
            std::cout << std::endl;
        }

        myFile.close();
    }
    void saveMap()
    {
    	Vector2int mapsize = Vector2int(10,10);

    	MapTile map[mapsize.x][mapsize.y];
    	//GENERATE tile array
        for (int i = 0; i < mapsize.x; ++i)
        {
            for (int j = 0; j < mapsize.y; ++j)
            {
                map[i][j].x = i * 64;
                map[i][j].y = j * 64;

                if(i % 2) map[i][j].type = 0;
                else map[i][j].type = 5;

            }
        }


    	char header[4] = {82,77,65,80}; //RMAP in ascii
    	char version[4] = {118,48,50,48}; //Version of the program << v0.2.0

    	int tileSetID = 2;


        std::fstream myFile;
        myFile.open ("data.rmap", std::ios::out | std::ios::binary);

        //Write header signature for our RMAP file (4bytes)
        myFile.write(reinterpret_cast<const char *>(&header), sizeof(header));

        myFile.write(reinterpret_cast<const char *>(&version), sizeof(version));
        myFile.write(reinterpret_cast<const char *>(&tileSetID), sizeof(tileSetID));

        //Write mapsize (2 + 2 bytes)
        myFile.write(reinterpret_cast<const char *>(&mapsize), sizeof(mapsize));



        //Write map data block by block
        for (int i = 0; i < mapsize.x; ++i)
        {
            for (int j = 0; j < mapsize.y; ++j)
            {
        		myFile.write(reinterpret_cast<const char *>(&map[i][j].x), sizeof(map[i][j].x));
        		myFile.write(reinterpret_cast<const char *>(&map[i][j].y), sizeof(map[i][j].y));
        		myFile.write(reinterpret_cast<const char *>(&map[i][j].type), sizeof(map[i][j].type));
            }
        }

        std::cout << "Done";

        myFile.close();
    }
}