# XFIG - Facility for Interactive Generation of figures under X11

Xfig is a menu-driven tool that allows the user to draw and manipulate objects
interactively in an X window.  The resulting pictures can be saved, printed
on postscript printers, or converted to a variety of other formats (e.g. to
allow inclusion in LaTeX documents).

For More info about Xfig check out the [YouTube video](https://www.youtube.com/watch?v=9wOMELa_Nx4 "YouTube Video").

# XFIG Tasks Project

Welcome to our Scafolding Project with xFig! Here you will be abble to develop small functions inside a big project. You will see the results of you work and how it can influence the main program.

Before starting, you need to follow the steps bellow to access a virtual machine previoly prepare to help you.

**Using AWS (Amazon Web Services) to set up Xfig**

**Requirments**

Remote Desktop Connection app, Credit/Debit Card, Phone number (for Verification), Internet Browser.

1. Setting Up AWS ([Video Tutorial](https://youtu.be/xkicUjw4wvs))
    1. The first thing to do is to create an account on AWS. This can be done by simply navigating to 
[AWS Console](https://aws.amazon.com/console/ "AWS Console") (Note this might take more time to set-up).
    2. After Sign in, go to menu 'Services' and click on 'Compute', then click on 'EC2 (Virtual Serves in the Cloud)'.
    3. Check that your server location is **N.Virginia** and not **Ohio**. You can change it at the top right corner on most webpages inside AWS.
    
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
    3. Once launched, copy and paste "sudo passwd -d ubuntu" to the terminal (if you want to set your own password, paste "sudo passwd ubuntu").
    
    ![image](https://user-images.githubusercontent.com/82111747/148692858-680af869-f5a7-43a5-87fd-f67791a1a9e5.png)
    
    4. Go back to your instance page and select your instance. Find the tab 'Security' and click on the blue 'Security groups'.
    
    ![image](https://user-images.githubusercontent.com/82111747/148693287-6b33115c-76ea-44fb-80eb-51ae675f379c.jpg)
    
    6. On the top right page, click on the button 'Actions' and select the option 'Edit inbound rules'.
    7. Click on the 'Type' and change it from 'SSH' to 'RDP', then click on the button 'Save rules'.
    
    ![image](https://user-images.githubusercontent.com/82111747/148693103-6ba0b673-3542-4a25-a91a-d647ee64dd7f.png)

3. Connecting the machine to your computer
    1. Go to your AWS instance page and select your instance. Find the 'Public IP' and copy it.
    2. (Just For Mac | [Video Tutorial](https://youtu.be/Dl_7oaLulag)) Open the 'App Store' and install 'Microsoft Remote Desktop'.
    3. Open the aplication 'Remote desktop connection' and past the public IP to 'Computer' box.
    4. A security pop-up will apper. Click on Yes.
    5. On the login page, write the username "ubuntu", then log in.
 
**Notes**

Every time you start and stop and instance, the IP address changes. you need to copy the new IP address to connect to your VM.

Always stop your session after you are done, or else you would be charged money as if you were using the machine. You can set a rule for time limit. For more [Check here](https://aws.amazon.com/about-aws/whats-new/2013/01/08/use-amazon-cloudwatch-to-detect-and-shut-down-unused-amazon-ec2-instances/). If you leave you maching running 24/7, you will be billed anywhere between **30-50 dollars per month**.

# Let's go to work!

1. Accessing Tasks
    1. Open the 'GitHub Desktop'. Go to 'Current branch' and click on the task's name. (The first one is 'Project-1-Enhanced-Rotation').
    
    <img width="1438" alt="branchManager" src="https://user-images.githubusercontent.com/85720584/176274825-5a31ab7e-842a-4af8-b0a0-146452931a65.png"> 
    
    
    2. In the section **Open the repository in your external editor**, click on 'Open in Visual Studio Code'.
    3. Open the file **Assignment Information.txt** and follow the instructions.

2. Switching Branches

    1. Switch to a different project using the branch manager. A pop-up will appear; select…
        1. _Leave my changes_
        2. _Switch branch_
        3. _Overwrite_

 <img width="448" alt="switchBranch" src="https://user-images.githubusercontent.com/85720584/176275201-220e9568-4564-4547-a00a-8c7bf76cb26d.png">


 <img width="596" alt="overwriteStash" src="https://user-images.githubusercontent.com/85720584/176275338-b055a8e3-6892-494a-a036-f082bc573cf6.png">

  
3. Re-accessing Edited Branches

    1. Re-access edited projects through the branch manager. Select… 
        1. _View stash_
        2. _Restore_

<img width="963" alt="viewStash" src="https://user-images.githubusercontent.com/85720584/176276087-8eef38b9-d6c0-4962-b5bd-7a07d18e4a3d.png">

<img width="968" alt="restore" src="https://user-images.githubusercontent.com/85720584/176276125-cec114b5-f9cf-422d-812b-3ac7bc550617.png">

    ii. Continue to Visual Studio Code and the project should be re-opened

For more info about managing, accessing, or compiling your projects on GitHub: [Video Tutorial](https://youtu.be/_jMa9k74U7s).
