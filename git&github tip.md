- 1.安装完成后配置自己的姓名和Email地址：
$ git config --global user.name "Your Name"
$ git config --global user.email "email@example.com"
`git config`命令的`--global`参数，用了这个参数，表示你这台机器上所有的Git仓库都会使用这个配置

- 2.安装版本库(repository)：
- /c/Users/Administrator/Documents/Github换到你github的目录下再安装
$ mkdir learngit
$ cd learngit
$ pwd
/c/Users/Administrator/notes

- 通过git init命令把这个目录变成Git可以管理的仓库：
$ git init
Initialized empty Git repository in /Users/michael/learngit/.git/

- 用命令git add告诉Git，把文件添加到仓库：
$ git add readme.txt

- 用命令git commit告诉Git，把文件提交到仓库：
$ git commit -m "wrote a readme file"
[master (root-commit) cb926e7] wrote a readme file
 1 file changed, 2 insertions(+)
 create mode 100644 readme.txt

- 3.版本修改
- 修改文件，然后把修改提交到Git版本库：
$ git add readme.txt
$ git commit -m "append GPL"
[master 3628164] append GPL
 1 file changed, 1 insertion(+), 1 deletion(-)

- 历史记录在Git中用git log命令查看
如果嫌输出信息太多，看得眼花缭乱的，可以试试加上--pretty=oneline参数

- 要把当前版本回退到上一个版本，可以使用git reset命令
$ git reset --hard HEAD^
找到被删除的commit id 仍然可以还原退回操作

- 查看内容用 `cat`
- Git提供了一个命令`git reflog`用来记录你的每一次命令：

-git checkout --
一种是readme.md自修改后还没有被放到暂存区，现在，撤销修改就回到和版本库一模一样的状态；
一种是readme.md已经添加到暂存区后，又作了修改，现在，撤销修改就回到添加到暂存区后的状态。

- 4。删除文件
要从版本库中删除该文件，那就用命令git rm删掉，并且git commit：
把误删的文件恢复到最新版本：
$ git checkout -- test.txt

- 5.远程仓库GitHub连接
登陆GitHub，然后，在右上角找到“Create a new repo”按钮，创建一个新的仓库
在本地的learngit仓库下运行命令：
$ git remote add origin git@github.com:hyqskevin /notes.git

下一步，就可以把本地库的所有内容推送到远程库上：
$ git push -u origin master
由于远程库是空的，我们第一次推送master分支时，加上了-u参数，Git不但会把本地的master分支内容推送的远程新的master分支，还会把本地的master分支和远程的master分支关联起来，在以后的推送或者拉取时就可以简化命令。

- 如果仓库建错了，可以撤回：
1、先删除远程 Git 仓库
$ git remote rm origin
2、再添加远程 Git 仓库

- 
