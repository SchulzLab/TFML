#TFML
**T**ranscription **F**actor **M**achine **L**earning

*TFML* is a GUI software which is designed for open chromatin data analysis. In TFML, we provide a workflow to conduct analysis for open chromatin data such as DNase1 data. 

##Requirment
In order to run TFML on a linux system, the following software must be available:
* [JAMM Peak Finder] (https://github.com/mahmoudibrahim/JAMM)
* [TEPIC] (https://github.com/SchulzLab/TEPIC)

After download the software, please also add the directory into your $PATH. Edit file "~/.bashrc" by adding following lines.
* export PATH=$PATH:path of JAMM
* export PATH=$PATH:path of TEPIC/Code

Then run command: source ~/.bashrc

##Install

Download TFML from github. Then add the following directory into your $PATH.
* export PATH=$PATH:path of TFML/bin
* export PATH=$PATH:path of TFML/scripts

You can run command "echo $PATH" to check if the directory is added into $PATH correctly.

##Usage

To start TFML, you can run by following command in TFML/bin or anywhere if you already add TFML into your $PATH.

    TFML
