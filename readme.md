 # Xfig Installation 
**How to Install on Windows**

**Requirements (Windows)**
 
Internet Connection, Windows 7 or later, 10 gb of free space, Internet Browser, Free time of one and a half hours, 7zip or Winrar, Visual Studio Code, Visual C++ 2008 and 2010, 4gb of RAM(8 is recommended)

**Steps**
1. Download and Install Cygwin
    1. Open your browser and check that you have a stable internet connection
    2. Download Cygwin from the [Cygwin Official Website](https://www.cygwin.com "Cygwin")
    3. Go to the Installing Cygwin section then click on [setup-x86-64.exe](https://www.cygwin.com/setup-x86_64.exe "setup-x86-64.exe")
    4. Click on run when the prompt comes up
    5. Once the program opens up click on Install from Internet
    6. On the next page you can change the root directory it is preferred that you just click on next
    7. The same goes for the local package directory just click on next
    8. If you have a proxy you can figure it out if not just click on next
    9. On the next page it is going to have a bunch of mirrors you can select whichever is closest but if you do not know you can click on the first few ones then click on next
    10. A new windows should pop up that helps you to select the package
    11.  On the new windows around the upper left corner you will see a menu View click on that and click on category!
       <img src="https://user-images.githubusercontent.com/82111747/134729912-97fc4ddc-0c92-4c43-912a-3d4a7d266cb0.png">
    12. Next to that there is a search bar search "X11" and expand the "All" folder
    13. Look for X11 then next to it there is an option that says Default click on that and click on the Install option 
    14. Repeat the two steps above for Base and Gnome
    15. Once done switch the View option from Category to Full
    16. Search for libXaw3d click on the option Skip and select the latest version from the options
    17. Repeat XVI step for "libXaw3d-devel", "make", "automake1.16", and "htmldoc"
    19. Search for "xfig" then select the latest version which has the “a” version from the options like "3.2.8a-1" not "3.2.8b-1" then check the box on the src column and turn it on!
       <img src="https://user-images.githubusercontent.com/82111747/134729940-da4ad908-ca59-4135-b0c6-07c27d536388.png">
    19. Repeat the same step for "xfig-lib"
    20. Click on next on the bottom right corner
    21. There will be a confirmation box click on next you have successfully downloaded and installed Cygwin
       
*Note* Do not turn off, disconnect the wifi, or put the laptop on sleep while it is downloading you may need to delete the root directory and start the whole step


2. Configuring the root directory
    1. Open Cygwin64 Terminal
    2. Open your file explorer then locate the cygwin64 root directory if default that is C:\cygwin64   
    3. Open your browser 
    4. Go to https://github.com/Da-vid21/xfig-3.2.8a
    5. Click on the “Fork” on the top right corner and copy the url from the address bar ![How to Fork](https://user-images.githubusercontent.com/82111747/136603785-110c3817-16a8-44b2-827d-8d5e83b115d3.png)
    6. Open you Github Desktop and click on "Clone Repository" and go to the url section then paste the URL of the forked github page
    7. Clone the xfig-3.2.8a to the root directory of cygwin64 for default location C:\cygwin64
    8. Go to the opened CYGWIN64 terminal and write "cd /" and then press enter
    9. Write “ls” and press on enter and you should see all the folders listed
    10. Write cd xfig-3.2.8a/
    11. Write “cat INSTALL”
    12.  Go to the xfig-3.2.8a home folder and locate the “install” file
    13. Go to the bottom of the page and copy the code under “On debian, to install xfig under "/usr/share, try”
    14. Copy the next line (./configure -- prefix...defaults), paste in the xfig terminal, delete the space between “$” and “.” and press “Enter”. It would take 5-10 minutes             to configure.                   
    15. Write “make -j” in the xfig terminal when it finishes configuring.
    16. Press the window key, find and start up the “XWin Server”
    17. Hover over to the hidden icon tray and right click on the green xfig icon go to graphics  <img src="https://user-images.githubusercontent.com/82111747/134729963-eec7c6ab-7faf-44a8-a2a9-deca95ae0119.png">
    18. After launching the xfig, check if the application opens and work


3. Editing Xfig Source code
    1. Download and Install [Visual Studio Code](https://code.visualstudio.com/sha/download?build=stable&os=win32-x64 "VSCodeSetup-x64-1.60.1.exe")
    2. Find and locate w_cmdpanel.c in the “src” folder
    3. Open that file in VS Code
    4. In the gap between “Undo” and “(Meta-U)”, write “TEST”, then save the file and exit Visual Studio Code
    5. Write “make -j” in the xfig terminal and hit “Enter
    6. To check that xfig can be opened up manually write “cd src” then write “startx ./xfig”
    7. Click the edit button and you should see a change undo menu that has “Test”
    8. Close the application then write “cd ..” and press enter
    9. Write the code “make -j install” and press enter
    10. Now launch xfig from the system tray and clicking on graphics then xfig check if the undo menu has updated for it too !
       <img src="https://user-images.githubusercontent.com/82111747/134729997-2bc3f91a-805b-4310-9283-d10f19dca633.png">
    11. If successful close the right click on xfig from the system tray xdg menu and exit

**How to Install On MacOS**
       
**Requirements (MacOS)**

Internet Connection, macOS 11/Big Sur or higher, Internet Browser, Free time of 30 minutes  

**Steps**
1. Download the Xfig Code 
    1. Open browser and go to the link https://github.com/Da-vid21/xfig-3.2.8a
    2. Click on the “Fork” on the top right corner and copy the url from the address bar ![How to Fork](https://user-images.githubusercontent.com/82111747/136603785-110c3817-16a8-44b2-827d-8d5e83b115d3.png)
    3. Open you Github Desktop and click on "Clone Repository" and go to the url section then paste the URL of the forked github page
    4. Clone to the directory to you prefrence
    5. After the clone has finished open the Xfig folder
    6. Open the Install file and copy the 2 lines of code below on specific distributions under mac
    7. Right click on an empty space then select Open in Terminal repeat it twice
    8. Paste the code you copied on step VI and hit enter
    9. On the second terminal write “sudo apt-get install xaw3dg-dev” and hit enter then enter your password
    10. If apt-get doesn't work on mac download Homebrew to install copy asnd paste |/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"| this into your terminal 
    11. call brew instead of apt-get (as a prerequisite download Xcode)
    12. Write “make-j” and hit enter
    13. Write “cd src” and click enter then write “ls” and click enter
    14. Write “./xfig” if a new windows opens up that means you have compiled xfig
    15. Write “cd ..” and click enter then write “sudo make install” then hit enter and enter your password
    16. Open finder and search for xfig if it shows up and opens your installation has worked successfully 

**How to Sync your edit from your Source Code on Mac**
 
After you have edited the source code you need to run the code “make -j”

**How to Install on Linux** 

**Requirement (Linux)**

Debian Base Linux, Internet Connection, Internet Browser, Free Space of 100Mb, Free time of 30 minutes, Github for linux 

**Note**
Linux is very case sensitive to the codes you write on the terminal

**Steps**

1. Download the Xfig Code
    1. Open browser and go to the link https://github.com/Da-vid21/xfig-3.2.8a
    2. Click on the “Fork” on the top right corner and copy the url from the address bar ![How to Fork](https://user-images.githubusercontent.com/82111747/136603785-110c3817-16a8-44b2-827d-8d5e83b115d3.png)
    3. To clone xfig to place you prefer open the folder location and right click on an empty space and right click "Open Terminal Here"                                         
![image](https://user-images.githubusercontent.com/82111747/137647109-a22a2cef-0f4d-4cda-ab32-f18b602f4745.png)
    4. Second option to clone is open a terminal then use cd to target that folder location. Ex. if you want to Downloads then New Folder "cd Downloads" then click eneter then "cd 'New Folder'" if the folder name has a space use a string
    ![image](https://user-images.githubusercontent.com/82111747/137647390-e75dd2cb-d5de-4c95-88e3-af8a7abfb76c.png)
    5. Open a terminal and copy "git clone https://github.com/Da-vid21/xfig-3.2.8a"
    6. After the clone has finished open the Xfig folder
    7. Open the Install file and copy the first lines of code below on specific distributions under Debian/Linux
    8. Open two terminals with one on the location of the xfig folder
    9. Paste the code you copied on step VII and hit enter
    10. On the second terminal write “sudo apt-get install xaw3dg-dev” and hit enter hen enter your password
    11. Write “make-j” on the first terminal and hit enter
    12. Write “cd src” and click enter then write “ls” and click enter
    13. If you see a green text with xfig that means you have compiled xfig and you have the excutable file
    ![image](https://user-images.githubusercontent.com/82111747/137647449-764a5d21-549a-45a8-93f2-4c3fe71f09ad.png)
    13. Write “./xfig” if a new windows opens up that means you have succesfully compiled xfig if this step is not working repeat the steps starting from VII
    14. Write “cd ..” and click enter then write “sudo make install” then hit enter and enter your password
    15. Open finder and search for xfig if it shows up and opens your installation has worked successfully 
    

**How to Sync your edit from your Source Code on Linux**
 
After you have edited the source code you need to run the code “make -j” in the xfig folder





