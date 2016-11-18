#TFML
**T**ranscription **F**actor **M**achine **L**earning

*TFML* is a software GUI that supports integrative analyses of open-chromatin and gene expression data with transcription factor predictions. In TFML, we provide workflows for:
* peak calling from aligned DNAse1 read data using [JAMM]
(https://github.com/mahmoudibrahim/JAMM)
* genome-wide annotation of regions (e.g. open-chromatin peaks or footprints) using TRAP
* computation of TF-gene scores derived from [TEPIC](https://github.com/SchulzLab/TEPIC) annotations
* prediction of **key TFs** for a given gene expression data set, which denotes TFs that are regulating many genes and thus capture their expression variability 
* prediction of **discriminatory TFs** for two given gene classes, for example up- and down-regulated genes
* **TFML** features comprehensive reports for its integrative analyses

##Requirements
In order to run TFML on a linux system, the following software must be available:
* [Qt] (https://www.qt.io/download/), version greater than 5.4
* [JAMM Peak Finder] (https://github.com/mahmoudibrahim/JAMM)
* [TEPIC] (https://github.com/SchulzLab/TEPIC)

After downloading the software, please also add the directory into your $PATH. Edit file "~/.bashrc" by adding the following lines.
* export PATH=$PATH:path of JAMM
* export PATH=$PATH:path of TEPIC/Code

Then run command: source ~/.bashrc

##Install

Download TFML from github. Then add the following directories to your $PATH.
* export PATH=$PATH:path of TFML/bin
* export PATH=$PATH:path of TFML/scripts

You can run command "echo $PATH" to check if the directory was added to $PATH correctly.

Then, go to TFML/bin, execute the following command.

    qmake -config release -o Makefile ../src/TFML.pro
    make

##Usage

To start TFML, you can run in TFML/bin or anywhere if you already added TFML into your $PATH.

    TFML

###Setup your project
1. Create a new project or load existing project by clicking **File->New project/Open project**. If you create a new project, the new project directory will be created in *~/TFML_project/your_new_project* automatically. If you want to load your existing project, go to the directory in *~/TFML_project/your_project* and click *your_project.pro*. You have to either create a new project or load an existing one before you can do any analysis.

2. Load your file or directory by clicking **File->Open File/Open Directory**. The file or directory will be added into the FileList which is the window in the upper left corner.


###Data preprocessing
1. Do peak calling by clicking **Preprocessing->Peak Calling**.

2. Run TEPIC by clicking **Preprocessing->TEPIC**.

3. Integrate your TF affinity score data with expression data by clicking **Preprocessing->Integrate data**.

###Analysis
1. Identify discriminatory TFs by clicking **Analysis->Identify discriminatory TFs**.

2. Identify Key TFs by clicking **Analysis->Identify Key TFs**.

###Other functions
* Save console output into log file by clicking **Save log** button in function bar. The log file will be saved in *~/TFML_project/your_project/Log*.

* Cancel the running process by clicking **Stop** button in the function bar.

* Refresh your filelist by clicking **Refresh list** button in the function bar.

* **Settings->Settings** shows your path for Peak Caller, TEPIC and TFML script. TFML will detect the path of these tools automatically, if you already set their paths. You can check if your paths of these tools are correct, and you can also change the setting yourself.

* You can remove a directory from the list by **right click->Remove Folder**. You can also remove the directory by **Right click->Remove Folder Permanently**. It will not only remove the entry on the list but also on your disk drive.

###TFML directory
* The TFML directory contains the directories of all project and *Setting.txt* which stores the path of Peak Caller, TEPIC and TFML script.

* Project directory has *Log* directory, *Result* directory and *Your_project_name.pro*. All the log files you have will be in the Log directory. Result directory stores all the output of your analysis. Your_project_name.pro is the file which contains all the directories in Filelist and Result Filelist.

