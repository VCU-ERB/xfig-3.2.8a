# XFIG - Facility for Interactive Generation of figures under X11

XFig is a menu-driven tool that allows the user to draw and manipulate objects
interactively in an X window.  The resulting pictures can be saved, printed
on postscript printers, or converted to a variety of other formats (e.g. to
allow inclusion in LaTeX documents).

For More info about Xfig check out the [YouTube video](https://www.youtube.com/watch?v=9wOMELa_Nx4 "YouTube Video").

# XFIG Tasks Project

Welcome to our Scaffolding Project with xFig! Here you will be able to develop functions inside a big project. You will see the results of your work and how it can influence the main program.

Before starting, you need to follow the steps below to access a virtual machine previously prepared to help you.

**Using AWS (Amazon Web Services) to set up Xfig**

**Requirments**

Remote Desktop Connection app, Credit/Debit Card, Phone number (for Verification), Internet Browser.

1. Setting Up AWS ([Video Tutorial](https://youtu.be/xkicUjw4wvs))
    1. The first thing to do is to create an account on AWS. This can be done by simply navigating to 
[AWS Console](https://aws.amazon.com/console/ "AWS Console") (Note this might take more time to set-up).
    2. After Signing in, go to the menu 'Services' and click on 'Compute', then click on 'EC2 (Virtual Servers in the Cloud)'.
    3. Check that your server location is **N.Virginia** and not **Ohio**. You can change it at the top right corner on most web pages inside AWS.
    
    ![image](https://user-images.githubusercontent.com/82111747/165028560-049ee527-91c2-47c1-8d1d-77a452b3e566.png)
    
    4. Once you select the server, go to 'Instances', then click on 'Launch Instances'. The page 'Launch an instance will open'.
    5. Give a name for your instance. In the section **Applications and OS Images**, click on **Browse more AMIs**. Then, paste **ami-0c577f1417b7969a2** to the search bar. In the **Community AMIs**, "Ubuntu Linux with Xfig" should appear. Press on select.
    
    ![image](https://user-images.githubusercontent.com/82111747/163631249-dfe3e6cc-450a-4ffb-b888-0840d1b7479a.png)
    
    6. For the **Instance type**, select 't2.medium', the one that 2 vCPUs and 4 GiB of memory or higher (Check if you are eligible for free storage of 30Gb or 27.9GiB of gp2 or gp3 storage).
    7. In the section **Key pair (login)** choose the option 'Proceed without a key pair' (If you want, you can click on **Create new key pair** and use it instead).
    8. Go to the section **Configure storage** and increase the value from 8 GiB to 14 Gib.
    9. At the end, click on 'Launch instance'.
    
2. Configuring your machine network
    1. Go to your AWS Instance page. Select your instance and click on the button 'Connect' on the top right corner. (You also can use the button 'Actions -> Connect').
    2. On the **Connect to instance** page click on 'Connect'.    
    3. Go back to your instance page and select your instance. Find the tab 'Security' and click on the blue 'Security groups'.
    
    ![image](https://user-images.githubusercontent.com/82111747/148693287-6b33115c-76ea-44fb-80eb-51ae675f379c.jpg)
    
    4. On the top right page, click on the button 'Actions' and select the option 'Edit inbound rules'.
    5. Click on the 'Type' and change it from 'SSH' to 'RDP', then click on the button 'Save rules'.
    
    ![image](https://user-images.githubusercontent.com/82111747/148693103-6ba0b673-3542-4a25-a91a-d647ee64dd7f.png)

3. Connecting the machine to your computer
    1. Go to your AWS instance page and select your instance. Find the 'Public IP' and copy it.
    > (Just For Mac | [Video Tutorial](https://youtu.be/Dl_7oaLulag)) Open the 'App Store' and install 'Microsoft Remote Desktop'.
    2. Open the aplication 'Remote desktop connection' and past the public IP to 'Computer' box.
    3. A security pop-up will appear. Click on Yes.
    4. On the login page, write the username "ubuntu" and password "ubuntu", then log in.
 
**Notes**

Every time you start and stop an instance, the IP address changes. you need to copy the new IP address to connect to your VM.

Always stop your session after you are done, or else you would be charged money as if you were using the machine. You can set a rule for the time limit. For more [Check here](https://aws.amazon.com/about-aws/whats-new/2013/01/08/use-amazon-cloudwatch-to-detect-and-shut-down-unused-amazon-ec2-instances/). If you leave you machine running 24/7, you will be billed anywhere between **30-50 dollars per month**.

You should be *Stopping* your instance and not *Terminating* it, as this will delete your instance and you will need to complete these steps again.

# Let's go to work!

1. Accessing Tasks
    1. Open the 'GitHub Desktop'. Go to 'Current branch' and click on the task's name. (The first one is 'Project-1-Enhanced-Rotation').
    
     ![image](https://user-images.githubusercontent.com/85720584/176274825-5a31ab7e-842a-4af8-b0a0-146452931a65.png)    
    
    2. In the section **Open the repository in your external editor**, click on 'Open in Visual Studio Code'.
    3. Open the file **Assignment Information.txt** and follow the instructions.

2. Switching Branches

    1. When you switch to a different project using the branch manager, a pop-up appears. Choose the first option 'Leave my changes on Project_Name', and then click on the button 'Switch Branch'.
    
    ![image](https://user-images.githubusercontent.com/85720584/176275201-220e9568-4564-4547-a00a-8c7bf76cb26d.png)
    
    2. A pop-up will appear. Click on the button 'Overwrite'.

 ![image](https://user-images.githubusercontent.com/85720584/176275338-b055a8e3-6892-494a-a036-f082bc573cf6.png)
  
3. Re-accessing Edited Branches

    1. To re-access edited projects, use the branch manager. Select 'View stash' and 'Restore'.

 ![image](https://user-images.githubusercontent.com/85720584/176276087-8eef38b9-d6c0-4962-b5bd-7a07d18e4a3d.png)

 ![image](https://user-images.githubusercontent.com/85720584/176276125-cec114b5-f9cf-422d-812b-3ac7bc550617.png)

    2. Continue to Visual Studio Code and the project should be re-opened.

For more info about managing, accessing, or compiling your projects on GitHub: [Video Tutorial](https://youtu.be/_jMa9k74U7s).
