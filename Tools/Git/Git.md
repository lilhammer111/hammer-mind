#### 下载GIT

`sudo apt install git`

#### 创建仓库

来到项目目录下，`git init`创建版本库，会多出一个.git文件

#### 配置身份

`git config --global user.mail "your-email"`

`git config --global user.name "your-name"`

#### 查看文件状态

`git status`

#### 添加文件至更新列表， . 表示当前所有内容，可以用具体文件名替代.

`git add .`

#### 提交文件到本地， -a -m [note] 用来添加注释

`git commit -a -m [note]`

#### 查看提交日志

`git log`

#### 重置文件版本

`git reset --hard [branch-id]`

或者回退到上个版本：

`git reset --hard HEAD^`

#### 连接远程仓库

`git remote add [shortname] <hub-link>`



#### 提交到云端

`git push -u origin main`

#### 从云端拉取

`git pull`

#### 查看分支

`git branch`

#### 新建并切换分支

`git checkout -b [branch-name]`

切换分支

`git checkout [branch-name]`

#### 合并分支

`git merge [branch-name]`

#### 删除分支

`git branch -D [branch-name]`

