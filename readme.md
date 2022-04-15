# XFIG - Facility for Interactive Generation of figures under X11

Xfig is a menu-driven tool that allows the user to draw and manipulate objects
interactively in an X window.  The resulting pictures can be saved, printed
on postscript printers, or converted to a variety of other formats (e.g. to
allow inclusion in LaTeX documents).


**Using AWS (Amazon Web Services) to set up Xfig**
**Requirments**
Remote Desktop Connection app, Credit/Debit Card, Phone number(for Verification), Internet Browser

1. Setting Up AWS
    1. This file contains some notes about how to install AWS on a computer.  The first thing to do is to create an account on AWS. This can be done by simply navigating to 
[AWS Console](https://aws.amazon.com/console/ "AWS Console") (Note this might take more time to set-up)
    2. After Sign in Go to Services and click on Compute then click EC2
    3. Check that your server location is **Ohio** and not **N.Virginia** you can change it at the top right corner on most webpages inside AWS![image](https://user-images.githubusercontent.com/82111747/163630691-4cd7cc0d-3227-4eb1-8fab-aa46b89794a3.png)
    4. Once you select the server go to instances then click on Launch Instances
    5. For AMI selection go to **Applications and OS Images** and click on **Browse more AMIs** and then paste **ami-0d426ee9116efd859** to the search bar and "Ubuntu Linux with Xfig" should appear then press on select![image](https://user-images.githubusercontent.com/82111747/163631249-dfe3e6cc-450a-4ffb-b888-0840d1b7479a.png)
    6. For the Instance type select t2.medium the one that 2 vCPUs and 4 GiB of memory or higher
    7. Click on Review and Launch then click on launch
    8. A pop-up should appear about a key pair click on create a new key pair name it on the box below then click on download then click on launch
    
2. Configuring your machine network
    1. Go to your AWS Instance page then click on connect on the top right corner
    2. On the connect to instance page click on connect
    3. Once launched copy and paste "sudo passwd -d ubuntu" to the terminal or if you want to set your own password paste "sudo passwd ubuntu"
      ![image](https://user-images.githubusercontent.com/82111747/148692858-680af869-f5a7-43a5-87fd-f67791a1a9e5.png) 
    4. Go back to your instance page then under security tab click on the blue security group ![148692981-b2f132ec-788f-447e-ab23-4f6d2585b4a6_LI](https://user-images.githubusercontent.com/82111747/148693287-6b33115c-76ea-44fb-80eb-51ae675f379c.jpg)
    5. Click on actions on the top right page then click on edit inbound rules 
    6. Click on the type and change it from SSH to RDP then click on save rules ![image](https://user-images.githubusercontent.com/82111747/148693103-6ba0b673-3542-4a25-a91a-d647ee64dd7f.png)

3. Connecting the machine to your computer (For Windows)
    1. Open remote desktop connection then copy and paste your public IP to Computer box then click yes on the security pop-up
    2. On the login page write the username "ubuntu" then log in then you are all done 

4. Connecting the machine to your computer (For Mac)
    1. Open the App Store and install Microsoft Remote Desktop
    2. Open Microsoft Remote Desktop then copy and paste your public IP to the computer box then click yes on the security pop-up
    3. On the login page write the username "ubuntu" then log in then you are all done 


**Notes**
Every time you start and stop and instance the IP address changes you need to copy the new IP address to connect to your VM
Always stop your session after you are done or else you would be charged money as if you were using the machine or else set a rule for time limit For more [Check here](https://aws.amazon.com/about-aws/whats-new/2013/01/08/use-amazon-cloudwatch-to-detect-and-shut-down-unused-amazon-ec2-instances/). If you leave you maching running 24/7 you will be billed anywhere between **30-50 dollars per month**.

