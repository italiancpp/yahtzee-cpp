Yahtzee
=======

This is the codebase for the workshop on C++11/14.

It's necessary Cocos2d-X can be downloaded here: [http://www.cocos2d-x.org/download/version#Cocos2d-x][1] [Version 3.2][2]



### Prerequisites ###

    * Linux: at least gcc 4.8
    * Win32: VS 2013 e python 2.7.5
    * OSX: 


### How to build it ###

### Build and run new project for OSX ###

    $ cocos run -p mac

### Build and run new project for linux ###

if you never run cocos2d-x on linux, you need to install all dependences by the
script in **cocos2d/build/install-deps-linux.sh**

    $ cd cocos2d-x/build
    $ ./install-deps-linux.sh

Then

    $ cd NEW_PROJECTS_DIR/MyGame
    $ cocos run -p linux
    
Run

    $ bin/MyGame

### Build and run new project for win32 ###

    $ cocos run -p win32


[1]: http://www.cocos2d-x.org/download/version#Cocos2d-x "Cocos2d-x"
[2]: http://www.cocos2d-x.org/filedown/cocos2d-x-3.2.zip "Versione 3.2"