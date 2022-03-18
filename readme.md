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
    3. Go to instances then click on Launch Instances
    4. For AMI selection select Community AMI and then paste **ami-0b2ad7a7993ad7907** to the search bar and "Ubuntu with Xfig should appear" then press on select![image](https://user-images.githubusercontent.com/82111747/147860829-ab055201-7b8e-4fe9-933b-5d62c9098ee4.png)
    5. For the Instance type select t2.medium the one that 2 vCPUs and 4 GiB of memory or higher
    6. Click on Review and Launch then click on launch
    7. A pop-up should appear about a key pair click on create a new key pair name it on the box below then click on download then click on launch