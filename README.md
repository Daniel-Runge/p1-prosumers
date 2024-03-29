# p1-prosumers
Our project for first semester deals with energy awareness, and turning consumers into prosumers.
Outlined below is the setup of tools used to collaborate on the project.

## 

# Preparation tutorial for developers
On a system with the below installed dependencies, simply type make in the WSL terminal/bash window to create the file energyApp, or type make exe to generate a windows executable (not currently working).

## WSL 2 setup
First enable and install WSL following the guide [here](https://docs.microsoft.com/en-us/windows/wsl/install-win10).
Then install gcc, make, Git, cURL & Libcurl using the following commands:
> sudo apt update && sudo apt upgrade  
> sudo apt install build-essential  
> sudo apt-get install manpages-dev  
> sudo apt install curl  
> sudo apt install libcurl4-openssl-dev  
> sudo apt install libjson-c-dev  
> sudo apt-get install mingw-w64

Optional installations that may be worth installing:
> sudo apt-get install doxygen  
> sudo apt install cmake

### Practical Ubuntu commands to know
| Command | Description |
|---|--:|
| mkdir \<directory> | Creates a folder called \<directory>. |
| touch \<filename> | Creates and empty file called \<filename>. Also used to update the timestamp of \<filename>. |
| cd \<directory> | Change directory to \<directory>. Sends you home if not directory is chosen. |
| ls -al | Show you all the files (hidden files too) in the working directory line-by-line. |
| code . | Opens **Visual Studio Code** editor inside the folder you are in. |
| explorer.exe . | Opens the current directory in Windows explorer at the linux folder. |
| ./\<filename> | Runs the file \<filename>. |

***

## Connecting to Git with SSH
To give ourselves an easier time, we're going to use SSH (whatever that means) with git.
To set it up, follow the guide [here](https://docs.github.com/en/free-pro-team@latest/github/authenticating-to-github/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent) and [here](https://docs.github.com/en/free-pro-team@latest/github/authenticating-to-github/adding-a-new-ssh-key-to-your-github-account).

### Using Git in the terminal
Here is a list of important Git commands in the Ubuntu terminal, as well as a short description. 

| Command | Description |
|---|--:|
| git clone \<repo> | Clones \<repo> onto your local machine. \<repo> is a SSH link from GitHub. |
| git status | Displays the current working tree status. |
| git pull | Update your local data to match online repository. Depends on current branch. |
| git add . | After making a change or adding a file locally, this prepares all changes to be comitted. |
| git commit -m "\<message>" | Write a telling \<message> about your change, and records the changes to be pushed. |
| git push | Pushes your comitted changes to the branch you are working in. |
| git checkout \<branch> | Changes to the specified \<branch>. |
| git checkout -b \<branch> | Creates a new local branch with \<branch> name. |
| git push --set-upstream origin \<branch> | Creates your local branch in the online repo, and pushes to it. |
| git branch | Displays the branch you are working in, as well as other available branches in the project. |

### GitHub flow
[An explanation of an approriate flow for us to get the most out of GitHub.](https://guides.github.com/introduction/flow/)

***

**TODO!** Integrate with Jira. How?

**TODO!** Further describe the setup of WSL.

**TODO!** Further describe working with git and its flow.
