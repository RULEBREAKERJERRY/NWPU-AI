# Git

# 先立一个小心智模型（超重要！）

- **工作区（Working Directory）**：你正在编辑的真实文件。
- **暂存区（Staging / Index）**：下一次提交要打包带走的变更清单。
- **本地仓库（Repository / HEAD）**：已经提交的历史。
- **远端（Remote）**：GitHub 等服务器上的仓库（常叫 `origin`）。

------

# CONFIGURE TOOLING（配置）

### `git config --global user.name "你的名字"`

给你的提交署名。通常用真实姓名/ID。

- **例子**：`git config --global user.name "Chu Hao Ji"`

### `git config --global user.email "邮箱"`

和名字一起写进提交记录里（不是登录邮箱，纯署名）。

- **例子**：`git config --global user.email "you@example.com"`

### `git config --global color.ui auto`

命令行输出自动上色，更好读。

- **加分项**（可选但实用）：
  - 默认分支名：`git config --global init.defaultBranch main`
  - 常用编辑器：`git config --global core.editor "code --wait"`

> 范围说明：`--global` 影响当前用户；不加则只改当前仓库。

------

# CREATE REPOSITORIES（建仓）

### `git init [project-name]`

把当前目录（或新建的目录）变成 Git 仓库。

- **例子**：

  ```
  mkdir demo && cd demo
  git init
  ```

- **小坑**：已有文件会保持原样，只有你后续 `add/commit` 的才进版本库。

### `git clone [url]`

克隆远端仓库（连同历史）。

- **例子**：`git clone https://github.com/user/repo.git`
- **提示**：克隆后会自动设置远端别名为 `origin`。

------

# MAKE CHANGES（改动与提交）

### `git status`

查看当前仓库状态（修改了啥、哪些在暂存区）。

- **随手一敲**：开发时高频指令；配合下面的 `diff` 用。

### `git add [file]`

把修改加入暂存区。

- **例子**：`git add app.py` 或 `git add .`（全部）
- **提示**：重复 `add` 可更新同一文件的最新修改到暂存区。

### `git reset [file]`

**仅把文件从暂存区移除**，工作区内容不变（“撤销 add”）。

- **例子**：`git reset app.py`
- **等价现代写法**：`git restore --staged app.py`

### `git diff`

查看**未暂存**的改动（工作区 ↔ 暂存区）。

- **例子**：`git diff`

### `git diff --staged`

查看**已暂存**的改动（暂存区 ↔ 上一次提交）。

- **等价写法**：`git diff --cached`

### `git commit -m "信息"`

把暂存区内容记录成一次提交。

- **例子**：`git commit -m "feat: add login flow"`
- **建议**：提交信息遵循动机+内容，如 `fix: resolve crash on M4 macOS`.

------

# GROUP CHANGES（分支与合并）

### `git branch`

列出本地分支；`*` 表示当前所在分支。

- **例子**：`git branch`

### `git branch [branch-name]`

创建新分支（从当前提交分叉）。

- **例子**：`git branch feature/ui`

### `git checkout [branch-name]`

切到某分支，并切换工作区内容。

- **例子**：`git checkout feature/ui`
- **现代替代**：
  - 切换：`git switch feature/ui`
  - 新建并切换：`git switch -c feature/ui`

### `git merge [branch]`

把指定分支合并到**当前分支**。

- **例子**：在 `main` 上执行 `git merge feature/ui`
- **提示**：可能产生合并冲突，按文件提示解决后 `git add`，再 `git commit` 完成合并。

### `git branch -d [branch-name]`

删除本地分支（已合并情况下安全删除）。

- **例子**：`git branch -d feature/ui`
- **强删**（未合并也删）：`git branch -D feature/ui`（请谨慎！）

------

# SYNCHRONIZE CHANGES（远端交互）

> cheat-sheet 用“bookmark/alias”指**远端别名**，常见就是 `origin`。

### `git fetch [bookmark]`

获取远端最新**引用与对象**，不动你的本地分支。

- **例子**：`git fetch origin`
- **应用**：先 fetch，再看 `git log` 或 `git diff`，再决定是否合并。

### `git merge [bookmark]/[branch]`

把远端分支合并到当前分支。

- **例子**：`git merge origin/main`

### `git push [alias] [branch]`

把本地分支的提交推送到远端。

- **例子**：`git push origin main`
- **首次推送并建立上游**：`git push -u origin main`

### `git pull`

相当于 `git fetch` + `git merge`（把远端同名分支合并进来）。

- **等价显式**：`git pull --ff-only` 只快进；`--rebase` 先变基再合并，历史更直。团队约定优先。

------

# REFACTOR FILENAMES（文件重构）

### `git rm [file]`

删除文件并**把删除操作加入暂存区**。

- **例子**：`git rm data.csv` → 随后 `git commit` 记录删除。

### `git rm --cached [file]`

**停止跟踪**该文件，但保留本地文件。

- **例子**：`git rm --cached .env`
- **常配套**：把 `.env` 写进 `.gitignore`，以后不再被追踪。

### `git mv [old] [new]`

重命名/移动文件并自动暂存这个变更。

- **例子**：`git mv README.txt README.md`

> 说明：即便你用系统重命名，Git 通常也能“侦测”到改名（基于内容相似度），但 `git mv` 更显式更稳。

------

# SAVE FRAGMENTS（暂存工作现场）

### `git stash`

把**已追踪文件**的改动打包“塞进抽屉”，工作区回到干净状态。

- **例子**：`git stash`，或命名：`git stash push -m "WIP: card hover"`

### `git stash list`

查看抽屉里有哪些 stash。

- **例子**：`git stash list`

### `git stash pop`

取出最近的 stash 并**删除**这条 stash。

- **例子**：`git stash pop`
- **不删除版本**：`git stash apply`（应用但保留）

### `git stash drop`

丢弃最近的 stash（或指定条目）。

- **例子**：`git stash drop stash@{2}`

> 小坑：未纳入版本控制的新文件默认不被 stash。可用 `git stash -u` 一并收纳未追踪文件。

------

# REDO COMMITS（撤销与回滚）

### `git reset [commit]`

把当前分支指针移到指定提交；**保留**变更在工作区（默认 `--mixed` 行为）。

- **例子**：`git reset HEAD~1`（回退一格提交，但改动还在工作区/部分在暂存区之外）

### `git reset --hard [commit]`

**彻底回到过去**：分支指针、暂存区、工作区统统重置到该提交。

- **例子**：`git reset --hard HEAD~1`
- **高危提示**：会丢本地未推送的改动！别把它当“作业本橡皮擦”。（真的擦掉了就很难救，虽然 *reflog* 有时能救命，但今天先不展开）

> 想“撤销某次提交但保留历史”的更保守做法：考虑 `git revert`（创建一个“反向提交”），适合已推送到团队仓库的场景。

------

# REVIEW HISTORY（看历史/对比）

### `git log`

查看当前分支提交历史。

- **常用选项**：
  - 单行：`git log --oneline`
  - 图谱：`git log --oneline --graph --decorate --all`

### `git log --follow [file]`

查看**某个文件**的历史（包括改名前的历史）。

- **例子**：`git log --follow src/main.cpp`

### `git diff [first-branch]...[second-branch]`

三点语法：对比“`second` 与二者**共同祖先**”的差异（更接近“我需要把 second 合并进 first 会引入什么变化”）。

- **例子**：`git diff main...feature/ui`
- **对比**：两点 `A..B` 是“B 相比 A 的变化”；三点 `A...B` 是“B 相比 merge-base 的变化”。

### `git show [commit]`

展示某个提交的**元信息 + 变更**（patch）。

- **例子**：`git show a1b2c3d`
- **花活**：看特定文件在该提交的内容：`git show a1b2c3d:path/to/file`

------

# SUPPRESS TRACKING（忽略与排除）

### `git ls-files --other --ignored --exclude-standard`

列出当前项目中**被忽略**的非跟踪文件（按标准规则：.gitignore、.git/info/exclude 等）。

- **排查神器**：为什么我 `git add .` 加不上？先查查是不是被忽略了。

### `.gitignore`（文件示例）

```
*.log
build/
temp-*
```

- `*.log`：忽略所有 `.log` 结尾的文件
- `build/`：忽略整个目录
- `temp-*`：忽略以 `temp-` 开头的文件

> 小技巧：如果某文件已经被纳入版本控制，再写进 `.gitignore` 不会自动“取消跟踪”。需要 `git rm --cached path` 一次，把它从版本库里“摘掉”。

---

## 一套最常用工作流（你可以照抄练习）

```
# 1) 初始化/克隆
git init        # 或 git clone <url>
git config user.name "Your Name"
git config user.email "you@example.com"

# 2) 开新分支开发
git switch -c feature/login
# （写代码……）
git status
git add .
git commit -m "feat: basic login page"

# 3) 看差异/历史
git log --oneline --graph --decorate --all
git diff main...feature/login

# 4) 同步远端
git fetch origin
git rebase origin/main   # 或 git merge origin/main（按团队约定）
# 解决冲突 -> add -> 继续 rebase/merge

# 5) 推送
git push -u origin feature/login
```

------

## 常见“等价/现代”对照表（送你）

- 取消暂存：`git reset file` ≈ `git restore --staged file`
- 查看已暂存差异：`git diff --cached` ≈ `git diff --staged`
- 切换分支：`git checkout br` ≈ `git switch br`
- 新建并切换：`git checkout -b br` ≈ `git switch -c br`