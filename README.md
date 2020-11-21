# p1-prosumers
Our project for first semester deals with energy awareness, and turning consumers into prosumers.
Outlined below is the setup of tools used to collaborate on the project.

## WSL 2 setup
First enable and install WSL following the guide [here](https://docs.microsoft.com/en-us/windows/wsl/install-win10).
Then install gcc, make, Git, cURL & Libcurl using the following commands:

### Practical Ubuntu commands to know
| Command | Description |
|---|--:|
| mkdir <directory> | Creates a folder called <directory> |
| touch <filename> | Creates and empty file called <filename>. Also used to update the timestamp of <filename> |
| cd <directory> | Change directory to <directory>. Sends you home if not directory is chosen. |
| ls -al | Show you all the files (hidden files too) in the working directory line-by-line. |
| code . | Opens **Visual Studio Code** editor inside the folder you are in. |
| explorer.exe . | Opens the current directory in Windows explorer at the linux folder. |
| ./<filename> | Runs the file <filename>. |

***

## Connecting to Git with SSH
To give ourselves an easier time, we're going to use SSH (whatever that means) with git.
To set it up, follow the guide [here](https://docs.github.com/en/free-pro-team@latest/github/authenticating-to-github/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent) and [here](https://docs.github.com/en/free-pro-team@latest/github/authenticating-to-github/adding-a-new-ssh-key-to-your-github-account).

### Using Git in the terminal
Here is a list of important Git commands in the Ubuntu terminal, as well as a short description. 

| Command | Description |
|---|--:|
| git status | Displays the current working tree status. |
| git add . | After making a change or adding a file locally, this prepares all changes to be comitted. |
| git commit -m "" | Write a telling description about your change, and records the changes to be pushed. |
| git push | Pushes your comitted changes to the branch you are working in. |
| git checkout <branch> | Changes to the specified <branch>. |
| git checkout -b <branch> | Creates a new local branch with <branch> name. |
| git push --set-upstream origin <branch> | Creates your local branch in the online repo, and pushes to it. |
| git branch | Displays the branch you are working in, as well as other available branches in the project. |

### Git flow
An explanation of an approriate flow for us to get the most out of GitHub.

***

**TODO!** Integrate with Jira. How?
**TODO!** Further describe the setup of WSL.
**TODO!** Further describe working with git and its flow.