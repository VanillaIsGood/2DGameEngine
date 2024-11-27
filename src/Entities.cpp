#include "Entities.hpp"

// LISTEN SAM ITS 11/19/24 YOU MADE A NEW LINE OF CODE BELOW LINE 97-100

// Remade the entire structure by deleted all previous spaghetti code, made better version.
// 23/10/2024 at exactly 11:19AM -Sam

// Added checks for possible errors stuff
// 23/10/2024 at exactly 11:54 pm -Sam

void Entity::addSprite(SDL_Texture *sprite, int columns, const std::vector<int> &Arr)
{
    EntRect.x = 0;
    EntRect.y = 0;
    Struc_TEXTURE image_information;
    // .texture is where the sprite is lcoated, .columns for columns of the sprite, .frameArr are frames each column of the sprite.
    image_information.texture = sprite;
    image_information.columns = columns;
    image_information.frameArr = Arr;
    SDL_QueryTexture(sprite, NULL, NULL, &image_information.texture_width, &image_information.texture_height);
    // Add the SpriteSheet to the SpriteSheets vector
    SpriteSheets.push_back(image_information);

    // Checks if the frames per column is greater than the number of columns in the texture
    if (image_information.frameArr.size() > image_information.columns || image_information.frameArr.size() < image_information.columns)
    {
        std::cerr << "The frames per column " << image_information.columns << " is not equal " << image_information.frameArr.size() - 1 << std::endl;
        exit(1);
    }
    // Checks if any is not NULL
    else if (image_information.texture != NULL)
    {
        std::cout << "Sprite successfully added." << std::endl
                  << "Size: " << image_information.texture_width << ", Height: " << image_information.texture_height << ", Columns: " << image_information.columns << ", Frame Array: ";
        for (int num : image_information.frameArr)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cerr << "The texture is NULL." << std::endl;
        exit(1);
    }
}

// Remember this thought that for each Sprite Added the size will increase and that should be the index

// name of the Animation, FrameStart where the index of the frame will start, FrameEnd is for the end of the animation, ColumnStart is where the index of the column will start and columnEnd is the column that ends the animation.
void Entity::nameSpriteFraming(std::string name, int FrameStart, int FrameEnd, int columnStart, int columnEnd)
{
    if (FrameStart < 0 || FrameEnd <= 0)
    {
        std::cerr << "Invalid FrameStart, FrameEnd or Sprite Index." << std::endl;
        exit(1);
    }
    else if (columnStart < 0 || columnEnd < 0 || columnEnd < columnStart)
    {
        std::cerr << "Invalid columnStart or columnEnd indice. \n The columnStart should be less than columnEnd and ColumnStart should not be less than 0." << std::endl;
        exit(1);
    }
    // The Index is the SpriteSheet, The FrameStart is where the Frame Starts and versa with FrameEnd
    // New : added column Start and columnEnd
    /*  SpriteSheet array size at [0]
        FrameStart at [1]
        FrameEnd at [2]
        columnStart [3]
        columnEnd [4]
    */
    AnimationDict[name].push_back(SpriteSheets.size() - 1);
    AnimationDict[name].push_back(FrameStart);
    AnimationDict[name].push_back(FrameEnd);
    AnimationDict[name].push_back(columnStart);
    AnimationDict[name].push_back(columnEnd);
}
// FOrgot what day is this
// Future Sam please dont rewrite the code just change the Entity::update() method and ALSO Re Learn what you fucking made and learn how to extract
//  the data from the FramesPerColumnSprite cause i know you will forget it

// The idea is that i want you to not forget that you have to code this into something that will animate only certain parts of the SpriteSheet
// Also FUck you for the fact that you learned 3D arrays instead of finding a better solution

void Entity::update(const std::string &name, int interval)
{
    this->name = name;
    Uint32 currentTime = SDL_GetTicks();
    static Uint32 lastUpdateTime = currentTime;

    // SDL_QueryTexture(SpriteSheets[AnimationDict[name][0]].texture, NULL, NULL, &EntRect.w, &EntRect.h);

    // IMPORTANT: The reason why AnimationDict[name][0] exists is so that for each time a texture is added you don't have to manually change where the texture in the vector.
    int FrameWidth = SpriteSheets[AnimationDict[name][0]].texture_width / SpriteSheets[AnimationDict[name][0]].frameArr[0];
    int FrameHeight = SpriteSheets[AnimationDict[name][0]].texture_height / SpriteSheets[AnimationDict[name][0]].columns;

    EntRect.w = FrameWidth;
    EntRect.h = FrameHeight;

    if (currentTime - lastUpdateTime >= interval)
    {
        std::cout << "current_frame: " << current_frame << " frameArr[current_frame]: " << SpriteSheets[AnimationDict[name][0]].frameArr[current_frame] << " FrameWidth : " << FrameWidth << " EntRect.x = " << EntRect.x << " EntRect.y = " << EntRect.y << std::endl;
        lastUpdateTime = currentTime;

        // Move the sprite to the next frame in the sequence.

        // BUG NEED TO FIX IS THAT THIS LINE OF CODE IS MULTIPLYING ITSELF AND GOING OUT OF BOUNDS.
        // 24/10/2024 at 3:30am -Sam
        // Issue Fixed 7/11/2024 at 1:03 am.

        // This line makes the x axis move to the next frame
        EntRect.x += FrameWidth;
        
        if (!executed)
        {
            std::cout << "AnimationDict : " << AnimationDict[name][1] << std::endl;
            EntRect.x += FrameWidth * AnimationDict[name][1];
            EntRect.y += FrameHeight * AnimationDict[name][3]; // this as well
            executed = true;
        }

        // If the FrameStart reached FrameEnd then it resets the frame back from FrameStart.
        if (EntRect.x > FrameWidth * AnimationDict[name][2] && EntRect.y >= FrameHeight * AnimationDict[name][4]) // this too
        {
            EntRect.x = FrameWidth * AnimationDict[name][1];
            EntRect.y = FrameHeight * AnimationDict[name][3]; // This was the update
            executed = false;
            std::cout << "Frame reseted" << std::endl;
        }
        // else if the frame will reset if it reaches equal to or more than the width of the Sprite Width.
        else if (EntRect.x >= SpriteSheets[AnimationDict[name][0]].texture_width)
        {
            EntRect.x = 0;
            EntRect.y += FrameHeight;
            std::cout << "The Current Frame : " << current_frame << std::endl;
            current_frame++;
            // this part also had an update
            if (current_frame >= SpriteSheets[AnimationDict[name][0]].frameArr.size())
            {
                current_frame = 0;
            }
        }

        // If we've reached the end of the row, reset to the first frame in that row and move the column down.
        // if (EntRect.x >= SpriteSheets[AnimationDict[name][0]].texture_width)
        // {
        //     EntRect.x = 0;
        //     EntRect.y += FrameHeight;
        //     std::cout << "The Current Frame : " << current_frame << std::endl;
        //     current_frame++;
        //     if (current_frame >= SpriteSheets[AnimationDict[name][0]].frameArr.size())
        //     {
        //         current_frame = 0;
        //     }
        // }
        // // If we've reached the end of the column, reset to the first column in that row and move the row down.
        // else if (EntRect.y >= SpriteSheets[AnimationDict[name][0]].texture_height)
        // {
        //     EntRect.x = 0;
        //     EntRect.y = 0;
        // }
    }
}

void Entity::render()
{
    SDL_RenderCopy(RenderWindow::getRenderer(), SpriteSheets[AnimationDict[name][0]].texture, &EntRect, &atr);
}

/*  IMPORTANT IDEA: Entity won't work properly thus this is the future solution Sam before you forget about this.

The idea is you have to change the structure of Entity::update() to find a way to take the column where the FrameStart or FrameEnd will start/end

Idea 1 - Complex route:
    change the FrameStart and FrameEnd to something similar to a tuple but doing that will change the map of AnimationDict
    like (5,3) where 5 is the column and 3 is the start of the Frame
Idea 2 - Lazy route:
    Just add another 2 more inside the SpriteSheet and deal with it
*/

// Btw update your drivers, Please remember to update the int FrameWidth = SpriteSheets[AnimationDict[name][0]].texture_width / SpriteSheets[AnimationDict[name][0]].frameArr[0];
// Make sure you remember to reset the EntRect.y