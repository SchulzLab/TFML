#TFML
**T**ranscription **F**actor **M**achine **L**earning

*TFML* is a GUI software which is designed for open chromatin data analysis. In TFML, we provide a workflow to conduct analysis for open chromatin data such as DNase1 data. 

##Requirment
In order to run TFML on a linux system, the following software must be available:
* [Qt] (https://www.qt.io/download/), version greater than 5.4
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

Then, go to TFML/bin, execute following command.

    qmake -config release -o Makefile ../src/TFML.pro
    make

##Usage

To start TFML, you can run by following command in TFML/bin or anywhere if you already add TFML into your $PATH.

    TFML

###Setup ypur project
1. Create new project or load exsited project by clicking **File->New project/Open project**. If you create a new project, the new project directory will be created in *~/TFML_project/your_new_project* automatically. If you want to load your existed project, go to the directory in *~/TFML_project/your_project* and click *your_project.pro*. You have to either create a new project or load a existed one before you can do any analysis.

2. Load your file or directory by clicking **File->Open File/Open Directory**. The file or directory will be added into the FileList which is the window in upper left corner.


###Data preprocessing
1. Do peak calling by clicking **Preprocessing->Peak Calling**.

2. Run TEPIC by clicking **Preprocessing->TEPIC**.

3. Integrate your TF affinity score data with expression data by clicking **Preprocessing->Integrate data**.

###Analysis
1. Identify discriminatory TFs by clicking **Analysis->Identify discriminatory TFs**.

2. Identify Key TFs by clicking **Analysis->Identify Key TFs**.

###Other functions
* Save console output into log file by clicking **Save log** button in function bar. The log file will be saved in *~/TFML_project/your_project/Log*.

* Cancel the running process by clicking **Stop** button in function bar.

* Refresh your filelist by clicking **Refresh list** button in function bar.

* **Settings->Settings** shows your path of Peak Caller, TEPIC and TFML script. TFML will detect the path of these tools automatically, if you already set their paths. You can check if your paths of these tools are correct, and you can also change the setting by yourself.

* You can remove directory from the list by **right click->Remove Folder**. You can also remove the directory by **Right click->Remove Folder Permanently**. It will not only remove the entry on the list but also on your disk drive.

###TFML directory
* The TFML directory contains the directories of all project and *Setting.txt* which stores the path of Peak Caller, TEPIC and TFML script.

* Project directory has *Log* directory, *Result* directory and *Your_project_name.pro*. All the log files you have will be in the Log directory. Result directory stores all the output of your analysis. Your_project_name.pro is the file which contains all the directories in Filelist and Result Filelist.

